#include "Image.h"
#include "Image_view.h"
#include "Param_converters.h"

namespace Prism::HAL::Vulkan
{
  Image::~Image()
  {
    if (_vk_image != nullptr)
    {
      vkDestroyImage(*_vk_device, *_vk_image, nullptr);
      _vk_image = nullptr;
    }
  }

  Image_view Image::create_image_view(const Image_view_create_info &create_info) const
  {
    VkImageViewCreateInfo vk_image_view_create_info = convert(create_info);
    VkImageView           vk_image_view;
    vkCreateImageView(*_vk_device, &vk_image_view_create_info, nullptr, &vk_image_view);

    return Image_view(std::move(vk_image_view), _vk_device);
  }

  VkImage *Image::get_vk_image() const { return _vk_image.get(); }
} // namespace Prism::HAL::Vulkan
