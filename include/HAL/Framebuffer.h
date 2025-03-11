/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <memory>
#include <vector>

namespace Prism::HAL
{
  class Image_view;
  class Render_pass;

  struct Framebuffer_create_info
  {
    Render_pass              *render_pass;
    std::vector<Image_view *> attachments;
    uint32_t                  width;
    uint32_t                  height;
    uint32_t                  layers;
  };

  class Framebuffer
  {
  public:
    virtual ~Framebuffer() = default;
  };
} // namespace Prism::HAL
