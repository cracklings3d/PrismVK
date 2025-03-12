/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 12 2025       *
 *****************************/

#pragma once

#include <cstdint>
#include <type_traits>

namespace Prism::HAL::Vulkan
{
  template <typename TEnumTo, typename TEnumFrom>
    requires requires {
      std::is_enum_v<TEnumFrom>;
      std::is_enum_v<TEnumTo>;
      std::is_same_v<std::underlying_type_t<TEnumFrom>, uint32_t>;
    }
  TEnumTo convert_enum(const TEnumFrom &enum_value)
  {
    return static_cast<TEnumTo>(static_cast<uint32_t>(enum_value));
  }
} // namespace Prism::HAL::Vulkan
