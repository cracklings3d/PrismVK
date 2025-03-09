/*****************************
 * Copyright 2025 Cracklings *
 * Created Jan 24 2025       *
 *****************************/

#include "Core/Engine.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_vulkan.h>
#include <array>
#include <cassert>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "HAL/Attachment_description.h"
#include "HAL/Device.h"
#include "HAL/Image.h"
#include "HAL/Instance.h"
#include "HAL/Physical_device.h"
#include "HAL/Pipeline.h"
#include "HAL/Primitive.h"
#include "HAL/Render_pass.h"
#include "HAL/Shader.h"
#include "HAL/Swapchain.h"
#include "HAL/Viewport.h"
#include "HAL/Window.h"

#include "../Resource/TriangleMesh.h"

namespace Prism
{
  void Engine::create_instance()
  {
    HAL::Instance_create_info instance_create_info;

    instance_create_info.application_name    = "Prism Application";
    instance_create_info.engine_name         = "Prism Engine";
    instance_create_info.application_version = PRISM_VERSION(0, 0, 1);
    instance_create_info.engine_version      = PRISM_VERSION(0, 0, 1);

    _instance = HAL::create_instance(std::move(instance_create_info));
  }

  void Engine::create_surface() { _surface = _window->create_surface(*_instance); }

  void Engine::select_physical_device()
  {
    auto physical_devices = _instance->enumerate_physical_devices();

    for (auto &physical_device : physical_devices)
    {
      auto physical_device_properties = physical_device->get_device_properties();
      if (physical_device_properties.device_type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
      {
        this->_physical_device = physical_device;
        break;
      }
    }
    assert(this->_physical_device && "failed to find a suitable GPU!");
  }

  void Engine::create_device_and_queue()
  {
    HAL::Device_queue_create_info device_queue_create_info;
    device_queue_create_info.queue_family_index = 0;
    device_queue_create_info.queue_priorities   = std::make_shared<std::vector<float>>(1.0f);

    HAL::Device_create_info device_create_info;
    device_create_info.queue_create_infos = {device_queue_create_info};

    _device = _physical_device->create_device(device_create_info);
    _queue  = _device->get_graphics_queue();
    assert(_device);
  }

  void Engine::create_swapchain()
  {
    HAL::Swapchain_create_info swapchain_create_info;

    swapchain_create_info.surface            = _surface.get();
    swapchain_create_info.image_format       = HAL::Image_format::B8G8R8A8_SRGB;
    swapchain_create_info.image_color_space  = HAL::Color_space::SRGB_NONLINEAR;
    swapchain_create_info.image_extent       = {800, 600};
    swapchain_create_info.image_array_layers = 1;
    swapchain_create_info.image_usage        = HAL::Image_usage::COLOR_ATTACHMENT;
    swapchain_create_info.image_sharing_mode = HAL::Image_sharing_mode::EXCLUSIVE;
    swapchain_create_info.image_present_mode = HAL::Image_present_mode::FIFO;

    _swapchain = _device->create_swapchain(swapchain_create_info);
  }

  void Engine::create_swapchain_image_views()
  {
    _swapchain_images = _swapchain->get_images();

    for (const std::unique_ptr<HAL::Image> &image : _swapchain_images)
    {
      HAL::Image_view_create_info image_view_create_info;

      image_view_create_info.image        = image.get();
      image_view_create_info.image_format = HAL::Image_format::B8G8R8A8_SRGB;

      _swapchain_image_views.push_back(image->create_view(image_view_create_info));
    }
  }

  void Engine::create_render_pass()
  {
    HAL::Attachment_description attachment_description;

    attachment_description.format           = HAL::Image_format::B8G8R8A8_SRGB;
    attachment_description.samples          = HAL::Sample_count::Count_1;
    attachment_description.load_op          = HAL::Attachment_load_op::Clear;
    attachment_description.store_op         = HAL::Attachment_store_op::Store;
    attachment_description.stencil_load_op  = HAL::Attachment_load_op::Dont_care;
    attachment_description.stencil_store_op = HAL::Attachment_store_op::Dont_care;
    attachment_description.initial_layout   = HAL::Image_layout::Undefined;
    attachment_description.final_layout     = HAL::Image_layout::Present_src;

    HAL::Attachment_reference color_attachment;

    color_attachment.attachment = 0;
    color_attachment.layout     = HAL::Image_layout::Color_attachment_optimal;

    HAL::Subpass_description subpass;
    subpass.pipeline_bind_point = HAL::Pipeline_bind_point::Graphics;
    subpass.color_attachments.push_back(color_attachment);

    HAL::Render_pass_create_info render_pass_create_info;
    render_pass_create_info.attachments = {attachment_description};
    render_pass_create_info.subpasses   = {subpass};

    _render_pass = _device->create_render_pass(render_pass_create_info);
  }

  void Engine::create_shader_modules()
  {
    _vert_shader_module = create_shader_module("Shader/default.vert.spv");
    _frag_shader_module = create_shader_module("Shader/default.frag.spv");
  }

  void Engine::create_graphics_pipeline()
  {
    HAL::Pipeline_shader_stage_create_info vert_shader_stage_info;
    vert_shader_stage_info.shader_stage = HAL::Shader_stage::Vertex;
    vert_shader_stage_info.module       = _vert_shader_module.get();
    vert_shader_stage_info.entry_point  = "main";

    HAL::Pipeline_shader_stage_create_info frag_shader_stage_info;
    frag_shader_stage_info.shader_stage = HAL::Shader_stage::Fragment;
    frag_shader_stage_info.module       = _frag_shader_module.get();
    frag_shader_stage_info.entry_point  = "main";

    std::vector<HAL::Pipeline_shader_stage_create_info> shader_stages
        = {vert_shader_stage_info, frag_shader_stage_info};

    HAL::Vertex_input_binding_description vertex_input_binding_description;
    vertex_input_binding_description.binding    = 0;
    vertex_input_binding_description.stride     = sizeof(float) * 3;
    vertex_input_binding_description.input_rate = HAL::Vertex_input_rate::Vertex;

    HAL::Vertex_input_attribute_description vertex_input_attribute_description;
    vertex_input_attribute_description.location = 0;
    vertex_input_attribute_description.binding  = 0;
    vertex_input_attribute_description.format   = HAL::Image_format::R32G32B32_SFLOAT;
    vertex_input_attribute_description.offset   = 0;

    HAL::Pipeline_vertex_input_state_create_info vertex_input_info;
    vertex_input_info.binding_descriptions.push_back(vertex_input_binding_description);
    vertex_input_info.attribute_descriptions.push_back(vertex_input_attribute_description);

    HAL::Pipeline_input_assembly_state_create_info input_assembly;
    input_assembly.topology                 = HAL::Primitive_topology::Triangle_list;
    input_assembly.primitive_restart_enable = false;

    HAL::Viewport viewport;
    viewport.x         = 0.0f;
    viewport.y         = 0.0f;
    viewport.width     = 800.0f;
    viewport.height    = 600.0f;
    viewport.min_depth = 0.0f;
    viewport.max_depth = 1.0f;

    HAL::Rect2D scissor;
    scissor.offset = {0, 0};
    scissor.extent = {800, 600};

    HAL::Pipeline_viewport_state_create_info viewport_state;
    viewport_state.viewports.push_back(viewport);
    viewport_state.scissors.push_back(scissor);

    HAL::Pipeline_rasterization_state_create_info rasterizer;
    rasterizer.depth_clamp_enable        = false;
    rasterizer.rasterizer_discard_enable = false;
    rasterizer.polygon_mode              = HAL::Polygon_mode::Fill;
    rasterizer.line_width                = 1.0f;
    rasterizer.cull_mode                 = HAL::Cull_mode::Back;
    rasterizer.front_face                = HAL::Front_face::Counter_clockwise;
    rasterizer.depth_bias_enable         = false;

    HAL::Pipeline_multisample_state_create_info multisampling;
    multisampling.rasterization_samples = HAL::Sample_count::Count_1;
    multisampling.sample_shading_enable = false;

    HAL::Pipeline_color_blend_attachment_state color_blend_attachment;
    color_blend_attachment.color_write_mask
        = HAL::Color_component::R | HAL::Color_component::G | HAL::Color_component::B | HAL::Color_component::A;
    color_blend_attachment.blend_enable = false;

    HAL::Pipeline_color_blend_state_create_info color_blending;
    color_blending.logic_op_enable = false;
    color_blending.attachments.push_back(color_blend_attachment);

    HAL::Pipeline_layout_create_info pipeline_layout_create_info;
    pipeline_layout_create_info.descriptor_set_layouts = {};
    pipeline_layout_create_info.push_constant_ranges   = {};

    _pipeline_layout = _device->create_pipeline_layout(pipeline_layout_create_info);

    HAL::Graphics_pipeline_create_info graphics_pipeline_create_info;
    graphics_pipeline_create_info.stages               = shader_stages;
    graphics_pipeline_create_info.vertex_input_state   = &vertex_input_info;
    graphics_pipeline_create_info.input_assembly_state = &input_assembly;
    graphics_pipeline_create_info.viewport_state       = &viewport_state;
    graphics_pipeline_create_info.rasterization_state  = &rasterizer;
    graphics_pipeline_create_info.multisample_state    = &multisampling;
    graphics_pipeline_create_info.color_blend_state    = &color_blending;
    graphics_pipeline_create_info.layout               = _pipeline_layout.get();
    graphics_pipeline_create_info.render_pass          = _render_pass.get();
    graphics_pipeline_create_info.subpass              = 0;

    _pipeline = _device->create_graphics_pipeline(graphics_pipeline_create_info);
  }

  void Engine::create_frame_buffers()
  {
    swap_chain_frame_buffers.resize(swap_chain_size);
    for (size_t i = 0; i < swap_chain_size; i++)
    {
      VkFramebufferCreateInfo framebuffer_info = {};
      framebuffer_info.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
      framebuffer_info.renderPass              = render_pass;
      framebuffer_info.attachmentCount         = 1;
      framebuffer_info.pAttachments            = &swap_chain_image_views[i];
      framebuffer_info.width                   = 800;
      framebuffer_info.height                  = 600;
      framebuffer_info.layers                  = 1;

      assert(
          vkCreateFramebuffer(device, &framebuffer_info, nullptr, &swap_chain_frame_buffers[i]) == VK_SUCCESS
          && "failed to create framebuffer!");
    }
  }

  void Engine::create_vertex_buffer()
  {
    const std::vector vertex_positions = Triangle_mesh::get_vertex_positions();

    VkBufferCreateInfo vertex_buffer_info = {};
    vertex_buffer_info.sType              = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    vertex_buffer_info.size               = sizeof(float) * vertex_positions.size();
    vertex_buffer_info.usage              = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    vertex_buffer_info.sharingMode        = VK_SHARING_MODE_EXCLUSIVE;

    assert(
        vkCreateBuffer(device, &vertex_buffer_info, nullptr, &mesh_vertex_buffer) == VK_SUCCESS
        && "failed to create vertex buffer!");

    VkMemoryRequirements vertex_buffer_memory_requirements;
    vkGetBufferMemoryRequirements(device, mesh_vertex_buffer, &vertex_buffer_memory_requirements);

    VkMemoryPropertyFlags desired_memory_property_flags
        = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    VkMemoryAllocateInfo vertex_buffer_memory_info = {};

    vertex_buffer_memory_info.sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    vertex_buffer_memory_info.allocationSize = vertex_buffer_memory_requirements.size;
    vertex_buffer_memory_info.memoryTypeIndex
        = find_memory_type(vertex_buffer_memory_requirements.memoryTypeBits, desired_memory_property_flags);

    assert(
        vkAllocateMemory(device, &vertex_buffer_memory_info, nullptr, &mesh_vertex_buffer_memory) == VK_SUCCESS
        && "failed to allocate vertex buffer memory!");

    vkBindBufferMemory(device, mesh_vertex_buffer, mesh_vertex_buffer_memory, 0);

    void *data;
    vkMapMemory(device, mesh_vertex_buffer_memory, 0, vertex_buffer_memory_requirements.size, 0, &data);
    memcpy(data, vertex_positions.data(), vertex_buffer_memory_requirements.size);
    vkUnmapMemory(device, mesh_vertex_buffer_memory);
  }

  void Engine::create_command_pool()
  {
    VkCommandPoolCreateInfo pool_info = {};
    pool_info.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.flags                   = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pool_info.queueFamilyIndex        = 0;

    const auto create_command_pool_result = vkCreateCommandPool(device, &pool_info, nullptr, &command_pool);
    if (create_command_pool_result == VK_ERROR_OUT_OF_HOST_MEMORY)
    {
      throw std::runtime_error("failed to create command pool: out of host memory!");
    }
    if (create_command_pool_result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
    {
      throw std::runtime_error("failed to create command pool: out of device memory!");
    }
    assert(create_command_pool_result == VK_SUCCESS);
  }

  void Engine::create_command_buffers()
  {
    command_buffers.resize(swap_chain_size);
    VkCommandBufferAllocateInfo command_buffer_allocate_info = {};
    command_buffer_allocate_info.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    command_buffer_allocate_info.commandPool                 = command_pool;
    command_buffer_allocate_info.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    command_buffer_allocate_info.commandBufferCount          = static_cast<uint32_t>(command_buffers.size());

    const auto allocate_command_buffer_result
        = vkAllocateCommandBuffers(device, &command_buffer_allocate_info, command_buffers.data());
    if (allocate_command_buffer_result == VK_ERROR_OUT_OF_HOST_MEMORY)
    {
      throw std::runtime_error("failed to allocate command buffer: out of host memory!");
    }
    if (allocate_command_buffer_result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
    {
      throw std::runtime_error("failed to allocate command buffer: out of device memory!");
    }
    assert(allocate_command_buffer_result == VK_SUCCESS);
  }

  void Engine::create_index_buffer()
  {
    const std::vector<uint32_t> indices = {0, 1, 2};

    VkBufferCreateInfo index_buffer_info = {};
    index_buffer_info.sType              = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    index_buffer_info.size               = sizeof(indices[0]) * indices.size();
    index_buffer_info.usage              = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    index_buffer_info.sharingMode        = VK_SHARING_MODE_EXCLUSIVE;

    // assert(
    //   vkCreateBuffer(device, &index_buffer_info, nullptr, &mesh_index_buffer) == VK_SUCCESS &&
    //   "failed to create index buffer!"
    // );
    //
    // void *data;
    // vkMapMemory(device, mesh_index_buffer_memory, 0, VK_WHOLE_SIZE, 0, &data);
    // memcpy(data, indices.data(), (size_t)VK_WHOLE_SIZE);
    // vkUnmapMemory(device, mesh_index_buffer_memory);
  }

  void Engine::present_frame_buffer()
  {
    VkPresentInfoKHR present_info   = {};
    present_info.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores    = get_render_finished_semaphore();
    present_info.swapchainCount     = 1;
    present_info.pSwapchains        = &swap_chain;
    present_info.pImageIndices      = &swap_chain_index;

    vkQueuePresentKHR(graphic_queue, &present_info);
  }

  void Engine::request_frame_buffer()
  {
    vkWaitForFences(device, 1, get_current_command_buffer_fence(), VK_TRUE, UINT64_MAX);
    vkResetFences(device, 1, get_current_command_buffer_fence());

    vkAcquireNextImageKHR(
        device, swap_chain, UINT64_MAX, *(image_available_semaphores.data() + semaphore_index), VK_NULL_HANDLE,
        &swap_chain_index);
  }

  void Engine::initialize()
  {
    _window = HAL::create_window(_render_api);
    create_instance();
    create_surface();
    select_physical_device();
    create_device_and_queue();
    create_swapchain();
    create_swapchain_image_views();
    create_render_pass();
    create_shader_modules();
    create_graphics_pipeline();
    create_frame_buffers();
    create_vertex_buffer();
    create_command_pool();
    create_command_buffers();
    create_semaphores();
    create_fences();

    // Main loop
    while (!should_quit)
    {
      printf("--- frame #%d ---\n", frame_index);

      semaphore_index = frame_index % swap_chain_size;

      handle_input_events();
      request_frame_buffer();
      record_command_buffer(command_buffers[swap_chain_index], swap_chain_frame_buffers[swap_chain_index]);
      submit_command_buffer();
      present_frame_buffer();

      frame_index++;
    }

    _device->wait_idle();
  }

  std::unique_ptr<HAL::Shader_module> Engine::create_shader_module(const std::string &file_path) const
  {
    std::ifstream file(file_path);

    if (!file.is_open())
    {
      throw std::runtime_error("failed to open file: " + file_path);
    }

    std::vector<char> spirv((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::string spirv_code(spirv.begin(), spirv.end());

    HAL::Shader_module_create_info create_info = {};

    create_info.code = spirv_code;

    return _device->create_shader_module(create_info);
  }

  uint32_t Engine::find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) const
  {
    assert(physical_device);

    VkPhysicalDeviceMemoryProperties physical_device_constraint;

    vkGetPhysicalDeviceMemoryProperties(physical_device, &physical_device_constraint);

    for (uint32_t i = 0; i < physical_device_constraint.memoryTypeCount; ++i)
    {
      if ((type_filter & (1 << i)) && // Is memory type compatible with buffer?
          (physical_device_constraint.memoryTypes[i].propertyFlags & properties)
              == properties) // Does memory type have required properties?
      {
        return i;
      }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
  }

  void Engine::create_semaphores()
  {
    image_available_semaphores.resize(swap_chain_size);
    render_finished_semaphores.resize(swap_chain_size);
    for (size_t i = 0; i < swap_chain_size; i++)
    {
      VkSemaphoreCreateInfo semaphore_info = {};

      semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

      assert(
          vkCreateSemaphore(device, &semaphore_info, nullptr, &image_available_semaphores[i]) == VK_SUCCESS
          && "failed to create semaphores!");
      assert(
          vkCreateSemaphore(device, &semaphore_info, nullptr, &render_finished_semaphores[i]) == VK_SUCCESS
          && "failed to create semaphores!");
    }
  }

  void Engine::create_fences()
  {
    image_available_semaphores.resize(swap_chain_size);
    render_finished_semaphores.resize(swap_chain_size);
    command_buffer_fences.resize(swap_chain_size);

    VkFenceCreateInfo fence_info = {};

    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < swap_chain_size; i++)
    {
      VkSemaphoreCreateInfo semaphore_info = {};
      semaphore_info.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

      assert(vkCreateSemaphore(device, &semaphore_info, nullptr, &image_available_semaphores[i]) == VK_SUCCESS);
      assert(vkCreateSemaphore(device, &semaphore_info, nullptr, &render_finished_semaphores[i]) == VK_SUCCESS);
      assert(vkCreateFence(device, &fence_info, nullptr, &command_buffer_fences[i]) == VK_SUCCESS);
    }
  }

  void Engine::handle_input_events()
  {
    SDL_Event event;
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
    {
      should_quit = true;
    }
  }

  void Engine::submit_command_buffer()
  {
    VkSubmitInfo submitInfo           = {};
    submitInfo.sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT};
    submitInfo.waitSemaphoreCount     = 1;
    submitInfo.pWaitSemaphores        = get_image_available_semaphore();
    submitInfo.pWaitDstStageMask      = waitStages;
    submitInfo.commandBufferCount     = 1;
    submitInfo.pCommandBuffers        = &command_buffers[swap_chain_index];
    submitInfo.signalSemaphoreCount   = 1;
    submitInfo.pSignalSemaphores      = get_render_finished_semaphore();

    if (vkQueueSubmit(graphic_queue, 1, &submitInfo, *get_current_command_buffer_fence()) != VK_SUCCESS)
    {
      throw std::runtime_error("failed to submit draw command buffer!");
    }
  }

  VkFramebuffer Engine::get_current_frame_buffer() const
  {
    return swap_chain_frame_buffers[frame_index % swap_chain_size];
  }

  VkCommandBuffer Engine::get_current_command_buffer() const { return command_buffers[frame_index % swap_chain_size]; }

  const VkFence *Engine::get_previous_command_buffer_fence() const
  {
    return command_buffer_fences.data() + (frame_index + 2) % swap_chain_size;
  }

  const VkFence *Engine::get_current_command_buffer_fence() const
  {
    return command_buffer_fences.data() + frame_index % swap_chain_size;
  }

  const VkSemaphore *Engine::get_image_available_semaphore() const
  {
    return image_available_semaphores.data() + semaphore_index;
  }

  const VkSemaphore *Engine::get_render_finished_semaphore() const
  {
    return render_finished_semaphores.data() + semaphore_index;
  }

  void Engine::record_command_buffer(VkCommandBuffer command_buffer, VkFramebuffer frame_buffer) const
  {
    VkCommandBufferBeginInfo command_buffer_info = {};
    command_buffer_info.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    command_buffer_info.flags                    = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

    assert(
        vkBeginCommandBuffer(command_buffer, &command_buffer_info) == VK_SUCCESS
        && "failed to begin recording command buffer!");

    VkRenderPassBeginInfo render_pass_begin_info = {};
    render_pass_begin_info.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_begin_info.renderPass            = render_pass;
    render_pass_begin_info.framebuffer           = frame_buffer;
    render_pass_begin_info.renderArea.offset     = {0, 0};
    render_pass_begin_info.renderArea.extent     = {800, 600};
    render_pass_begin_info.clearValueCount       = 1;
    render_pass_begin_info.pClearValues          = &clear_color;

    vkCmdBeginRenderPass(command_buffer, &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

    std::vector<VkDeviceSize> offsets = {0};

    // Bind pipeline and draw triangle here (pipeline creation omitted for brevity)
    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphics_pipeline);
    vkCmdBindVertexBuffers(command_buffer, 0, 1, &mesh_vertex_buffer, offsets.data());
    vkCmdDraw(command_buffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(command_buffer);

    assert(vkEndCommandBuffer(command_buffer) == VK_SUCCESS && "failed to record command buffer!");
  }
} // namespace Prism
