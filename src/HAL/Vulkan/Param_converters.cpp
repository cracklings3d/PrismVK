#include "HAL/Vulkan/Param_converters.h"

#include "HAL/Attachment_description.h"
#include "HAL/Device.h"
#include "HAL/Instance.h"
#include "HAL/Render_pass.h"
#include "HAL/Swapchain.h"

#include "HAL/Vulkan/Image.h"
#include "HAL/Vulkan/Pipeline.h"
#include "HAL/Vulkan/Shader.h"
#include "HAL/Vulkan/Surface.h"
#include "HAL/Vulkan/Viewport.h"

namespace Prism::HAL::Vulkan
{
  /*****************************************************************/
  /************************* HAL to Vulkan *************************/
  /*****************************************************************/

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

  VkPolygonMode convert(const HAL::Polygon_mode &mode)
  {
    switch (mode)
    {
    case HAL::Polygon_mode::Fill:
      return VK_POLYGON_MODE_FILL;
    case HAL::Polygon_mode::Line:
      return VK_POLYGON_MODE_LINE;
    case HAL::Polygon_mode::Point:
      return VK_POLYGON_MODE_POINT;
    default:
      throw std::runtime_error("Unsupported polygon mode");
    }
  }

  VkCullModeFlags convert(const HAL::Cull_mode &mode)
  {
    switch (mode)
    {
    case HAL::Cull_mode::None:
      return VK_CULL_MODE_NONE;
    case HAL::Cull_mode::Back:
      return VK_CULL_MODE_BACK_BIT;
    case HAL::Cull_mode::Front:
      return VK_CULL_MODE_FRONT_BIT;
    case HAL::Cull_mode::Front_and_back:
      return VK_CULL_MODE_FRONT_AND_BACK;
    default:
      throw std::runtime_error("Unsupported cull mode");
    }
  }

  VkFrontFace convert(const HAL::Front_face &face)
  {
    switch (face)
    {
    case HAL::Front_face::Clockwise:
      return VK_FRONT_FACE_CLOCKWISE;
    case HAL::Front_face::Counter_clockwise:
      return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    default:
      throw std::runtime_error("Unsupported front face");
    }
  }

  VkSampleCountFlagBits convert(const HAL::Sample_count &samples)
  {
    switch (samples)
    {
    case HAL::Sample_count::Count_1:
      return VK_SAMPLE_COUNT_1_BIT;
    case HAL::Sample_count::Count_2:
      return VK_SAMPLE_COUNT_2_BIT;
    case HAL::Sample_count::Count_4:
      return VK_SAMPLE_COUNT_4_BIT;
    case HAL::Sample_count::Count_8:
      return VK_SAMPLE_COUNT_8_BIT;
    case HAL::Sample_count::Count_16:
      return VK_SAMPLE_COUNT_16_BIT;
    default:
      throw std::runtime_error("Unsupported sample count");
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
    vk.image                           = *((Vulkan::Image &)hal.image).get_vk_handle();
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

  VkAttachmentLoadOp convert(const HAL::Attachment_load_op &load_op)
  {
    switch (load_op)
    {
    case HAL::Attachment_load_op::Load:
      return VK_ATTACHMENT_LOAD_OP_LOAD;
    case HAL::Attachment_load_op::Clear:
      return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case HAL::Attachment_load_op::Dont_care:
      return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    default:
      throw std::runtime_error("Unsupported attachment load op");
    }
  }

  VkAttachmentStoreOp convert(const HAL::Attachment_store_op &store_op)
  {
    switch (store_op)
    {
    case HAL::Attachment_store_op::Store:
      return VK_ATTACHMENT_STORE_OP_STORE;
    case HAL::Attachment_store_op::Dont_care:
      return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    default:
      throw std::runtime_error("Unsupported attachment store op");
    }
  }

  VkImageLayout convert(const HAL::Image_layout &layout)
  {
    switch (layout)
    {
    case HAL::Image_layout::Undefined:
      return VK_IMAGE_LAYOUT_UNDEFINED;
    case HAL::Image_layout::Color_attachment_optimal:
      return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    case HAL::Image_layout::Present_src:
      return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    default:
      throw std::runtime_error("Unsupported image layout");
    }
  }

  VkAttachmentDescription convert(const HAL::Attachment_description &attachment_description)
  {
    VkAttachmentDescription vk_attachment_description{};
    vk_attachment_description.format         = convert(attachment_description.format);
    vk_attachment_description.loadOp         = convert(attachment_description.load_op);
    vk_attachment_description.storeOp        = convert(attachment_description.store_op);
    vk_attachment_description.stencilLoadOp  = convert(attachment_description.stencil_load_op);
    vk_attachment_description.stencilStoreOp = convert(attachment_description.stencil_store_op);
    vk_attachment_description.initialLayout  = convert(attachment_description.initial_layout);
    vk_attachment_description.finalLayout    = convert(attachment_description.final_layout);
    return vk_attachment_description;
  }

  VkAttachmentReference convert(const HAL::Attachment_reference &attachment_reference)
  {
    VkAttachmentReference vk_attachment_reference{};
    vk_attachment_reference.attachment = attachment_reference.attachment;
    vk_attachment_reference.layout     = convert(attachment_reference.layout);
    return vk_attachment_reference;
  }

  VkSubpassDescription convert(const HAL::Subpass_description &subpass_description)
  {
    VkSubpassDescription vk_subpass_description{};
    vk_subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    std::vector<VkAttachmentReference> color_attachments;
    for (const auto &attachment : subpass_description.color_attachments)
    {
      color_attachments.push_back(convert(attachment));
    }

    vk_subpass_description.colorAttachmentCount = color_attachments.size();
    vk_subpass_description.pColorAttachments    = color_attachments.data();

    return vk_subpass_description;
  }

  VkRenderPassCreateInfo convert(const HAL::Render_pass_create_info &render_pass_create_info)
  {
    std::vector<VkAttachmentDescription> attachments;
    for (const auto &attachment : render_pass_create_info.attachments)
    {
      attachments.push_back(convert(attachment));
    }

    std::vector<VkSubpassDescription> subpasses;
    for (const auto &subpass : render_pass_create_info.subpasses)
    {
      subpasses.push_back(convert(subpass));
    }

    VkRenderPassCreateInfo vk_render_pass_create_info{};
    vk_render_pass_create_info.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    vk_render_pass_create_info.attachmentCount = attachments.size();
    vk_render_pass_create_info.pAttachments    = attachments.data();
    vk_render_pass_create_info.subpassCount    = subpasses.size();
    vk_render_pass_create_info.pSubpasses      = subpasses.data();

    return vk_render_pass_create_info;
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
