#include "Param_converters.h"

#include "../Device.h"
#include "../Image_view.h"
#include "../Instance.h"
#include "../Swapchain.h"
#include "Image.h"
#include "Surface.h"

namespace Prism::HAL::Vulkan
{
  /*****************************************************************/
  /************************* HAL to Vulkan *************************/
  /*****************************************************************/

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

  VkSwapchainCreateInfoKHR convert(const HAL::Swapchain_create_info &swapchain_create_info)
  {
    VkSwapchainCreateInfoKHR vk_swapchain_create_info{};

    vk_swapchain_create_info.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    vk_swapchain_create_info.surface          = *((Vulkan::Surface &)swapchain_create_info.surface).get_vk_surface();
    vk_swapchain_create_info.minImageCount    = swapchain_create_info.min_image_count;
    vk_swapchain_create_info.imageFormat      = convert(swapchain_create_info.image_format);
    vk_swapchain_create_info.imageColorSpace  = convert(swapchain_create_info.image_color_space);
    vk_swapchain_create_info.imageExtent      = convert(swapchain_create_info.image_extent);
    vk_swapchain_create_info.imageArrayLayers = swapchain_create_info.image_array_layers;
    vk_swapchain_create_info.imageUsage       = convert(swapchain_create_info.image_usage);
    vk_swapchain_create_info.imageSharingMode = convert(swapchain_create_info.image_sharing_mode);
    vk_swapchain_create_info.presentMode      = convert(swapchain_create_info.image_present_mode);

    return vk_swapchain_create_info;
  }

  VkFormat convert(const HAL::Image_format &image_format)
  {
    switch (image_format)
    {
    case HAL::Image_format::R8G8B8A8_UNORM:
      return VK_FORMAT_R8G8B8A8_UNORM;
    case HAL::Image_format::B8G8R8A8_UNORM:
      return VK_FORMAT_B8G8R8A8_UNORM;
    case HAL::Image_format::R8G8B8A8_SRGB:
      return VK_FORMAT_R8G8B8A8_SRGB;
    case HAL::Image_format::B8G8R8A8_SRGB:
      return VK_FORMAT_B8G8R8A8_SRGB;
    default:
      throw std::runtime_error("Unsupported image format");
    }
  }

  VkColorSpaceKHR convert(const HAL::Color_space &image_color_space)
  {
    switch (image_color_space)
    {
    case HAL::Color_space::SRGB_NONLINEAR:
      return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    default:
      throw std::runtime_error("Unsupported image color space");
    }
  }

  VkExtent2D convert(const HAL::Extent &image_extent) { return VkExtent2D{image_extent.width, image_extent.height}; }

  VkImageUsageFlags convert(const HAL::Image_usage &image_usage)
  {
    switch (image_usage)
    {
    case HAL::Image_usage::COLOR_ATTACHMENT:
      return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    default:
      throw std::runtime_error("Unsupported image usage");
    }
  }

  VkSharingMode convert(const HAL::Image_sharing_mode &image_sharing_mode)
  {
    switch (image_sharing_mode)
    {
    case HAL::Image_sharing_mode::EXCLUSIVE:
      return VK_SHARING_MODE_EXCLUSIVE;
    default:
      throw std::runtime_error("Unsupported image sharing mode");
    }
  }

  VkPresentModeKHR convert(const HAL::Image_present_mode &image_present_mode)
  {
    switch (image_present_mode)
    {
    case HAL::Image_present_mode::FIFO:
      return VK_PRESENT_MODE_FIFO_KHR;
    default:
      throw std::runtime_error("Unsupported image present mode");
    }
  }

  VkImageViewCreateInfo convert(const HAL::Image_view_create_info &hal)
  {
    VkImageViewCreateInfo vk           = {};
    vk.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vk.image                           = *((Vulkan::Image &)hal.image).get_vk_image();
    vk.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
    vk.format                          = convert(hal.image_format);
    vk.subresourceRange                = {};
    vk.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    vk.subresourceRange.baseMipLevel   = 0;
    vk.subresourceRange.levelCount     = 1;
    vk.subresourceRange.baseArrayLayer = 0;
    vk.subresourceRange.layerCount     = 1;

    return vk;
  }

  /*****************************************************************/
  /************************* Vulkan to HAL *************************/
  /*****************************************************************/

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
