/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 19 2025      *
 *****************************/

#include "HAL/Vulkan/Instance.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Param_converters.h"
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

  VkInstance *Instance::get_vk_handle() const { return _vk_handle.get(); }

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

  VkInstanceCreateInfo convert(const HAL::Instance_create_info &instance_create_info)
  {
    VkApplicationInfo application_info{};
    application_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.pApplicationName   = instance_create_info.application_name.c_str();
    application_info.applicationVersion = instance_create_info.application_version;
    application_info.pEngineName        = instance_create_info.engine_name.c_str();
    application_info.engineVersion      = instance_create_info.engine_version;

    VkInstanceCreateInfo vk_instance_create_info{};
    vk_instance_create_info.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vk_instance_create_info.pApplicationInfo        = &application_info;
    vk_instance_create_info.enabledExtensionCount   = instance_create_info.required_extensions.size();
    vk_instance_create_info.ppEnabledExtensionNames = instance_create_info.required_extensions.data();
    return vk_instance_create_info;
  }

  std::unique_ptr<Instance> create_instance(const Instance_create_info &create_info)
  {
    VkInstanceCreateInfo vk_instance_create_info = convert(create_info);
    VkInstance           vk_instance;
    VkResult             result = vkCreateInstance(&vk_instance_create_info, nullptr, &vk_instance);
    check_result(result, "Create_instance");

    return std::make_unique<Vulkan::Instance>(std::move(vk_instance));
  }
} // namespace Prism::HAL::Vulkan
