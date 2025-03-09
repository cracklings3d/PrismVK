#include "HAL/Vulkan/Image.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Param_converters.h"

namespace Prism::HAL::Vulkan
{
  Image_view::~Image_view()
  {
    if (_vk_handle != nullptr)
    {
      vkDestroyImageView(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  VkImageView *Image_view::get_vk_handle() const { return _vk_handle.get(); }

  Image::~Image()
  {
    if (_vk_handle != nullptr)
    {
      vkDestroyImage(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  std::unique_ptr<HAL::Image_view> Image::create_view(const Image_view_create_info &create_info) const
  {
    VkImageViewCreateInfo vk_image_view_create_info = convert(create_info);
    VkImageView           vk_image_view;
    VkResult              result = vkCreateImageView(*_vk_device, &vk_image_view_create_info, nullptr, &vk_image_view);

    check_result(result, __func__);

    return std::make_unique<Image_view>(std::move(vk_image_view), _vk_device);
  }

  VkImage *Image::get_vk_handle() const { return _vk_handle.get(); }

  VkImageUsageFlags convert(const HAL::Image_usage &image_usage)
  {
    switch (image_usage)
    {
    case HAL::Image_usage::COLOR_ATTACHMENT:
      return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    default:
      throw std::runtime_error("Unsupported image usage");
    }
  }
} // namespace Prism::HAL::Vulkan
