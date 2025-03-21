#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "HAL/Buffer.h"
#include "HAL/Command.h"
#include "HAL/Device.h"
#include "HAL/Framebuffer.h"
#include "HAL/Image.h"
#include "HAL/Instance.h"
#include "HAL/Pipeline.h"
#include "HAL/Queue.h"
#include "HAL/Render_pass.h"
#include "HAL/Shader.h"
#include "HAL/Surface.h"
#include "HAL/Swapchain.h"
#include "HAL/Sync.h"
#include "HAL/Window.h"

namespace Prism
{
  class Engine
  {
  public:
    explicit Engine(const HAL::Render_settings &render_settings) : _render_settings(render_settings) {}

    void initialize();

  private:
    [[nodiscard]] std::unique_ptr<HAL::Shader_module> create_shader_module(const std::string &file_path) const;

    [[nodiscard]] uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) const;

    void create_instance();
    void create_surface();
    void select_physical_device();
    void create_device_and_queue();
    void create_swapchain();
    void create_swapchain_image_views();
    void create_render_pass();
    void create_shader_modules();
    void create_graphics_pipeline();
    void create_frame_buffers();
    void create_vertex_buffer();
    void create_command_pool();
    void create_command_buffers();
    void create_index_buffer();
    void create_semaphores();
    void create_fences();


    void handle_input_events();
    void request_frame_buffer();
    void record_command_buffer(VkCommandBuffer command_buffer, VkFramebuffer frame_buffer) const;
    void submit_command_buffer();
    void present_frame_buffer();


    [[nodiscard]] HAL::Framebuffer    *get_current_frame_buffer() const;
    [[nodiscard]] HAL::Command_buffer *get_current_command_buffer() const;
    [[nodiscard]] HAL::Fence          *get_previous_command_buffer_fence() const;
    [[nodiscard]] HAL::Fence          *get_current_command_buffer_fence() const;

    [[nodiscard]] HAL::Semaphore *get_image_available_semaphore() const;
    [[nodiscard]] HAL::Semaphore *get_render_finished_semaphore() const;

  private:
    HAL::Render_settings _render_settings;

    std::unique_ptr<HAL::Window>   _window   = nullptr;
    std::unique_ptr<HAL::Instance> _instance = nullptr;
    std::unique_ptr<HAL::Surface>  _surface  = nullptr;

    std::shared_ptr<HAL::Physical_device> _physical_device;

    std::unique_ptr<HAL::Device>    _device    = nullptr;
    std::unique_ptr<HAL::Queue>     _queue     = nullptr;
    std::unique_ptr<HAL::Swapchain> _swapchain = nullptr;

    std::vector<std::unique_ptr<HAL::Image>>       _swapchain_images      = {};
    std::vector<std::unique_ptr<HAL::Image_view>>  _swapchain_image_views = {};
    std::vector<std::unique_ptr<HAL::Framebuffer>> _framebuffers          = {};

    std::unique_ptr<HAL::Render_pass> _render_pass = nullptr;

    std::unique_ptr<HAL::Shader_module> _vert_shader_module = nullptr;
    std::unique_ptr<HAL::Shader_module> _frag_shader_module = nullptr;

    std::unique_ptr<HAL::Pipeline_layout> _pipeline_layout = nullptr;
    std::unique_ptr<HAL::Pipeline>        _pipeline        = nullptr;

    std::unique_ptr<HAL::Buffer> _vertex_buffer = nullptr;

    std::unique_ptr<HAL::Command_pool>                _command_pool    = nullptr;
    std::vector<std::unique_ptr<HAL::Command_buffer>> _command_buffers = {};

    std::vector<std::unique_ptr<HAL::Semaphore>> _image_available_semaphores = {};
    std::vector<std::unique_ptr<HAL::Semaphore>> _render_finished_semaphores = {};

    std::vector<std::unique_ptr<HAL::Fence>> _command_buffer_fences = {};

  private:
    VkClearValue clear_color = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

    uint32_t swap_chain_size = 0;

    // per instance variable
    VkCommandPool  command_pool              = nullptr;
    VkPipeline     graphics_pipeline         = nullptr;
    VkDeviceMemory mesh_vertex_buffer_memory = nullptr;

    VkViewport viewport = {};
    VkRect2D   scissor  = {};

    VkPipelineLayout pipeline_layout = nullptr;

    // World data
    VkBuffer mesh_vertex_buffer = nullptr;

    std::vector<VkSemaphore> image_available_semaphores;
    std::vector<VkSemaphore> render_finished_semaphores;

    VkShaderModule vert_shader_module = nullptr;
    VkShaderModule frag_shader_module = nullptr;


    // volatile (per frame) data
    uint32_t     frame_index     = 0;
    uint32_t     swapchain_index = 0;
    uint32_t     semaphore_index = 0;
    VkRenderPass render_pass     = nullptr;

    std::vector<VkImage>         swap_chain_images;
    std::vector<VkImageView>     swap_chain_image_views;
    std::vector<VkFramebuffer>   swap_chain_frame_buffers;
    std::vector<VkCommandBuffer> command_buffers;
    std::vector<VkFence>         command_buffer_fences;

    bool should_quit = false;
  };
} // namespace Prism
