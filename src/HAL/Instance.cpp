// Created by cr on 2/21/25.

#include "Instance.h"
#include "Vulkan/Instance.h"


std::unique_ptr<Prism::HAL::Instance> Prism::HAL::Instance_factory::create_instance(
  const InstanceCreateInfo &create_info
, const Window *            window
)
{
  switch (Global_config::get().get_render_api())
  {
  case Render_api::Vulkan:
    return std::make_unique<Vulkan::Instance>(std::move(create_info), window);
  default:
    throw std::runtime_error("Unsupported render API!");
  }
}
