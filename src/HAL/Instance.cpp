/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 21 2025      *
 *****************************/

#include "HAL/Instance.h"
#include "HAL/HAL.h"
#include "HAL/Vulkan/Instance.h"

namespace Prism::HAL
{
  std::unique_ptr<Instance> create_instance(const Instance_create_info &create_info)
  {
    switch (Global_config::get().get_render_api())
    {
    case Render_api::Vulkan:
      return Vulkan::create_instance(create_info);
    default:
      throw std::runtime_error("Unsupported render API!");
    }
  }
} // namespace Prism::HAL
