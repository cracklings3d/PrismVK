#include "Image_view.h"

namespace Prism::HAL::Vulkan
{
  Image_view::~Image_view()
  {
    if (_vk_image_view != nullptr)
    {
      vkDestroyImageView(*_vk_device, *_vk_image_view, nullptr);
      _vk_image_view = nullptr;
    }
  }

  VkImageView *Image_view::get_vk_image_view() const { return _vk_image_view.get(); }
} // namespace Prism::HAL::Vulkan 