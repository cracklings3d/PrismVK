/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 26 2025       *
 *****************************/

#include "HAL/Vulkan/Device.h"

#include <cassert>
#include <memory>

#include "HAL/Vulkan/Buffer.h"
#include "HAL/Vulkan/Command.h"
#include "HAL/Vulkan/Common.h"
#include "HAL/Vulkan/Descriptor.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Framebuffer.h"
#include "HAL/Vulkan/Physical_device.h"
#include "HAL/Vulkan/Pipeline.h"
#include "HAL/Vulkan/Queue.h"
#include "HAL/Vulkan/Render_pass.h"
#include "HAL/Vulkan/Shader.h"
#include "HAL/Vulkan/Swapchain.h"
#include "HAL/Vulkan/Sync.h"
#include "Util/Util.h"

namespace Prism::HAL::Vulkan
{
  Device::Device(const VkDevice &vk_device, VkPhysicalDevice *vk_physical_device)
      : _vk_handle(std::make_unique<VkDevice>(vk_device)), _vk_physical_device(vk_physical_device)
  {}

  Device::~Device()
  {
    if (_vk_handle != nullptr)
    {
      vkDestroyDevice(*_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  [[nodiscard]] std::unique_ptr<HAL::Queue> Device::get_graphics_queue() const { return get_queue(0, 0); }

  std::unique_ptr<HAL::Swapchain> Device::create_swapchain(const HAL::Swapchain_create_info &create_info) const
  {
    VkSwapchainKHR           vk_swapchain;
    VkSwapchainCreateInfoKHR vk_swapchain_create_info = convert(create_info);
    vkCreateSwapchainKHR(*_vk_handle, &vk_swapchain_create_info, nullptr, &vk_swapchain);

    // TODO: Why does this even compile? Unique ptrs do not support covariant return types.
    return std::make_unique<Vulkan::Swapchain>(std::move(vk_swapchain), _vk_handle.get());
  }

  std::unique_ptr<HAL::Render_pass> Device::create_render_pass(const HAL::Render_pass_create_info &create_info) const
  {
    VkRenderPass           vk_render_pass;
    VkRenderPassCreateInfo vk_render_pass_create_info = convert(create_info);
    VkResult result = vkCreateRenderPass(*_vk_handle, &vk_render_pass_create_info, nullptr, &vk_render_pass);

    check_result(result, __func__);

    std::unique_ptr<Vulkan::Render_pass> vulkan_render_pass
        = std::make_unique<Vulkan::Render_pass>(std::move(vk_render_pass), _vk_handle.get());

    return std::make_unique<HAL::Render_pass>(std::move(*vulkan_render_pass));
  }

  std::unique_ptr<HAL::Shader_module>
  Device::create_shader_module(const HAL::Shader_module_create_info &create_info) const
  {
    VkShaderModuleCreateInfo vk_create_info = convert(create_info);
    VkShaderModule           vk_shader_module;

    VkResult result = vkCreateShaderModule(*_vk_handle, &vk_create_info, nullptr, &vk_shader_module);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Shader_module>(std::move(vk_shader_module), _vk_handle.get());
  }

  std::unique_ptr<HAL::Descriptor_set_layout>
  Device::create_descriptor_set_layout(const HAL::Descriptor_set_layout_create_info &create_info) const
  {
    VkDescriptorSetLayoutCreateInfo vk_create_info = convert(create_info);
    VkDescriptorSetLayout           vk_descriptor_set_layout;

    VkResult result = vkCreateDescriptorSetLayout(*_vk_handle, &vk_create_info, nullptr, &vk_descriptor_set_layout);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Descriptor_set_layout>(std::move(vk_descriptor_set_layout), _vk_handle.get());
  }

  std::unique_ptr<HAL::Pipeline_layout>
  Device::create_pipeline_layout(const HAL::Pipeline_layout_create_info &create_info) const
  {
    VkPipelineLayoutCreateInfo vk_create_info = convert(create_info);
    VkPipelineLayout           vk_pipeline_layout;

    VkResult result = vkCreatePipelineLayout(*_vk_handle, &vk_create_info, nullptr, &vk_pipeline_layout);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Pipeline_layout>(std::move(vk_pipeline_layout), _vk_handle.get());
  }

  std::unique_ptr<HAL::Pipeline>
  Device::create_graphics_pipeline(const HAL::Graphics_pipeline_create_info &create_info) const
  {
    VkGraphicsPipelineCreateInfo vk_create_info = convert(create_info);
    VkPipeline                   vk_pipeline;

    VkResult result = vkCreateGraphicsPipelines(*_vk_handle, nullptr, 1, &vk_create_info, nullptr, &vk_pipeline);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Pipeline>(std::move(vk_pipeline), _vk_handle.get());
  }

  void Device::wait_idle() const { vkDeviceWaitIdle(*_vk_handle); }

  uint32_t Device::find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) const
  {
    assert(_vk_physical_device);

    VkPhysicalDeviceMemoryProperties physical_device_constraint;

    vkGetPhysicalDeviceMemoryProperties(*_vk_physical_device, &physical_device_constraint);

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

  [[nodiscard]] std::unique_ptr<HAL::Queue> Device::get_queue(uint32_t queue_family_index, uint32_t queue_index) const
  {
    VkQueue vk_queue;
    vkGetDeviceQueue(*_vk_handle, queue_family_index, queue_index, &vk_queue);
    return std::make_unique<Vulkan::Queue>(vk_queue);
  }

  struct VkParamTag_DeviceCreateInfo_pQueueCreateInfos
  {};

  struct VkParamTag_DeviceQueueCreateInfo_pQueuePriorities
  {};

  template <>
  struct StructMemberTraits<VkParamTag_DeviceCreateInfo_pQueueCreateInfos>
  {
    using StructType = VkDeviceCreateInfo;
    using MemberType = VkDeviceQueueCreateInfo *;

    static constexpr MemberType StructType::*member = VkDeviceCreateInfo::pQueueCreateInfos;
  };

  template <>
  struct StructMemberTraits<VkParamTag_DeviceQueueCreateInfo_pQueuePriorities>
  {
    using StructType = VkDeviceQueueCreateInfo;
    using MemberType = float *;

    static constexpr MemberType StructType::*member = &VkDeviceQueueCreateInfo::pQueuePriorities;
  };

  VkScopedDeviceCreateInfo convert(const HAL::Device_create_info &device_create_info)
  {
    VkDeviceCreateInfo vk_device_create_info{};

    Util::Scoped_vector<VkDeviceQueueCreateInfo, std::vector<float>> vk_queue_create_infos;

    for (const auto &queue_create_info : device_create_info.queue_create_infos)
    {
      vk_queue_create_infos.push_back(convert(queue_create_info));
    }

    vk_device_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    vk_device_create_info.enabledExtensionCount   = device_create_info.required_extensions.size();
    vk_device_create_info.ppEnabledExtensionNames = device_create_info.required_extensions.data();
    vk_device_create_info.pQueueCreateInfos       = vk_queue_create_infos.data();
    vk_device_create_info.queueCreateInfoCount    = vk_queue_create_infos.size();

    return { vk_device_create_info, {vk_queue_create_infos}, device_create_info.required_extensions }
  };
}

VkScopedDeviceQueueCreateInfo convert(const HAL::Device_queue_create_info &device_queue_create_info)
{
  VkDeviceQueueCreateInfo vk_device_queue_create_info{};

  vk_device_queue_create_info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  vk_device_queue_create_info.queueFamilyIndex = device_queue_create_info.queue_family_index;
  vk_device_queue_create_info.queueCount       = device_queue_create_info.queue_priorities.size();
  vk_device_queue_create_info.pQueuePriorities = device_queue_create_info.queue_priorities.data();

  return {._vk_struct = vk_device_queue_create_info, ._kept_alive = device_queue_create_info.queue_priorities};
}

std::unique_ptr<HAL::Framebuffer> Device::create_framebuffer(const HAL::Framebuffer_create_info &create_info) const
{
  VkFramebufferCreateInfo vk_create_info = convert(create_info);
  VkFramebuffer           vk_framebuffer;

  VkResult result = vkCreateFramebuffer(*_vk_handle, &vk_create_info, nullptr, &vk_framebuffer);
  check_result(result, __func__);

  return std::make_unique<Vulkan::Framebuffer>(std::move(vk_framebuffer), _vk_handle.get());
}

std::unique_ptr<HAL::Buffer> Device::create_buffer(const HAL::Buffer_create_info &create_info) const
{
  VkBufferCreateInfo vk_create_info = convert(create_info);
  VkBuffer           vk_buffer;

  VkResult result = vkCreateBuffer(*_vk_handle, &vk_create_info, nullptr, &vk_buffer);
  check_result(result, __func__);

  VkMemoryRequirements mem_requirements;
  vkGetBufferMemoryRequirements(*_vk_handle, vk_buffer, &mem_requirements);

  VkMemoryAllocateInfo alloc_info{};
  alloc_info.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.allocationSize  = mem_requirements.size;
  alloc_info.memoryTypeIndex = find_memory_type(
      mem_requirements.memoryTypeBits, convert_enum<VkMemoryPropertyFlags>(create_info.desired_memory_properties));

  VkDeviceMemory vk_memory;
  result = vkAllocateMemory(*_vk_handle, &alloc_info, nullptr, &vk_memory);
  check_result(result, __func__);

  vkBindBufferMemory(*_vk_handle, vk_buffer, vk_memory, 0);

  return std::make_unique<Vulkan::Buffer>(std::move(vk_buffer), std::move(vk_memory), _vk_handle.get());
}

std::unique_ptr<HAL::Buffer_view> Device::create_buffer_view(const HAL::Buffer_view_create_info &create_info) const
{
  VkBufferViewCreateInfo vk_create_info = convert(create_info);
  VkBufferView           vk_buffer_view;

  VkResult result = vkCreateBufferView(*_vk_handle, &vk_create_info, nullptr, &vk_buffer_view);
  check_result(result, __func__);

  return std::make_unique<Vulkan::Buffer_view>(std::move(vk_buffer_view), _vk_handle.get());
}

std::unique_ptr<HAL::Command_pool> Device::create_command_pool(const HAL::Command_pool_create_info &create_info) const
{
  VkCommandPoolCreateInfo vk_create_info = convert(create_info);
  VkCommandPool           vk_command_pool;

  VkResult result = vkCreateCommandPool(*_vk_handle, &vk_create_info, nullptr, &vk_command_pool);
  check_result(result, __func__);

  return std::make_unique<Vulkan::Command_pool>(std::move(vk_command_pool), _vk_handle.get());
}

std::unique_ptr<HAL::Semaphore> Device::create_semaphore(const HAL::Semaphore_create_info &create_info) const
{
  VkSemaphoreCreateInfo vk_create_info = convert(create_info);
  VkSemaphore           vk_semaphore;

  VkResult result = vkCreateSemaphore(*_vk_handle, &vk_create_info, nullptr, &vk_semaphore);
  check_result(result, __func__);

  return std::make_unique<Vulkan::Semaphore>(std::move(vk_semaphore), _vk_handle.get());
}

std::unique_ptr<HAL::Fence> Device::create_fence(const HAL::Fence_create_info &create_info) const
{
  VkFenceCreateInfo vk_create_info = convert(create_info);
  VkFence           vk_fence;

  VkResult result = vkCreateFence(*_vk_handle, &vk_create_info, nullptr, &vk_fence);
  check_result(result, __func__);

  return std::make_unique<Vulkan::Fence>(std::move(vk_fence), _vk_handle.get());
}
} // namespace Prism::HAL::Vulkan
