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

    // Get the native handle to the shader module
    virtual void *get_native_handle() const = 0;
  };

  // Factory function to create a shader module
  std::unique_ptr<Shader_module> create_shader_module(const Shader_module_create_info &create_info);
} // namespace Prism::HAL
