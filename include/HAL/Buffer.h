/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <cstdint>
#include <memory>

namespace Prism::HAL
{
  enum class Sharing_mode
  {
    Exclusive,
    Concurrent,
  };

  enum class Buffer_usage : uint32_t
  {
    Transfer_src                                 = 0x00000001,
    Transfer_dst                                 = 0x00000002,
    Uniform_texel_buffer                         = 0x00000004,
    Storage_texel_buffer                         = 0x00000008,
    Uniform_buffer                               = 0x00000010,
    Storage_buffer                               = 0x00000020,
    Index_buffer                                 = 0x00000040,
    Vertex_buffer                                = 0x00000080,
    Indirect_buffer                              = 0x00000100,
    Conditional_rendering                        = 0x00000200,
    Shader_binding_table                         = 0x00000400,
    Transform_feedback_buffer                    = 0x00000800,
    Transform_feedback_counter_buffer            = 0x00001000,
    Video_decode_src                             = 0x00002000,
    Video_decode_dst                             = 0x00004000,
    Video_encode_dst                             = 0x00008000,
    Video_encode_src                             = 0x00010000,
    Shader_device_address                        = 0x00020000,
    Acceleration_structure_build_input_read_only = 0x00080000,
    Acceleration_structure_storage               = 0x00100000,
    Sampler_descriptor_buffer                    = 0x00200000,
    Resource_descriptor_buffer                   = 0x00400000,
    Micromap_build_input_read_only               = 0x00800000,
    Micromap_storage                             = 0x01000000,
    Ray_tracing                                  = 0x02000000,
    Push_descriptors_descriptor_buffer           = 0x04000000,
  };

  enum class Memory_property : uint32_t
  {
    Device_local     = 0x00000001,
    Host_visible     = 0x00000002,
    Host_coherent    = 0x00000004,
    Host_cached      = 0x00000008,
    Lazily_allocated = 0x00000010,
    Protected        = 0x00000020,
    Device_coherent  = 0x00000040,
    Device_uncached  = 0x00000080,
    RDMA_capable     = 0x00000100,
  };

  inline Memory_property operator|(Memory_property a, Memory_property b)
  {
    return static_cast<Memory_property>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
  }

  struct Buffer_create_info
  {
    size_t          size;
    Buffer_usage    usage;
    Sharing_mode    sharing_mode;
    Memory_property desired_memory_properties;
  };

  class Buffer
  {
  public:
    virtual ~Buffer() = default;

    virtual void stage(void *data, size_t size, size_t offset = 0) = 0;
  };

  struct Buffer_view_create_info
  {
    Buffer *buffer;
    size_t  offset;
    size_t  range;
  };

  class Buffer_view
  {
  public:
    virtual ~Buffer_view() = default;
  };
} // namespace Prism::HAL
