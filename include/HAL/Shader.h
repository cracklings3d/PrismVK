/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 09 2025       *
 *****************************/

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Prism::HAL
{
  enum class Shader_stage : uint32_t
  {
    Vertex                  = 0x00000001,
    Tessellation_control    = 0x00000002,
    Tessellation_evaluation = 0x00000004,
    Geometry                = 0x00000008,
    Fragment                = 0x00000010,
    Compute                 = 0x00000020,
    All_graphics            = 0x0000001F,
    All                     = 0x7FFFFFFF,
    Raygen                  = 0x00000100,
    Any_hit                 = 0x00000200,
    Closest_hit             = 0x00000400,
    Miss                    = 0x00000800,
    Intersection            = 0x00001000,
    Callable                = 0x00002000,
    Task                    = 0x00000040,
    Mesh                    = 0x00000080,
    Subpass_shading         = 0x00004000,
    Cluster_culling         = 0x00080000,
  };

  inline Shader_stage operator|(Shader_stage a, Shader_stage b)
  {
    return static_cast<Shader_stage>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
  }

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
