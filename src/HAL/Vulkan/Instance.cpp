// Created by cr on 2/19/25.

#include "Instance.h"
#include "../Instance.h"


Prism::HAL::Vulkan::Instance::Instance(
  const InstanceCreateInfo &&instance_create_info
, const Window *             window
)
{
  VkApplicationInfo vk_application_info;

  vk_application_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  vk_application_info.pApplicationName   = instance_create_info.application_name.c_str();
  vk_application_info.applicationVersion = instance_create_info.application_version;
  vk_application_info.pEngineName        = instance_create_info.engine_name.c_str();
  vk_application_info.engineVersion      = instance_create_info.engine_version;
  vk_application_info.apiVersion         = VK_API_VERSION_1_4;

  std::vector<const char *> Extensions;
  {
    Extensions = window->get_required_extensions();
  }

  VkInstanceCreateInfo vk_instance_create_info;

  vk_instance_create_info.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  vk_instance_create_info.pApplicationInfo        = &vk_application_info;
  vk_instance_create_info.enabledExtensionCount   = Extensions.size();
  vk_instance_create_info.ppEnabledExtensionNames = Extensions.data();

  switch (vkCreateInstance(&vk_instance_create_info, nullptr, &_vk_instance))
  {
  case VK_ERROR_OUT_OF_HOST_MEMORY:
    throw std::runtime_error("Failed to create Vulkan instance: Out of host memory!");
  case VK_ERROR_OUT_OF_DEVICE_MEMORY:
    throw std::runtime_error("Failed to create Vulkan instance: Out of device memory!");
  case VK_ERROR_INITIALIZATION_FAILED:
    throw std::runtime_error("Failed to create Vulkan instance: Initialization failed!");
  case VK_ERROR_LAYER_NOT_PRESENT:
    throw std::runtime_error("Failed to create Vulkan instance: Layer not present!");
  case VK_ERROR_EXTENSION_NOT_PRESENT:
    throw std::runtime_error("Failed to create Vulkan instance: Extension not present!");
  case VK_ERROR_INCOMPATIBLE_DRIVER:
    throw std::runtime_error("Failed to create Vulkan instance: Incompatible driver!");
  case VK_SUCCESS:
    return;
  default:
    throw std::runtime_error("Failed to create Vulkan instance: Unknown error!");
  }
}

Prism::HAL::Vulkan::Instance::~Instance()
{
  vkDestroyInstance(_vk_instance, nullptr);
}

Prism::HAL::Device Prism::HAL::Vulkan::Instance::create_device() {}
VkInstance         Prism::HAL::Vulkan::Instance::get_vk_instance()
{
  return _vk_instance;
}
