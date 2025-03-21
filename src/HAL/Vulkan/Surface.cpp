/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 22 2025       *
 *****************************/

#include "HAL/Vulkan/Surface.h"
#include "HAL/Vulkan/Instance.h" // Need Vulkan Instance

#include <SDL2/SDL_vulkan.h>

namespace Prism::HAL::Vulkan
{
  Surface::Surface(VkSurfaceKHR &&vk_surface, VkInstance *vk_instance)
  {
    _vk_surface  = std::make_unique<VkSurfaceKHR>(vk_surface);
    _vk_instance = vk_instance;
  }

  Surface::~Surface()
  {
    if (_vk_surface != nullptr)
    {
      vkDestroySurfaceKHR(*_vk_instance, *_vk_surface, nullptr);
      _vk_surface = nullptr;
    }
  }

  VkSurfaceKHR *Surface::get_vk_surface() const { return _vk_surface.get(); }
} // namespace Prism::HAL::Vulkan
