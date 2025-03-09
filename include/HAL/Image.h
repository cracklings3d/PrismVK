/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <memory>

namespace Prism::HAL
{
  enum class Image_format
  {
    Unknown,
    R8G8B8A8_UNORM,
    R8G8B8A8_SRGB,
    B8G8R8A8_UNORM,
    B8G8R8A8_SRGB,
    R32G32B32_SFLOAT,
  };

  enum class Image_present_mode
  {
    Unknown,
    FIFO,
  };

  enum class Image_sharing_mode
  {
    Unknown,
    EXCLUSIVE,
  };

  enum class Image_usage
  {
    Unknown,
    COLOR_ATTACHMENT,
  };

  // Forward declarations
  class Image;
  class Image_view;

  struct Image_view_create_info
  {
    Image       *image;
    Image_format image_format;
  };

  class Image_view
  {
  public:
    virtual ~Image_view() = default;
  };

  class Image
  {
  public:
    virtual ~Image() = default;

    virtual std::unique_ptr<Image_view> create_view(const Image_view_create_info &create_info) const = 0;
  };
} // namespace Prism::HAL
