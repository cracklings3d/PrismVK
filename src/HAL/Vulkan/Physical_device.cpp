// Created by cr on 2/23/25.

#include "HAL/Device.h"

#include "HAL/Vulkan/Device.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Param_converters.h"
#include "HAL/Vulkan/Physical_device.h"

namespace Prism::HAL::Vulkan
{
  Physical_device::Physical_device(const VkPhysicalDevice &vk_physical_device)
      : _vk_physical_device(std::make_shared<VkPhysicalDevice>(vk_physical_device))
  {}

  Physical_device_properties Physical_device::get_device_properties() const
  {
    VkPhysicalDeviceProperties vk_physical_device_properties;
    vkGetPhysicalDeviceProperties(*_vk_physical_device, &vk_physical_device_properties);
    return convert(vk_physical_device_properties);
  }

  std::unique_ptr<HAL::Device> Physical_device::create_device(const Device_create_info &device_create_info)
  {
    VkDeviceCreateInfo vk_device_create_info = convert(device_create_info);

    VkDevice vk_device;
    VkResult result = vkCreateDevice(*_vk_physical_device, &vk_device_create_info, nullptr, &vk_device);

    check_result(result, "Create_device");

    return std::make_unique<Device>(vk_device);
  }

  VkPhysicalDevice *Physical_device::get_vk_physical_device() const { return _vk_physical_device.get(); }
} // namespace Prism::HAL::Vulkan
