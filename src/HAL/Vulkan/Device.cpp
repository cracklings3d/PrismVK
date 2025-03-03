// Created by cr on 2/26/25.

#include "Device.h"


namespace Prism::HAL::Vulkan
{
  Device::Device(const VkDevice &vk_device) : _device(std::make_unique<VkDevice>(vk_device)) {}
}
