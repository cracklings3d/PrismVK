// Created by cr on 2/19/25.

#include "Window_Sdl2.h"

#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include "Instance.h"
#include "Surface.h"
#include "../Instance.h"


Prism::HAL::Vulkan::Sdl2_manager &Prism::HAL::Vulkan::Sdl2_manager::get()
{
  static Sdl2_manager instance;
  return instance;
}

Prism::HAL::Vulkan::Sdl2_manager::Sdl2_manager()
{
  assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0);
}

Prism::HAL::Vulkan::Sdl2_manager::~Sdl2_manager()
{
  SDL_Quit();
}

Prism::HAL::Vulkan::Window_Sdl2::Window_Sdl2()
{
  assert(SDL_WasInit(SDL_INIT_VIDEO) == SDL_TRUE);
  assert(SDL_WasInit(SDL_INIT_EVENTS) == SDL_TRUE);

  _window = SDL_CreateWindow(
    "Vulkan Triangle"
  , SDL_WINDOWPOS_UNDEFINED
  , SDL_WINDOWPOS_UNDEFINED
  , 800
  , 600
  , SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
  );
  assert(_window);
}

Prism::HAL::Vulkan::Window_Sdl2::~Window_Sdl2()
{
  if (_window)
  {
    SDL_DestroyWindow(_window);
  }
}

void Prism::HAL::Vulkan::Window_Sdl2::request_close()
{
  _should_close = true;
}

void Prism::HAL::Vulkan::Window_Sdl2::set_title(const std::string &title)
{
  SDL_SetWindowTitle(_window, title.c_str());
}

void Prism::HAL::Vulkan::Window_Sdl2::resize(int width, int height)
{
  SDL_SetWindowSize(_window, width, height);
}

void Prism::HAL::Vulkan::Window_Sdl2::set_position(int x, int y)
{
  SDL_SetWindowPosition(_window, x, y);
}

void Prism::HAL::Vulkan::Window_Sdl2::set_fullscreen(bool fullscreen)
{
  SDL_SetWindowFullscreen(_window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

bool Prism::HAL::Vulkan::Window_Sdl2::should_close()
{
  return _should_close;
}

void Prism::HAL::Vulkan::Window_Sdl2::poll_event()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      _should_close = true;
    default:
      break;
    }
  }
}

std::vector<const char *> Prism::HAL::Vulkan::Window_Sdl2::get_required_extensions() const
{
  unsigned int extension_count = 0;
  SDL_Vulkan_GetInstanceExtensions(_window, &extension_count, nullptr);
  std::vector<const char *> extensions(extension_count);
  SDL_Vulkan_GetInstanceExtensions(_window, &extension_count, extensions.data());
  return extensions;
}

std::unique_ptr<Prism::HAL::Surface> Prism::HAL::Vulkan::Window_Sdl2::create_surface(HAL::Instance &instance)
{
  VkSurfaceKHR surface;
  auto         vulkan_instance = static_cast<Vulkan::Instance&>(instance);

  assert(SDL_Vulkan_CreateSurface(_window, instance, &surface) == SDL_TRUE);
  return {};
}
