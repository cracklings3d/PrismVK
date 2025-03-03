// Created by cr on 2/19/25.

#include "Instance.h"
#include "../Instance.h"
#include "../Physical_device.h"
#include "Device.h"
#include "Error.h"
#include "Param_converters.h"
#include "Physical_device.h"

namespace Prism::HAL::Vulkan
{
  Instance::Instance(const Instance_create_info &instance_create_info)
  {
    VkInstanceCreateInfo vk_instance_create_info = convert(instance_create_info);

    VkInstance vk_instance;
    check_result(vkCreateInstance(&vk_instance_create_info, nullptr, &vk_instance), "Create_instance");

    _vk_instance = std::make_unique<VkInstance>(vk_instance);
  }

  Instance::~Instance()
  {
    vkDestroyInstance(*_vk_instance, nullptr);
    _vk_instance.reset();
  }

  VkInstance &Instance::get_vk_instance() const { return *_vk_instance; }

  std::shared_ptr<HAL::Physical_device> Instance::select_discrete_gpu() const
  {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(*_vk_instance, &device_count, nullptr);
    std::vector<VkPhysicalDevice> vk_physical_devices(device_count);
    vkEnumeratePhysicalDevices(*_vk_instance, &device_count, vk_physical_devices.data());

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
    vkEnumeratePhysicalDevices(*_vk_instance, &device_count, nullptr);
    std::vector<VkPhysicalDevice> vk_physical_devices(device_count);
    vkEnumeratePhysicalDevices(*_vk_instance, &device_count, vk_physical_devices.data());

    std::vector<std::shared_ptr<HAL::Physical_device>> physical_devices;
    for (const VkPhysicalDevice &vk_physical_device : vk_physical_devices)
    {
      physical_devices.push_back(std::make_shared<Physical_device>(vk_physical_device));
    }

    return physical_devices;
  }
} // namespace Prism::HAL::Vulkan
