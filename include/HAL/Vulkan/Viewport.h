/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 09 2025       *
 *****************************/

#pragma once

#include "HAL/Viewport.h"

#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  VkRect2D   convert(const Rect2D &rect);
  VkExtent2D convert(const Extent2D &extent);
  VkOffset2D convert(const Offset2D &offset);
  VkFormat   convert(const Format &format);
  VkViewport convert(const Viewport &viewport);
} // namespace Prism::HAL::Vulkan
