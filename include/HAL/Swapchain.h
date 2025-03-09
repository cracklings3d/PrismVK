#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "HAL/HAL.h"
#include "HAL/Viewport.h"

namespace Prism::HAL
{
  class Surface;
  class Image;
  class Image_view;
  class Image_view_create_info;

  struct Extent2D;

  enum class Image_format;
  enum class Image_usage;
  enum class Image_sharing_mode;
  enum class Image_present_mode;


  enum class Color_space
  {
    Unknown,
    SRGB_NONLINEAR,
  };

  class Swapchain
  {
  public:
    virtual ~Swapchain() = default;

    [[nodiscard]] virtual std::vector<std::unique_ptr<Image>> get_images() const = 0;

    [[nodiscard]] virtual std::vector<Image_view> create_image_views(
        const Image_view_create_info &create_info, const std::vector<std::unique_ptr<Image>> &images) const
        = 0;
  };

  struct Swapchain_create_info
  {
    Surface           *surface;
    uint32_t           min_image_count;
    Image_format       image_format;
    Color_space        image_color_space;
    Extent2D           image_extent;
    uint32_t           image_array_layers;
    Image_usage        image_usage;
    Image_sharing_mode image_sharing_mode;
    Image_present_mode image_present_mode;
  };
} // namespace Prism::HAL
