// Created by cr on 2/21/25.

#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "HAL.h"
#include "Utils.h"


namespace Prism::HAL
{
  /**
   * @brief TODO
   */
  class Instance
  {
  public:
    virtual ~Instance() = default;

    virtual Device create_device() = 0;
  };

  /**
   * @brief Information required to create an instance
   */
  struct InstanceCreateInfo
  {
    uint32_t application_version = PRISM_VERSION(0, 0, 1);
    uint32_t engine_version      = PRISM_VERSION(0, 0, 1);

    std::string application_name = "Prism Application";
    std::string engine_name      = "Prism Engine";
  };

  struct Instance_factory
  {
    static std::unique_ptr<Instance> create_instance(const InstanceCreateInfo &create_info, const Window *window);
  };
}
