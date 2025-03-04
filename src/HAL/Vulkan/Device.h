// Created by cr on 2/26/25.

#pragma once

#include "../Device.h"
#include "../Queue.h"
#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Physical_device;

  class Device : public HAL::Device
  {
  public:
    ~Device() override;
    explicit Device(const VkDevice &vk_device);

    [[nodiscard]] virtual std::unique_ptr<HAL::Queue> get_graphics_queue() const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Swapchain>
    create_swapchain(const HAL::Swapchain_create_info &create_info) const override;

    [[nodiscard]] VkDevice *get_vk_device() const;

  private:
    std::unique_ptr<VkDevice> _vk_device = nullptr;

    [[nodiscard]] std::unique_ptr<HAL::Queue> get_queue(uint32_t queue_family_index, uint32_t queue_index) const;
  };

  constexpr auto DEVICE_SWAPCHAIN_EXTENSIONS = std::array{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
} // namespace Prism::HAL::Vulkan
