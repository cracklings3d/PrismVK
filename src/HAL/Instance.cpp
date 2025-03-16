/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 21 2025      *
 *****************************/

#include "HAL/Instance.h"
#include "HAL/HAL.h"
#include "HAL/Vulkan/Instance.h"
#include "HAL/Vulkan/Window_Sdl2.h"

namespace Prism::HAL
{
  std::unique_ptr<Instance> create_instance(
      const Render_api &render_api, Instance_create_info &&create_info, std::vector<const char *> &&window_extensions)
  {
    switch (render_api)
    {
    case Render_api::Vulkan:
      return Vulkan::create_instance(std::move(create_info), std::move(window_extensions));
    default:
      throw std::runtime_error("Unsupported render API!");
    }
  }
} // namespace Prism::HAL
