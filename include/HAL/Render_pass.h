/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <memory>
#include <vector>

#include "Attachment.h"
#include "HAL/HAL.h"
#include "HAL/Image.h"

namespace Prism::HAL
{
  struct Attachment_reference
  {
    uint32_t     attachment;
    Image_layout layout;
  };

  enum class Pipeline_bind_point
  {
    Graphics,
    Compute,
  };

  struct Subpass_description
  {
    Pipeline_bind_point               pipeline_bind_point;
    std::vector<Attachment_reference> color_attachments;
  };

  struct Render_pass_create_info
  {
    std::vector<Attachment_description> attachments;
    std::vector<Subpass_description>    subpasses;
  };

  class Render_pass
  {
  public:
    virtual ~Render_pass() = default;
  };
} // namespace Prism::HAL
