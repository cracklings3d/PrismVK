/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <memory>

#include "HAL.h"
#include "Image.h"

namespace Prism::HAL
{
  class Image_view
  {
  public:
    virtual ~Image_view() = default;
  };

  struct Image_view_create_info
  {
    Image       &image;
    Image_format image_format;
  };

  class Image_view_create_info_builder
  {
  public:
    Image_view_create_info_builder &image(Image &image);
    Image_view_create_info_builder &image_format(Image_format image_format);
    Image_view_create_info          build();

  private:
    Image       *_image;
    Image_format _image_format;
  };
} // namespace Prism::HAL
