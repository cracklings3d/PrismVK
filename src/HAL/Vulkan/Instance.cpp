/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 19 2025      *
 *****************************/

#include <vulkan/vulkan.h>

#include "HAL/Vulkan/Instance.h"

#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Physical_device.h"

#include <memory>

namespace Prism::HAL::Vulkan
{
  Instance::Instance(VkInstance &&vk_handle) { _vk_handle = std::make_unique<VkInstance>(vk_handle); }

  Instance::~Instance()
  {
    vkDestroyInstance(*_vk_handle, nullptr);
    _vk_handle.reset();
  }

  std::shared_ptr<HAL::Physical_device> Instance::select_discrete_gpu() const
  {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(*_vk_handle, &device_count, nullptr);
    std::vector<VkPhysicalDevice> vk_physical_devices(device_count);
    vkEnumeratePhysicalDevices(*_vk_handle, &device_count, vk_physical_devices.data());

    for (const VkPhysicalDevice &vk_physical_device : vk_physical_devices)
    {
      VkPhysicalDeviceProperties vk_physical_device_properties;
      vkGetPhysicalDeviceProperties(vk_physical_device, &vk_physical_device_properties);

      if (vk_physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
      {
        return std::make_shared<Physical_device>(vk_physical_device);
      }
    }
    return nullptr;
  }

  std::vector<std::shared_ptr<HAL::Physical_device>> Instance::enumerate_physical_devices() const
  {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(*_vk_handle, &device_count, nullptr);
    std::vector<VkPhysicalDevice> vk_physical_devices(device_count);
    vkEnumeratePhysicalDevices(*_vk_handle, &device_count, vk_physical_devices.data());

    std::vector<std::shared_ptr<HAL::Physical_device>> physical_devices;
    for (const VkPhysicalDevice &vk_physical_device : vk_physical_devices)
    {
      physical_devices.push_back(std::make_shared<Physical_device>(vk_physical_device));
    }

    return physical_devices;
  }

  std::pair<VkInstanceCreateInfo, VkApplicationInfo> convert(HAL::Instance_create_info &&instance_create_info)
  {
    VkApplicationInfo application_info{};
    application_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.pApplicationName   = instance_create_info.application_name.c_str();
    application_info.applicationVersion = instance_create_info.application_version;
    application_info.pEngineName        = instance_create_info.engine_name.c_str();
    application_info.engineVersion      = instance_create_info.engine_version;
    application_info.apiVersion         = VK_API_VERSION_1_4;

    VkInstanceCreateInfo vk_instance_create_info{};
    vk_instance_create_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vk_instance_create_info.pApplicationInfo = &application_info;

    return std::make_pair(std::move(vk_instance_create_info), std::move(application_info));
  }

  std::unique_ptr<Instance> create_instance(Instance_create_info &&hal, std::vector<const char *> &&window_extensions)
  {
    auto [vk_create_info, vk_application_info] = convert(std::move(hal));
    vk_create_info.pApplicationInfo            = &vk_application_info;

    vk_create_info.enabledExtensionCount   = window_extensions.size();
    vk_create_info.ppEnabledExtensionNames = window_extensions.data();

    VkInstance vk_instance;
    VkResult   result = vkCreateInstance(&vk_create_info, nullptr, &vk_instance);
    check_result(result, "Create_instance");

    return std::make_unique<Vulkan::Instance>(std::move(vk_instance));
  }
} // namespace Prism::HAL::Vulkan
