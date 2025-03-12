/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include "HAL/Swapchain.h"

#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

namespace Prism::HAL
{
  class Image_view;
}

namespace Prism::HAL::Vulkan
{
  class Swapchain : public HAL::Swapchain
  {
  public:
    Swapchain(VkSwapchainKHR &&vk_swapchain, VkDevice *vk_device)
        : _vk_handle(std::make_unique<VkSwapchainKHR>(vk_swapchain)), _vk_device(vk_device)
    {}

    ~Swapchain() override;

    [[nodiscard]] std::vector<std::unique_ptr<HAL::Image>> get_images() const override;
    [[nodiscard]] std::vector<HAL::Image_view>             create_image_views(
                    const HAL::Image_view_create_info              &create_info,
                    const std::vector<std::unique_ptr<HAL::Image>> &images) const override;
    [[nodiscard]] uint32_t
    acquire_next_image(HAL::Semaphore *semaphore, uint64_t timeout, HAL::Fence *fence) const override;

    [[nodiscard]] VkSwapchainKHR *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkSwapchainKHR> _vk_handle;
    VkDevice                       *_vk_device;
  };

  VkSwapchainCreateInfoKHR convert(const HAL::Swapchain_create_info &swapchain_create_info);
} // namespace Prism::HAL::Vulkan
