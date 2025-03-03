// Created by cr on 2/21/25.

#include "Instance.h"
#include "Vulkan/Instance.h"

namespace Prism::HAL
{
  std::unique_ptr<Instance> create_instance(const Instance_create_info &create_info)
  {
    switch (Global_config::get().get_render_api())
    {
    case Render_api::Vulkan:
      return std::make_unique<Vulkan::Instance>(create_info);
    default:
      throw std::runtime_error("Unsupported render API!");
    }
  }
} // Prism::HAL
