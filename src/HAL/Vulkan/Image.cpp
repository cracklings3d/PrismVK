#include "HAL/Vulkan/Image.h"

#include "HAL/Vulkan/Common.h"
#include "HAL/Vulkan/Error.h"

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

    VkResult result = vkCreateImageView(*_vk_device, &vk_image_view_create_info, nullptr, &vk_image_view);
    check_result(result, __func__);

    return std::make_unique<Image_view>(std::move(vk_image_view), _vk_device);
  }

  VkImageViewCreateInfo convert(const HAL::Image_view_create_info &hal)
  {
    VkImageViewCreateInfo vk           = {};
    vk.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vk.image                           = *((Vulkan::Image &)hal.image).get_vk_handle();
    vk.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
    vk.format                          = convert_enum<VkFormat>(hal.image_format);
    vk.subresourceRange                = {};
    vk.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    vk.subresourceRange.baseMipLevel   = 0;
    vk.subresourceRange.levelCount     = 1;
    vk.subresourceRange.baseArrayLayer = 0;
    vk.subresourceRange.layerCount     = 1;

    return vk;
  }


} // namespace Prism::HAL::Vulkan
