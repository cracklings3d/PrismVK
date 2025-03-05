/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 03 2025       *
 *****************************/

#pragma once

#include <cstdint>

namespace Prism::HAL
{
  enum class Render_api
  {
    Unknown,
    Vulkan,
  };

  enum class Image_format
  {
    Unknown,
    R8G8B8A8_UNORM,
    R8G8B8A8_SRGB,
    B8G8R8A8_UNORM,
    B8G8R8A8_SRGB,
  };

  enum class Sample_count
  {
    Unknown,
    Count_1,
    Count_2,
    Count_4,
    Count_8,
    Count_16,
  };

  enum class Color_space
  {
    Unknown,
    SRGB_NONLINEAR,
  };

  enum class Image_usage
  {
    Unknown,
    COLOR_ATTACHMENT,
  };

  enum class Image_sharing_mode
  {
    Unknown,
    EXCLUSIVE,
  };

  struct Extent
  {
    uint32_t width;
    uint32_t height;
  };

  enum class Image_present_mode
  {
    Unknown,
    FIFO,
  };

  class Global_config
  {
  public:
    static Global_config &get();

    void set_render_api(const Render_api &render_api);

    Render_api get_render_api() const;

    Global_config(const Global_config &)            = delete;
    Global_config(Global_config &&)                 = delete;
    Global_config &operator=(const Global_config &) = delete;
    Global_config &operator=(Global_config &&)      = delete;

  private:
    Render_api _render_api = Render_api::Unknown;

    Global_config()  = default;
    ~Global_config() = default;
  };

} // namespace Prism::HAL
