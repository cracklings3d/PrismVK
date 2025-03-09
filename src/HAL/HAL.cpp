// Created by cr on 2/19/25.

#include "HAL/HAL.h"

namespace Prism::HAL
{
  Global_config &Global_config::get()
  {
    static Global_config instance;
    return instance;
  }

  void Global_config::set_render_api(const Render_api &render_api) { _render_api = render_api; }

  Render_api Global_config::get_render_api() const { return _render_api; }
} // namespace Prism::HAL
