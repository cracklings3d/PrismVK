/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 09 2025       *
 *****************************/

#include "HAL/Vulkan/Viewport.h"

#include <stdexcept>

namespace Prism::HAL::Vulkan
{
  VkRect2D convert(const Rect2D &rect)
  {
    VkRect2D vk_rect{};
    vk_rect.offset = convert(rect.offset);
    vk_rect.extent = convert(rect.extent);
    return vk_rect;
  }

  VkExtent2D convert(const Extent2D &extent)
  {
    VkExtent2D vk_extent{};
    vk_extent.width  = extent.width;
    vk_extent.height = extent.height;
    return vk_extent;
  }

  VkOffset2D convert(const Offset2D &offset)
  {
    VkOffset2D vk_offset{};
    vk_offset.x = offset.x;
    vk_offset.y = offset.y;
    return vk_offset;
  }

  VkFormat convert(const Format &format)
  {
    switch (format)
    {
    case Format::R8G8B8A8_UNORM:
      return VK_FORMAT_R8G8B8A8_UNORM;
    case Format::R8G8B8A8_SRGB:
      return VK_FORMAT_R8G8B8A8_SRGB;
    case Format::B8G8R8A8_UNORM:
      return VK_FORMAT_B8G8R8A8_UNORM;
    case Format::B8G8R8A8_SRGB:
      return VK_FORMAT_B8G8R8A8_SRGB;
    default:
      throw std::runtime_error("Unsupported format");
    }
  }

  VkViewport convert(const Viewport &viewport)
  {
    VkViewport vk_viewport{};
    // Implementation from your existing converter
    return vk_viewport;
  }
} // namespace Prism::HAL::Vulkan
