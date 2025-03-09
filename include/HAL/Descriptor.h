/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 07 2025       *
 *****************************/

#pragma once

#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

#include "HAL/Shader.h"
#include "Util/PCH.h"

namespace Prism::HAL
{
  enum class Descriptor_type
  {
    Sampler                = 0,
    Combined_image_sampler = 1,
    Sampled_image          = 2,
    Storage_image          = 3,
    Uniform_texel_buffer   = 4,
    Storage_texel_buffer   = 5,
    Uniform_buffer         = 6,
    Storage_buffer         = 7,
    Uniform_buffer_dynamic = 8,
    Storage_buffer_dynamic = 9,
    Input_attachment       = 10,
    // TODO: Add the rest of the extended descriptor types
  };

  /**
   * @brief Information about a single binding in a descriptor set layout
   */
  struct Descriptor_set_layout_binding
  {
    uint32_t        binding;
    Descriptor_type descriptor_type;
    uint32_t        descriptor_count;
    Shader_stage    stage_flags;
  };

  /**
   * @brief Information required to create a descriptor set layout
   */
  struct Descriptor_set_layout_create_info
  {
    std::vector<Descriptor_set_layout_binding> bindings;
  };

  /**
   * @brief Abstract interface for descriptor set layout
   */
  class Descriptor_set_layout
  {
  public:
    virtual ~Descriptor_set_layout() = default;
  };

} // namespace Prism::HAL
