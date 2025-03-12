/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <cstdint>

namespace Prism::HAL
{
  struct Semaphore_create_info
  {
    // Currently empty, but can be extended for future use
  };

  struct Fence_create_info
  {
    bool signaled = false;
  };

  class Semaphore
  {
  public:
    virtual ~Semaphore() = default;
  };

  class Fence
  {
  public:
    virtual ~Fence() = default;

    virtual void wait(uint64_t timeout = UINT64_MAX) = 0;

    virtual void reset() = 0;
  };
} // namespace Prism::HAL
