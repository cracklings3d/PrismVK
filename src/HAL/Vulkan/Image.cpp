#include "Image.h"
#include "Error.h"
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

  HAL::Image_view Image::create_view(const Image_view_create_info &create_info) const
  {
    VkImageViewCreateInfo vk_image_view_create_info = convert(create_info);
    VkImageView           vk_image_view;
    VkResult              result = vkCreateImageView(*_vk_device, &vk_image_view_create_info, nullptr, &vk_image_view);

    check_result(result, __func__);

    return Image_view(std::move(vk_image_view), _vk_device);
  }

  VkImage *Image::get_vk_image() const { return _vk_image.get(); }
} // namespace Prism::HAL::Vulkan
