#pragma once

#include <vulkan/vulkan_core.h>

#include "../Physical_device.h"

namespace Prism::HAL
{
  struct Extent;

  struct Instance_create_info;
  struct Device_create_info;
  struct Swapchain_create_info;
  struct Image_view_create_info;
  struct Attachment_description;
  struct Attachment_reference;
  struct Subpass_description;
  struct Render_pass_create_info;

  enum class Image_format;
  enum class Color_space;
  enum class Image_usage;
  enum class Image_sharing_mode;
  enum class Image_present_mode;
} // namespace Prism::HAL

namespace Prism::HAL::Vulkan
{
  /************************* HAL to Vulkan *************************/
  VkInstanceCreateInfo     convert(const HAL::Instance_create_info &instance_create_info);
  VkDeviceCreateInfo       convert(const HAL::Device_create_info &device_create_info);
  VkSwapchainCreateInfoKHR convert(const HAL::Swapchain_create_info &swapchain_create_info);
  VkFormat                 convert(const HAL::Image_format &image_format);
  VkColorSpaceKHR          convert(const HAL::Color_space &image_color_space);
  VkExtent2D               convert(const HAL::Extent &image_extent);
  VkImageUsageFlags        convert(const HAL::Image_usage &image_usage);
  VkSharingMode            convert(const HAL::Image_sharing_mode &image_sharing_mode);
  VkPresentModeKHR         convert(const HAL::Image_present_mode &image_present_mode);
  VkImageViewCreateInfo    convert(const HAL::Image_view_create_info &image_view_create_info);
  VkAttachmentDescription  convert(const HAL::Attachment_description &attachment_description);
  VkAttachmentReference    convert(const HAL::Attachment_reference &attachment_reference);
  VkSubpassDescription     convert(const HAL::Subpass_description &subpass_description);
  VkRenderPassCreateInfo   convert(const HAL::Render_pass_create_info &render_pass_create_info);

  /************************* Vulkan to HAL *************************/
  Physical_device_properties convert(const VkPhysicalDeviceProperties &vk_physical_device_properties);

} // namespace Prism::HAL::Vulkan
