/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 07 2025       *
 *****************************/

#pragma once

#include "HAL/Logic_op.h"

#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  VkLogicOp convert(const Logic_op &logic_op)
  {
    switch (logic_op)
    {
    case Logic_op::Clear:
      return VK_LOGIC_OP_CLEAR;
    case Logic_op::And:
      return VK_LOGIC_OP_AND;
    case Logic_op::And_reverse:
      return VK_LOGIC_OP_AND_REVERSE;
    case Logic_op::Copy:
      return VK_LOGIC_OP_COPY;
    case Logic_op::And_inverted:
      return VK_LOGIC_OP_AND_INVERTED;
    case Logic_op::No_op:
      return VK_LOGIC_OP_NO_OP;
    case Logic_op::Xor:
      return VK_LOGIC_OP_XOR;
    case Logic_op::Or:
      return VK_LOGIC_OP_OR;
    case Logic_op::Nor:
      return VK_LOGIC_OP_NOR;
    case Logic_op::Equivalent:
      return VK_LOGIC_OP_EQUIVALENT;
    case Logic_op::Invert:
      return VK_LOGIC_OP_INVERT;
    case Logic_op::Or_reverse:
      return VK_LOGIC_OP_OR_REVERSE;
    case Logic_op::Copy_inverted:
      return VK_LOGIC_OP_COPY_INVERTED;
    case Logic_op::Or_inverted:
      return VK_LOGIC_OP_OR_INVERTED;
    case Logic_op::Nand:
      return VK_LOGIC_OP_NAND;
    case Logic_op::Set:
      return VK_LOGIC_OP_SET;
    default:
      return VK_LOGIC_OP_CLEAR;
    }
  }
} // namespace Prism::HAL::Vulkan
