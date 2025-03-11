/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#include "HAL/Vulkan/Framebuffer.h"
#include "HAL/Vulkan/Image.h"
#include "HAL/Vulkan/Render_pass.h"
#include <vector>

namespace Prism::HAL::Vulkan
{
  Framebuffer::Framebuffer(VkFramebuffer framebuffer, VkDevice* device)
      : _vk_handle(std::make_unique<VkFramebuffer>(framebuffer))
      , _vk_device(device)
  {
  }

  Framebuffer::~Framebuffer()
  {
    if (_vk_handle != nullptr && _vk_device != nullptr)
    {
      vkDestroyFramebuffer(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  VkFramebufferCreateInfo convert(const HAL::Framebuffer_create_info& create_info)
  {
    std::vector<VkImageView> vk_attachments;
    vk_attachments.reserve(create_info.attachments.size());

    for (const auto& attachment : create_info.attachments)
    {
      auto vulkan_image_view = static_cast<Vulkan::Image_view*>(attachment);
      vk_attachments.push_back(*vulkan_image_view->get_vk_handle());
    }

    VkFramebufferCreateInfo vk_create_info{};
    vk_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    vk_create_info.renderPass = *static_cast<Vulkan::Render_pass*>(create_info.render_pass)->get_vk_handle();
    vk_create_info.attachmentCount = static_cast<uint32_t>(vk_attachments.size());
    vk_create_info.pAttachments = vk_attachments.data();
    vk_create_info.width = create_info.width;
    vk_create_info.height = create_info.height;
    vk_create_info.layers = create_info.layers;

    return vk_create_info;
  }
} 