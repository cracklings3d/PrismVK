// Created by cr on 2/19/25.

#pragma once

#define SDL_MAIN_HANDLED
#include <string>
#include <vector>
#include <SDL2/SDL_video.h>

#include "Surface.h"
#include "../HAL.h"
#include "../Window.h"


namespace Prism::HAL::Vulkan
{
  class Instance;

  class Sdl2_manager final
  {
  public:
    static Sdl2_manager &get();

  private:
    Sdl2_manager();
    ~Sdl2_manager();
  };


  class Window_Sdl2 final : public Window
  {
  public:
    Window_Sdl2();
    ~Window_Sdl2() override;

    void request_close() override;

    void set_title(const std::string &title) override;
    void resize(int width, int height) override;
    void set_position(int x, int y) override;
    void set_fullscreen(bool fullscreen) override;

    bool should_close() override;
    void poll_event() override;

    std::vector<const char *>     get_required_extensions() const override;
    std::unique_ptr<HAL::Surface> create_surface(HAL::Instance &instance) override;

  private:
    SDL_Window *_window = nullptr;

    Instance *_instance = nullptr;

    bool _should_close = false;

    Sdl2_manager &_sdl2_manager = Sdl2_manager::get();
  };
} // Prism::HAL::Vulkan
