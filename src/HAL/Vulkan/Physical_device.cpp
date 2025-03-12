/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 23 2025       *
 *****************************/

#include "HAL/Vulkan/Physical_device.h"

#include "HAL/Vulkan/Device.h"
#include "HAL/Vulkan/Error.h"

#include <cassert>

namespace Prism::HAL::Vulkan
{
  Physical_device::Physical_device(const VkPhysicalDevice &vk_physical_device)
      : _vk_handle(std::make_shared<VkPhysicalDevice>(vk_physical_device))
  {}

  // Consider a top-down requirement approach instead of parsing and presenting the properties
  Physical_device_properties Physical_device::get_device_properties() const
  {
    VkPhysicalDeviceProperties vk_physical_device_properties;
    vkGetPhysicalDeviceProperties(*_vk_handle, &vk_physical_device_properties);
    return convert(vk_physical_device_properties);
  }

  std::unique_ptr<HAL::Device> Physical_device::create_device(const Device_create_info &device_create_info)
  {
    VkDeviceCreateInfo vk_device_create_info = convert(device_create_info);

    VkDevice vk_device;
    VkResult result = vkCreateDevice(*_vk_handle, &vk_device_create_info, nullptr, &vk_device);

    check_result(result, "Create_device");

    return std::make_unique<Device>(vk_device, _vk_handle.get());
  }

  Physical_device_properties convert(const VkPhysicalDeviceProperties &vk)
  {
    Physical_device_properties hal{};

    hal.api_version    = vk.apiVersion;
    hal.driver_version = vk.driverVersion;
    hal.vendor_id      = vk.vendorID;
    hal.device_id      = vk.deviceID;
    hal.device_type    = vk.deviceType;
    hal.device_name    = vk.deviceName;

    return hal;
  }
} // namespace Prism::HAL::Vulkan
