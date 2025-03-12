/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#include "HAL/Vulkan/Swapchain.h"

#include "HAL/Vulkan/Common.h"
#include "HAL/Vulkan/Image.h"
#include "HAL/Vulkan/Surface.h"
#include "HAL/Vulkan/Sync.h"
#include "HAL/Vulkan/Viewport.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  Swapchain::~Swapchain()
  {
    if (_vk_handle != nullptr)
    {
      vkDestroySwapchainKHR(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  std::vector<std::unique_ptr<HAL::Image>> Swapchain::get_images() const
  {
    std::vector<std::unique_ptr<HAL::Image>> hal_images;
    std::vector<VkImage>                     vk_images;

    uint32_t image_count;
    vkGetSwapchainImagesKHR(*_vk_device, *_vk_handle, &image_count, nullptr);
    vk_images.resize(image_count);
    vkGetSwapchainImagesKHR(*_vk_device, *_vk_handle, &image_count, vk_images.data());

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
      vk_create_info.image                 = *static_cast<Vulkan::Image *>(image.get())->get_vk_handle();

      vkCreateImageView(*_vk_device, &vk_create_info, nullptr, &vk_image_view);
      vk_image_views.push_back(vk_image_view);
    }

    return image_views;
  }

  uint32_t Swapchain::acquire_next_image(HAL::Semaphore *semaphore, uint64_t timeout, HAL::Fence *fence) const
  {
    uint32_t image_index;

    vkAcquireNextImageKHR(
        *_vk_device, *_vk_handle, timeout, *static_cast<Vulkan::Semaphore *>(semaphore)->get_vk_handle(),
        *static_cast<Vulkan::Fence *>(fence)->get_vk_handle(), &image_index);

    return image_index;
  }

  VkSwapchainCreateInfoKHR convert(const HAL::Swapchain_create_info &swapchain_create_info)
  {
    VkSwapchainCreateInfoKHR vk_swapchain_create_info{};

    vk_swapchain_create_info.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    vk_swapchain_create_info.surface          = *((Vulkan::Surface &)swapchain_create_info.surface).get_vk_surface();
    vk_swapchain_create_info.minImageCount    = swapchain_create_info.min_image_count;
    vk_swapchain_create_info.imageFormat      = convert_enum<VkFormat>(swapchain_create_info.image_format);
    vk_swapchain_create_info.imageColorSpace  = convert_enum<VkColorSpaceKHR>(swapchain_create_info.image_color_space);
    vk_swapchain_create_info.imageExtent      = convert(swapchain_create_info.image_extent);
    vk_swapchain_create_info.imageArrayLayers = swapchain_create_info.image_array_layers;
    vk_swapchain_create_info.imageUsage       = convert_enum<VkImageUsageFlags>(swapchain_create_info.image_usage);
    vk_swapchain_create_info.imageSharingMode = convert_enum<VkSharingMode>(swapchain_create_info.image_sharing_mode);
    vk_swapchain_create_info.presentMode = convert_enum<VkPresentModeKHR>(swapchain_create_info.image_present_mode);

    return vk_swapchain_create_info;
  }


} // namespace Prism::HAL::Vulkan
