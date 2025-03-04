/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 03 2025       *
 *****************************/

#include "Swapchain.h"

namespace Prism::HAL
{
  Prism::HAL::Swapchain_create_info_builder::Swapchain_create_info_builder(Surface &surface) : _surface(surface) {}

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::min_image_count(uint32_t min_image_count)
  {
    _min_image_count = min_image_count;
    return *this;
  }

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::image_format(Image_format image_format)
  {
    _image_format = image_format;
    return *this;
  }

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::image_color_space(Color_space image_color_space)
  {
    _image_color_space = image_color_space;
    return *this;
  }

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::image_extent(Extent image_extent)
  {
    _image_extent = image_extent;
    return *this;
  }

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::image_array_layers(uint32_t image_array_layers)
  {
    _image_array_layers = image_array_layers;
    return *this;
  }

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::image_usage(Image_usage image_usage)
  {
    _image_usage = image_usage;
    return *this;
  }

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::image_sharing_mode(Image_sharing_mode image_sharing_mode)
  {
    _image_sharing_mode = image_sharing_mode;
    return *this;
  }

  Prism::HAL::Swapchain_create_info_builder &
  Prism::HAL::Swapchain_create_info_builder::image_present_mode(Image_present_mode image_present_mode)
  {
    _image_present_mode = image_present_mode;
    return *this;
  }

  Prism::HAL::Swapchain_create_info Prism::HAL::Swapchain_create_info_builder::build()
  {
    return Prism::HAL::Swapchain_create_info{
        .surface            = _surface,
        .min_image_count    = _min_image_count,
        .image_format       = _image_format,
        .image_color_space  = _image_color_space,
        .image_extent       = _image_extent,
        .image_array_layers = _image_array_layers,
        .image_usage        = _image_usage,
        .image_sharing_mode = _image_sharing_mode,
        .image_present_mode = _image_present_mode,
    };
  }
} // namespace Prism::HAL
