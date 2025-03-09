// Created by cr on 2/21/25.

#pragma once

#include <memory>
#include <vector>

#include "HAL.h"

namespace Prism::HAL
{
  class Surface;
  class Instance;

  class Window
  {
  public:
    virtual ~Window() = default;

    virtual void request_close() = 0;

    virtual void set_title(const std::string &title) = 0;
    virtual void resize(int width, int height)       = 0;
    virtual void set_position(int x, int y)          = 0;
    virtual void set_fullscreen(bool fullscreen)     = 0;

    virtual bool should_close() = 0;
    virtual void poll_event()   = 0;

    virtual std::vector<const char *> get_required_extensions() const = 0;

    virtual std::unique_ptr<Surface> create_surface(Instance &instance) = 0;
  };

  std::unique_ptr<Window> create_window(const Render_api &render_api);
} // namespace Prism::HAL
