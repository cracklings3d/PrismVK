/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 26 2025       *
 *****************************/

#include <memory>

#include "../Render_pass.h"

#include "Device.h"
#include "Error.h"
#include "Param_converters.h"
#include "Queue.h"
#include "Render_pass.h"
#include "Shader_module.h"
#include "Swapchain.h"

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

    // TODO: Why does this even compile? Unique ptrs do not support covariant return types.
    return std::make_unique<Vulkan::Swapchain>(std::move(vk_swapchain), _vk_device.get());
  }

  std::unique_ptr<HAL::Render_pass> Device::create_render_pass(const HAL::Render_pass_create_info &create_info) const
  {
    VkRenderPass           vk_render_pass;
    VkRenderPassCreateInfo vk_render_pass_create_info = convert(create_info);
    VkResult result = vkCreateRenderPass(*_vk_device, &vk_render_pass_create_info, nullptr, &vk_render_pass);

    check_result(result, __func__);

    std::unique_ptr<Vulkan::Render_pass> vulkan_render_pass
        = std::make_unique<Vulkan::Render_pass>(std::move(vk_render_pass), _vk_device.get());

    return std::make_unique<HAL::Render_pass>(std::move(*vulkan_render_pass));
  }

  std::unique_ptr<HAL::Shader_module>
  Device::create_shader_module(const HAL::Shader_module_create_info &create_info) const
  {
    VkShaderModuleCreateInfo vk_create_info = convert(create_info);
    VkShaderModule           vk_shader_module;

    VkResult result = vkCreateShaderModule(*_vk_device, &vk_create_info, nullptr, &vk_shader_module);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Shader_module>(std::move(vk_shader_module), _vk_device.get());
  }

  VkDevice *Device::get_vk_device() const { return _vk_device.get(); }

  [[nodiscard]] std::unique_ptr<HAL::Queue> Device::get_queue(uint32_t queue_family_index, uint32_t queue_index) const
  {
    VkQueue vk_queue;
    vkGetDeviceQueue(*_vk_device, queue_family_index, queue_index, &vk_queue);
    return std::make_unique<Vulkan::Queue>(vk_queue);
  }
} // namespace Prism::HAL::Vulkan
