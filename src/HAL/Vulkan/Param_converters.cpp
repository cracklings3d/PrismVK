#include "Param_converters.h"

#include "../Device.h"
#include "../Instance.h"

namespace Prism::HAL::Vulkan
{
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

  VkDeviceCreateInfo convert(const HAL::Device_create_info &device_create_info)
  {
    VkDeviceCreateInfo vk_device_create_info{};
    vk_device_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    vk_device_create_info.enabledExtensionCount   = device_create_info.required_extensions.size();
    vk_device_create_info.ppEnabledExtensionNames = device_create_info.required_extensions.data();
    return vk_device_create_info;
  }

  Physical_device_properties convert(const VkPhysicalDeviceProperties &vk_physical_device_properties)
  {
    Physical_device_properties physical_device_properties{};

    physical_device_properties.api_version    = vk_physical_device_properties.apiVersion;
    physical_device_properties.driver_version = vk_physical_device_properties.driverVersion;
    physical_device_properties.vendor_id      = vk_physical_device_properties.vendorID;
    physical_device_properties.device_id      = vk_physical_device_properties.deviceID;
    physical_device_properties.device_type    = vk_physical_device_properties.deviceType;
    physical_device_properties.device_name    = vk_physical_device_properties.deviceName;

    return physical_device_properties;
  }
} // namespace Prism::HAL::Vulkan
