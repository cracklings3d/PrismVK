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

  std::vector<HAL::Image> Swapchain::get_images() const
  {
    std::vector<HAL::Image> images;
    std::vector<VkImage>    vk_images;

    uint32_t image_count;
    vkGetSwapchainImagesKHR(*_vk_device, *_vk_swapchain, &image_count, nullptr);
    vk_images.resize(image_count);
    vkGetSwapchainImagesKHR(*_vk_device, *_vk_swapchain, &image_count, vk_images.data());

    images.resize(image_count);
    for (uint32_t i = 0; i < image_count; i++)
    {
      images[i] = Vulkan::Image(std::move(vk_images[i]), _vk_device);
    }

    return images;
  }

  std::vector<HAL::Image_view> Swapchain::create_image_views(
      const HAL::Image_view_create_info &create_info, const std::vector<HAL::Image> &images) const
  {
    std::vector<HAL::Image_view> image_views;
    std::vector<VkImageView>     vk_image_views;

    VkImageViewCreateInfo vk_create_info = convert(create_info);

    for (const auto &image : images)
    {
      VkImageView vk_image_view;
      vkCreateImageView(*_vk_device, &vk_create_info, nullptr, &vk_image_view);
      vk_image_views.push_back(vk_image_view);
    }

    return image_views;
  }
} // namespace Prism::HAL::Vulkan
