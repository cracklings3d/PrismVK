// Created by cr on 2/21/25.

#include "Window.h"
#include "Vulkan/Window_Sdl2.h"

namespace Prism::HAL
{
  std::unique_ptr<Window> create_window(const Render_api &render_api)
  {
    switch (render_api)
    {
    case Render_api::Vulkan:
      return std::make_unique<Vulkan::Window_Sdl2>();
    default:
      throw std::runtime_error("Unsupported render API!");
    }
  }
} // namespace Prism::HAL
