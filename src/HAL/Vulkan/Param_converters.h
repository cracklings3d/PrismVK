#pragma once

#include "../Physical_device.h"
#include <vulkan/vulkan_core.h>

namespace Prism::HAL
{
  struct Instance_create_info;
  struct Device_create_info;
} // namespace Prism::HAL

namespace Prism::HAL::Vulkan
{
  /************************* HAL to Vulkan *************************/
  VkInstanceCreateInfo convert(const HAL::Instance_create_info &instance_create_info);
  VkDeviceCreateInfo   convert(const HAL::Device_create_info &device_create_info);

  /************************* Vulkan to HAL *************************/
  Physical_device_properties convert(const VkPhysicalDeviceProperties &vk_physical_device_properties);

} // namespace Prism::HAL::Vulkan
