// Created by cr on 2/26/25.

#include "Device.h"
#include "Param_converters.h"
#include "Queue.h"
#include "Swapchain.h"
#include <memory>

namespace Prism::HAL::Vulkan
{
  Device::Device(const VkDevice &vk_device) : _vk_device(std::make_unique<VkDevice>(vk_device)) {}

  Device::~Device()
  {
    if (_vk_device != nullptr)
    {
      vkDestroyDevice(*_vk_device, nullptr);
      _vk_device = nullptr;
    }
  }

  [[nodiscard]] std::unique_ptr<HAL::Queue> Device::get_graphics_queue() const { return get_queue(0, 0); }

  std::unique_ptr<HAL::Swapchain> Device::create_swapchain(const HAL::Swapchain_create_info &create_info) const
  {
    VkSwapchainKHR           vk_swapchain;
    VkSwapchainCreateInfoKHR vk_swapchain_create_info = convert(create_info);
    vkCreateSwapchainKHR(*_vk_device, &vk_swapchain_create_info, nullptr, &vk_swapchain);
    return std::make_unique<Vulkan::Swapchain>(std::move(vk_swapchain), _vk_device.get());
  }

  VkDevice *Device::get_vk_device() const { return _vk_device.get(); }

  [[nodiscard]] std::unique_ptr<HAL::Queue> Device::get_queue(uint32_t queue_family_index, uint32_t queue_index) const
  {
    VkQueue vk_queue;
    vkGetDeviceQueue(*_vk_device, queue_family_index, queue_index, &vk_queue);
    return std::make_unique<Vulkan::Queue>(vk_queue);
  }
} // namespace Prism::HAL::Vulkan
