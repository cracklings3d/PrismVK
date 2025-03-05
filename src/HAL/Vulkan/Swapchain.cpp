#include "Swapchain.h"

#include <vector>
#include <vulkan/vulkan.h>

#include "Image.h"
#include "Image_view.h"
#include "Param_converters.h"

namespace Prism::HAL::Vulkan
{
  Swapchain::~Swapchain()
  {
    if (_vk_swapchain != nullptr)
    {
      vkDestroySwapchainKHR(*_vk_device, *_vk_swapchain, nullptr);
      _vk_swapchain = nullptr;
    }
  }

  std::vector<std::unique_ptr<HAL::Image>> Swapchain::get_images() const
  {
    std::vector<std::unique_ptr<HAL::Image>> hal_images;
    std::vector<VkImage>                     vk_images;

    uint32_t image_count;
    vkGetSwapchainImagesKHR(*_vk_device, *_vk_swapchain, &image_count, nullptr);
    vk_images.resize(image_count);
    vkGetSwapchainImagesKHR(*_vk_device, *_vk_swapchain, &image_count, vk_images.data());

    for (auto &vk_image : vk_images)
    {
      hal_images.push_back(std::make_unique<Vulkan::Image>(std::move(vk_image), _vk_device));
    }

    return hal_images;
  }

  std::vector<HAL::Image_view> Swapchain::create_image_views(
      const HAL::Image_view_create_info &create_info, const std::vector<std::unique_ptr<HAL::Image>> &images) const
  {
    std::vector<HAL::Image_view> image_views;
    std::vector<VkImageView>     vk_image_views;


    for (const auto &image : images)
    {
      VkImageView vk_image_view;

      VkImageViewCreateInfo vk_create_info = convert(create_info);
      vk_create_info.image                 = *static_cast<Vulkan::Image *>(image.get())->get_vk_image();

      vkCreateImageView(*_vk_device, &vk_create_info, nullptr, &vk_image_view);
      vk_image_views.push_back(vk_image_view);
    }

    return image_views;
  }
} // namespace Prism::HAL::Vulkan
