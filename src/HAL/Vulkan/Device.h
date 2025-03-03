// Created by cr on 2/26/25.

#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include "../Device.h"


namespace Prism::HAL::Vulkan
{
  class Physical_device;

  class Device : public HAL::Device
  {
  public:
    ~Device() override = default;
    explicit Device(const VkDevice &vk_device);

  private:
    std::unique_ptr<VkDevice> _device = nullptr;
  };

  constexpr auto DEVICE_SWAPCHAIN_EXTENSIONS = std::array{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
}
