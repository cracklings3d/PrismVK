/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 09 2025       *
 *****************************/

#pragma once

#include "HAL/Render_pass.h"

#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Render_pass final : public HAL::Render_pass
  {
  public:
    Render_pass(VkRenderPass &&vk_render_pass, VkDevice *vk_device)
        : _vk_handle(std::make_unique<VkRenderPass>(std::move(vk_render_pass))), _vk_device(vk_device)
    {}

    ~Render_pass() override;

    [[nodiscard]] VkRenderPass *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkRenderPass> _vk_handle = nullptr;
    VkDevice                     *_vk_device = nullptr;
  };

  VkAttachmentDescription convert(const HAL::Attachment_description &attachment_description);
  VkAttachmentReference   convert(const HAL::Attachment_reference &attachment_reference);
  VkSubpassDescription    convert(const HAL::Subpass_description &subpass_description);
  VkRenderPassCreateInfo  convert(const HAL::Render_pass_create_info &render_pass_create_info);
} // namespace Prism::HAL::Vulkan
