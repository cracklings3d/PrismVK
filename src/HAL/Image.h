/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <memory>

namespace Prism::HAL
{
  class Image_view;

  struct Image_view_create_info;

  class Image
  {
  public:
    virtual ~Image() = default;

    virtual Image_view create_view(const Image_view_create_info &create_info) const = 0;
  };
} // namespace Prism::HAL
