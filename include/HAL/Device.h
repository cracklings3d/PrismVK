/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 01 2025       *
 *****************************/


#pragma once

#include <memory>
#include <vector>

namespace Prism::HAL
{
  class Queue;
  class Swapchain;
  class Render_pass;
  class Shader_module;
  class Descriptor_set_layout;
  class Pipeline;
  class Pipeline_layout;
  class Framebuffer;
  class Buffer;
  class Buffer_view;
  class Command_pool;
  class Semaphore;
  class Fence;

  struct Swapchain_create_info;
  struct Render_pass_create_info;
  struct Shader_module_create_info;
  struct Descriptor_set_layout_create_info;
  struct Graphics_pipeline_create_info;
  struct Pipeline_layout_create_info;
  struct Framebuffer_create_info;
  struct Buffer_create_info;
  struct Buffer_view_create_info;
  struct Command_pool_create_info;
  struct Semaphore_create_info;
  struct Fence_create_info;

  /**
   * @brief Information required to create a command queue
   */
  struct Device_queue_create_info
  {
    uint32_t                            queue_family_index;
    std::shared_ptr<std::vector<float>> queue_priorities;
  };

  /**
   * @brief Information required to create a device
   */
  struct Device_create_info
  {
    std::vector<Device_queue_create_info> queue_create_infos;
    std::vector<const char *>             required_extensions;
  };

  class Device
  {
  public:
    virtual ~Device() = default;

    [[nodiscard]] virtual std::unique_ptr<Queue> get_graphics_queue() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Swapchain> create_swapchain(const Swapchain_create_info &create_info) const
        = 0;
    [[nodiscard]] virtual std::unique_ptr<Render_pass>
    create_render_pass(const Render_pass_create_info &create_info) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Shader_module>
    create_shader_module(const Shader_module_create_info &create_info) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Descriptor_set_layout>
    create_descriptor_set_layout(const Descriptor_set_layout_create_info &create_info) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Pipeline_layout>
    create_pipeline_layout(const Pipeline_layout_create_info &create_info) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Pipeline>
    create_graphics_pipeline(const Graphics_pipeline_create_info &create_info) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Framebuffer>
    create_framebuffer(const Framebuffer_create_info &create_info) const = 0;

    [[nodiscard]] virtual std::unique_ptr<Buffer> create_buffer(const Buffer_create_info &create_info) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Buffer_view>
    create_buffer_view(const Buffer_view_create_info &create_info) const = 0;

    virtual void wait_idle() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Command_pool>
    create_command_pool(const Command_pool_create_info& create_info) const = 0;

    [[nodiscard]] virtual std::unique_ptr<Semaphore> 
    create_semaphore(const Semaphore_create_info& create_info) const = 0;
    
    [[nodiscard]] virtual std::unique_ptr<Fence>
    create_fence(const Fence_create_info& create_info) const = 0;
  };

} // namespace Prism::HAL
