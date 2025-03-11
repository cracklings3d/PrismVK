// Created by cr on 2/19/25.

#include "HAL/Vulkan/Window_Sdl2.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <cassert>

#include "HAL/Viewport.h"
#include "HAL/Vulkan/Instance.h"
#include "HAL/Vulkan/Surface.h"

namespace Prism::HAL
{
  Vulkan::Sdl2_manager &Vulkan::Sdl2_manager::get()
  {
    static Sdl2_manager instance;
    return instance;
  }

  Vulkan::Sdl2_manager::Sdl2_manager() { assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0); }

  Vulkan::Sdl2_manager::~Sdl2_manager() { SDL_Quit(); }

  Vulkan::Window_Sdl2::Window_Sdl2(Extent2D extent) : _extent(extent)
  {
    assert(SDL_WasInit(SDL_INIT_VIDEO) == SDL_TRUE);
    assert(SDL_WasInit(SDL_INIT_EVENTS) == SDL_TRUE);

    _window = SDL_CreateWindow(
        "Vulkan Triangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _extent.width, _extent.height,
        SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    assert(_window);
  }

  Vulkan::Window_Sdl2::~Window_Sdl2()
  {
    if (_window)
    {
      SDL_DestroyWindow(_window);
    }
  }

  void Vulkan::Window_Sdl2::request_close() { _should_close = true; }

  void Vulkan::Window_Sdl2::set_title(const std::string &title) { SDL_SetWindowTitle(_window, title.c_str()); }

  void Vulkan::Window_Sdl2::resize(int width, int height) { SDL_SetWindowSize(_window, width, height); }

  void Vulkan::Window_Sdl2::set_position(int x, int y) { SDL_SetWindowPosition(_window, x, y); }

  void Vulkan::Window_Sdl2::set_fullscreen(bool fullscreen)
  {
    SDL_SetWindowFullscreen(_window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
  }

  bool Vulkan::Window_Sdl2::should_close() { return _should_close; }

  void Vulkan::Window_Sdl2::poll_event()
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        _should_close = true;
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
          _extent = {(uint32_t)event.window.data1, (uint32_t)event.window.data2};
        }
        break;
      default:
        break;
      }
    }
  }

  Extent2D Vulkan::Window_Sdl2::get_extent() const { return _extent; }

  std::vector<const char *> Vulkan::Window_Sdl2::get_required_extensions() const
  {
    unsigned int extension_count = 0;
    SDL_Vulkan_GetInstanceExtensions(_window, &extension_count, nullptr);
    std::vector<const char *> extensions(extension_count);
    SDL_Vulkan_GetInstanceExtensions(_window, &extension_count, extensions.data());
    return extensions;
  }

  std::unique_ptr<HAL::Surface> Vulkan::Window_Sdl2::create_surface(HAL::Instance *instance)
  {
    VkSurfaceKHR      surface;
    Vulkan::Instance *vulkan_instance = static_cast<Vulkan::Instance *>(instance);
    assert(SDL_Vulkan_CreateSurface(_window, *vulkan_instance->get_vk_handle(), &surface) == SDL_TRUE);
    return std::make_unique<Vulkan::Surface>(std::move(surface), vulkan_instance->get_vk_handle());
  }
} // namespace Prism::HAL
