#pragma once

#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

#include "../Swapchain.h"

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
        : _vk_swapchain(std::make_unique<VkSwapchainKHR>(vk_swapchain)), _vk_device(vk_device)
    {
    }

    ~Swapchain() override;

    [[nodiscard]] std::vector<HAL::Image>      get_images() const override;
    [[nodiscard]] std::vector<HAL::Image_view> create_image_views(
        const HAL::Image_view_create_info &create_info, const std::vector<HAL::Image> &images) const override;

    [[nodiscard]] VkSwapchainKHR *get_vk_swapchain() const { return _vk_swapchain.get(); }

  private:
    std::unique_ptr<VkSwapchainKHR> _vk_swapchain;
    VkDevice                       *_vk_device;
  };
} // namespace Prism::HAL::Vulkan
