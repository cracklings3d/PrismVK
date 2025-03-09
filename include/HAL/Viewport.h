#pragma once

#include <cstdint>

namespace Prism::HAL
{
  /**
   * @brief A 2D offset in screen space.
   */
  struct Offset2D
  {
    int32_t x, y;
  };

  /**
   * @brief A 2D extent in screen space.
   */
  struct Extent2D
  {
    uint32_t width, height;
  };

  /**
   * @brief A 2D rectangle in screen space.
   */
  struct Rect2D
  {
    Offset2D offset;
    Extent2D extent;
  };

  enum class Format
  {
    Unknown,
    R8G8B8A8_UNORM,
    R8G8B8A8_SRGB,
    B8G8R8A8_UNORM,
    B8G8R8A8_SRGB,
  };

  /**
   * TODO what space is viewport in?
   * @brief A viewport.
   */
  struct Viewport
  {
    float x;
    float y;
    float width;
    float height;
    float min_depth;
    float max_depth;
  };
} // namespace Prism::HAL
