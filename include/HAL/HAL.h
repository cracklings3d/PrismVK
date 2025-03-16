/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 03 2025       *
 *****************************/

#pragma once

namespace Prism::HAL
{
  enum class Render_api
  {
    Unknown,
    Vulkan,
  };

  struct Render_settings
  {
    Render_api render_api;
  };

} // namespace Prism::HAL
