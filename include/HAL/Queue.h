/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include <cstdint>
#include <vector>

namespace Prism::HAL
{
  class Command_buffer;
  class Fence;
  class Semaphore;
  class Swapchain;

  enum class Pipeline_stage : uint32_t;

  struct Present_info
  {
    std::vector<Semaphore *> wait_semaphores;
    std::vector<Swapchain *> swapchains;
    std::vector<uint32_t>    image_indices;
  };

  struct Submit_info
  {
    std::vector<Command_buffer *> command_buffers;
    std::vector<Semaphore *>      wait_semaphores;
    std::vector<Semaphore *>      signal_semaphores;
    std::vector<Pipeline_stage>   wait_stages;
  };

  class Queue
  {
  public:
    virtual ~Queue() = default;

    virtual void present(const Present_info &present_info)                         = 0;
    virtual void submit(const std::vector<Submit_info> &submit_info, Fence *fence) = 0;
  };
} // namespace Prism::HAL
