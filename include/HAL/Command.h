/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <memory>
#include <vector>

namespace Prism::HAL
{
  class Command_buffer;
  class Semaphore;
  enum class Pipeline_stage : uint32_t;

  enum class Command_pool_create_flags
  {
    None                 = 0,
    Transient            = 1,
    Reset_command_buffer = 2,
  };

  struct Command_pool_create_info
  {
    uint32_t                  queue_family_index;
    Command_pool_create_flags flags;
  };

  enum class Command_buffer_level
  {
    Primary,
    Secondary,
  };

  struct Command_buffer_allocate_info
  {
    uint32_t             count;
    Command_buffer_level level;
  };

  class Command_buffer
  {
  public:
    virtual ~Command_buffer() = default;

    virtual void begin() = 0;
    virtual void end()   = 0;
  };

  class Command_pool
  {
  public:
    virtual ~Command_pool() = default;

    virtual std::vector<std::unique_ptr<Command_buffer>>
    allocate_command_buffers(const Command_buffer_allocate_info &allocate_info) = 0;
  };


} // namespace Prism::HAL
