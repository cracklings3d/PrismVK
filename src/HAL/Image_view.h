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
    Image       *image;
    Image_format image_format;
  };
} // namespace Prism::HAL
