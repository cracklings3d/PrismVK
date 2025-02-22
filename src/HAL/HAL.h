// Created by cr on 2/19/25.

#pragma once


namespace Prism::HAL
{
  enum class Render_api
  {
    Unknown, Vulkan,
  };

  class Global_config
  {
  public:
    static Global_config &get();

    void       set_render_api(const Render_api &render_api) { _render_api = render_api; }
    Render_api get_render_api() const { return _render_api; }

  private:
    Render_api _render_api = Render_api::Unknown;

    Global_config()  = default;
    ~Global_config() = default;

    Global_config(const Global_config &)            = delete;
    Global_config(Global_config &&)                 = delete;
    Global_config &operator=(const Global_config &) = delete;
    Global_config &operator=(Global_config &&)      = delete;
  };

  class Instance;
  class Window;
  class Surface;
  class Device;
}
