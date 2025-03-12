/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 22 2025       *
 *****************************/

#pragma once

#include "HAL/Surface.h"

#include <vulkan/vulkan_core.h>

namespace Prism::HAL::Vulkan
{
  class Surface final : public HAL::Surface
  {
  public:
    Surface(VkSurfaceKHR &&vk_surface, VkInstance *vk_instance);
    ~Surface() override;

    [[nodiscard]] VkSurfaceKHR *get_vk_surface() const;

  private:
    std::unique_ptr<VkSurfaceKHR> _vk_surface = nullptr;
    VkInstance *                 _vk_instance = nullptr;
  };
} // namespace Prism::HAL::Vulkan
