#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "HAL.h"

namespace Prism::HAL
{
  class Surface;
  class Image;
  class Image_view;
  class Image_view_create_info;
  class Extent;

  enum class Image_format;
  enum class Color_space;
  enum class Image_usage;
  enum class Image_sharing_mode;
  enum class Image_present_mode;

  class Swapchain
  {
  public:
    virtual ~Swapchain() = default;

    [[nodiscard]] virtual std::vector<Image> get_images() const = 0;
    [[nodiscard]] virtual std::vector<Image_view>
    create_image_views(const Image_view_create_info &create_info, const std::vector<Image> &images) const = 0;
  };

  struct Swapchain_create_info
  {
    Surface           &surface;
    uint32_t           min_image_count;
    Image_format       image_format;
    Color_space        image_color_space;
    Extent             image_extent;
    uint32_t           image_array_layers;
    Image_usage        image_usage;
    Image_sharing_mode image_sharing_mode;
    Image_present_mode image_present_mode;
  };

  class Swapchain_create_info_builder
  {
  public:
    Swapchain_create_info_builder(Surface &surface);

    Swapchain_create_info_builder &min_image_count(uint32_t min_image_count);
    Swapchain_create_info_builder &image_format(Image_format image_format);
    Swapchain_create_info_builder &image_color_space(Color_space image_color_space);
    Swapchain_create_info_builder &image_extent(Extent image_extent);
    Swapchain_create_info_builder &image_array_layers(uint32_t image_array_layers);
    Swapchain_create_info_builder &image_usage(Image_usage image_usage);
    Swapchain_create_info_builder &image_sharing_mode(Image_sharing_mode image_sharing_mode);
    Swapchain_create_info_builder &image_present_mode(Image_present_mode image_present_mode);

    Swapchain_create_info build();

  private:
    Surface           &_surface;
    uint32_t           _min_image_count;
    Image_format       _image_format;
    Color_space        _image_color_space;
    Extent             _image_extent;
    uint32_t           _image_array_layers;
    Image_usage        _image_usage;
    Image_sharing_mode _image_sharing_mode;
    Image_present_mode _image_present_mode;
  };
} // namespace Prism::HAL
