// Created by cr on 2/23/25.

#pragma once

#include <vulkan/vulkan_core.h>

#include "../Physical_device.h"

namespace Prism::HAL::Vulkan
{
  class Physical_device final : public HAL::Physical_device
  {
  public:
    explicit Physical_device(const VkPhysicalDevice &vk_physical_device);

    [[nodiscard]] Physical_device_properties   get_device_properties() const override;
    [[nodiscard]] std::unique_ptr<HAL::Device> create_device(const Device_create_info &device_create_info) override;

    [[nodiscard]] VkPhysicalDevice *get_vk_handle() const { return _vk_handle.get(); }

  private:

  private:
    std::shared_ptr<VkPhysicalDevice> _vk_handle = nullptr;
  };
} // namespace Prism::HAL::Vulkan
