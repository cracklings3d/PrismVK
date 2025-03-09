/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 26 2025       *
 *****************************/

#include <memory>

#include "HAL/Vulkan/Descriptor.h"
#include "HAL/Vulkan/Device.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Param_converters.h"
#include "HAL/Vulkan/Pipeline.h"
#include "HAL/Vulkan/Queue.h"
#include "HAL/Vulkan/Render_pass.h"
#include "HAL/Vulkan/Shader.h"
#include "HAL/Vulkan/Swapchain.h"

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

  std::unique_ptr<HAL::Descriptor_set_layout>
  Device::create_descriptor_set_layout(const HAL::Descriptor_set_layout_create_info &create_info) const
  {
    VkDescriptorSetLayoutCreateInfo vk_create_info = convert(create_info);
    VkDescriptorSetLayout           vk_descriptor_set_layout;

    VkResult result = vkCreateDescriptorSetLayout(*_vk_device, &vk_create_info, nullptr, &vk_descriptor_set_layout);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Descriptor_set_layout>(std::move(vk_descriptor_set_layout), _vk_device.get());
  }

  std::unique_ptr<HAL::Pipeline_layout>
  Device::create_pipeline_layout(const HAL::Pipeline_layout_create_info &create_info) const
  {
    VkPipelineLayoutCreateInfo vk_create_info = convert(create_info);
    VkPipelineLayout           vk_pipeline_layout;

    VkResult result = vkCreatePipelineLayout(*_vk_device, &vk_create_info, nullptr, &vk_pipeline_layout);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Pipeline_layout>(std::move(vk_pipeline_layout), _vk_device.get());
  }

  std::unique_ptr<HAL::Pipeline>
  Device::create_graphics_pipeline(const HAL::Graphics_pipeline_create_info &create_info) const
  {
    VkGraphicsPipelineCreateInfo vk_create_info = convert(create_info);
    VkPipeline                   vk_pipeline;

    VkResult result = vkCreateGraphicsPipelines(*_vk_device, nullptr, 1, &vk_create_info, nullptr, &vk_pipeline);
    check_result(result, __func__);

    return std::make_unique<Vulkan::Pipeline>(std::move(vk_pipeline), _vk_device.get());
  }

  void Device::wait_idle() const { vkDeviceWaitIdle(*_vk_device); }

  VkDevice *Device::get_vk_handle() const { return _vk_device.get(); }

  [[nodiscard]] std::unique_ptr<HAL::Queue> Device::get_queue(uint32_t queue_family_index, uint32_t queue_index) const
  {
    VkQueue vk_queue;
    vkGetDeviceQueue(*_vk_device, queue_family_index, queue_index, &vk_queue);
    return std::make_unique<Vulkan::Queue>(vk_queue);
  }

  VkDeviceCreateInfo convert(const HAL::Device_create_info &device_create_info)
  {
    VkDeviceCreateInfo vk_device_create_info{};

    auto vk_queue_create_infos
        = Prism::Util::vector_convert<VkDeviceQueueCreateInfo>(device_create_info.queue_create_infos);

    vk_device_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    vk_device_create_info.enabledExtensionCount   = device_create_info.required_extensions.size();
    vk_device_create_info.ppEnabledExtensionNames = device_create_info.required_extensions.data();
    vk_device_create_info.pQueueCreateInfos       = vk_queue_create_infos.data();
    vk_device_create_info.queueCreateInfoCount    = vk_queue_create_infos.size();

    return vk_device_create_info;
  }

  VkDeviceQueueCreateInfo convert(const HAL::Device_queue_create_info &device_queue_create_info)
  {
    VkDeviceQueueCreateInfo vk_device_queue_create_info{};

    vk_device_queue_create_info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vk_device_queue_create_info.queueFamilyIndex = device_queue_create_info.queue_family_index;
    vk_device_queue_create_info.queueCount       = device_queue_create_info.queue_priorities->size();
    vk_device_queue_create_info.pQueuePriorities = device_queue_create_info.queue_priorities->data();

    return vk_device_queue_create_info;
  }
} // namespace Prism::HAL::Vulkan
