/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 23 2025       *
 *****************************/

#pragma once

#include "HAL/Physical_device.h"

#include <vulkan/vulkan_core.h>

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

  Physical_device_properties convert(const VkPhysicalDeviceProperties &vk_physical_device_properties);
} // namespace Prism::HAL::Vulkan
