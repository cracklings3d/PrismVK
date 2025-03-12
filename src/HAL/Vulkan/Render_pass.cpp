/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 05 2025       *
 *****************************/

#include "HAL/Vulkan/Render_pass.h"

#include "HAL/Vulkan/Common.h"

namespace Prism::HAL::Vulkan
{
  Render_pass::~Render_pass()
  {
    if (_vk_handle != nullptr)
    {
      vkDestroyRenderPass(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  VkAttachmentDescription convert(const HAL::Attachment_description &hal)
  {
    VkAttachmentDescription vk{};

    vk.format         = convert_enum<VkFormat>(hal.format);
    vk.samples        = convert_enum<VkSampleCountFlagBits>(hal.samples);
    vk.loadOp         = convert_enum<VkAttachmentLoadOp>(hal.load_op);
    vk.storeOp        = convert_enum<VkAttachmentStoreOp>(hal.store_op);
    vk.stencilLoadOp  = convert_enum<VkAttachmentLoadOp>(hal.stencil_load_op);
    vk.stencilStoreOp = convert_enum<VkAttachmentStoreOp>(hal.stencil_store_op);
    vk.initialLayout  = convert_enum<VkImageLayout>(hal.initial_layout);
    vk.finalLayout    = convert_enum<VkImageLayout>(hal.final_layout);

    return vk;
  }

  VkAttachmentReference convert(const HAL::Attachment_reference &hal)
  {
    VkAttachmentReference vk{};

    vk.attachment = hal.attachment;
    vk.layout     = convert_enum<VkImageLayout>(hal.layout);

    return vk;
  }

  VkSubpassDescription convert(const HAL::Subpass_description &hal)
  {
    VkSubpassDescription vk{};

    std::vector<VkAttachmentReference> color_attachments;
    for (const auto &attachment : hal.color_attachments)
    {
      color_attachments.push_back(convert(attachment));
    }

    vk.pipelineBindPoint    = convert_enum<VkPipelineBindPoint>(hal.pipeline_bind_point);
    vk.colorAttachmentCount = color_attachments.size();
    vk.pColorAttachments    = color_attachments.data();

    return vk;
  }

  VkRenderPassCreateInfo convert(const HAL::Render_pass_create_info &hal)
  {
    std::vector<VkAttachmentDescription> attachments;
    for (const auto &attachment : hal.attachments)
    {
      attachments.push_back(convert(attachment));
    }

    std::vector<VkSubpassDescription> subpasses;
    for (const auto &subpass : hal.subpasses)
    {
      subpasses.push_back(convert(subpass));
    }

    VkRenderPassCreateInfo vk{};

    vk.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    vk.attachmentCount = attachments.size();
    vk.pAttachments    = attachments.data();
    vk.subpassCount    = subpasses.size();
    vk.pSubpasses      = subpasses.data();

    return vk;
  }

} // namespace Prism::HAL::Vulkan
