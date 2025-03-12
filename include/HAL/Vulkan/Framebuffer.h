/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include "HAL/Framebuffer.h"
#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Framebuffer : public HAL::Framebuffer
  {
  public:
    explicit Framebuffer(VkFramebuffer framebuffer, VkDevice *device);
    ~Framebuffer() override;

    [[nodiscard]] VkFramebuffer *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkFramebuffer> _vk_handle;
    VkDevice                      *_vk_device;
  };

  VkFramebufferCreateInfo convert(const HAL::Framebuffer_create_info &create_info);
} // namespace Prism::HAL::Vulkan
