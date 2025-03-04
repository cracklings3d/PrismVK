#include "Image_view.h"

namespace Prism::HAL
{
  Image_view_create_info_builder &Image_view_create_info_builder::image(Image &image)
  {
    _image = &image;
    return *this;
  }

  Image_view_create_info_builder &Image_view_create_info_builder::image_format(Image_format image_format)
  {
    _image_format = image_format;
    return *this;
  }

  Image_view_create_info Image_view_create_info_builder::build()
  {
    return Image_view_create_info{*_image, _image_format};
  }
} // namespace Prism::HAL
