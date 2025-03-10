/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 01 2025       *
 *****************************/


#pragma once

#include <memory>
#include <vector>

#include "HAL.h"
#include "Util/PCH.h"

namespace Prism::HAL
{
  class Queue;
  class Swapchain;
  class Swapchain_create_info;
  class Render_pass;
  class Render_pass_create_info;
  class Shader_module;
  class Shader_module_create_info;
  class Descriptor_set_layout;
  class Descriptor_set_layout_create_info;
  class Pipeline;
  class Graphics_pipeline_create_info;
  class Pipeline_layout;
  class Pipeline_layout_create_info;

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

    virtual void wait_idle() const = 0;
  };

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

} // namespace Prism::HAL
