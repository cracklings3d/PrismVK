// Created by cr on 2/23/25.

#pragma once

#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL
{
  class Surface
  {
  public:
    virtual ~Surface() = default;

    Surface() = default;
  };

  /**
   * @brief Information required to create a surface.
   */
  struct Surface_create_info
  {
  };
} // namespace Prism::HAL
