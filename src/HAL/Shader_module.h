#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Prism::HAL
{
  struct Shader_module_create_info
  {
    std::string code;
  };

  class Shader_module
  {
  public:
    virtual ~Shader_module() = default;
  };
} // namespace Prism::HAL
