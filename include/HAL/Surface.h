/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 23 2025       *
 *****************************/

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
