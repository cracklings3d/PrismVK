// Created by cr on 2/25/25.

#pragma once

#include <memory>
#include <vector>

#include "HAL.h"
#include "Physical_device.h" // Need to know about Physical_device
#include "Utils.h"

namespace Prism::HAL
{
  class Device
  {
  public:
    virtual ~Device() = default;

    // virtual class Command_queue* get_graphics_queue() = 0;
  };

  /**
   * @brief Information required to create a command queue
   */
  struct Device_queue_create_info
  {
    uint32_t queue_family_index;
    std::shared_ptr<std::vector<float>> queue_priorities;
  };

  /**
   * @brief Information required to create a device
   */
  struct Device_create_info
  {
    std::vector<Device_queue_create_info> queue_infos;
    std::vector<const char *>             required_extensions;
  };

} // namespace Prism::HAL
