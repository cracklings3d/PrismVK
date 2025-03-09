/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include "HAL/Image.h"
#include "HAL/Pipeline.h"

namespace Prism::HAL
{
  enum class Attachment_load_op
  {
    Load,
    Clear,
    Dont_care
  };

  enum class Attachment_store_op
  {
    Store,
    Dont_care
  };

  enum class Image_layout
  {
    Undefined,
    Color_attachment_optimal,
    Present_src
  };

  struct Attachment_description
  {
    Image_format        format;
    Sample_count        samples;
    Attachment_load_op  load_op;
    Attachment_store_op store_op;
    Attachment_load_op  stencil_load_op;
    Attachment_store_op stencil_store_op;
    Image_layout        initial_layout;
    Image_layout        final_layout;
  };
} // namespace Prism::HAL
