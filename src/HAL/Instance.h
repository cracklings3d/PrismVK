// Created by cr on 2/21/25.

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Utils.h"

namespace Prism::HAL
{
  class Physical_device;
  class Device;

  struct Instance_create_info;

  namespace Vulkan
  {
    class Instance;
  }

  /**
   * @brief TODO
   */
  class Instance
  {
  public:
    virtual ~Instance() = default;

    [[nodiscard]] virtual std::vector<std::shared_ptr<Physical_device>> enumerate_physical_devices() const = 0;

    [[nodiscard]] virtual std::shared_ptr<Physical_device> select_discrete_gpu() const = 0;
  };

  /**
   * @brief Information required to create an instance
   */
  struct Instance_create_info
  {
    uint32_t application_version = PRISM_VERSION(0, 0, 1);
    uint32_t engine_version      = PRISM_VERSION(0, 0, 1);

    std::string               application_name = "Prism Application";
    std::string               engine_name      = "Prism Engine";
    std::vector<const char *> required_extensions;
  };

  std::unique_ptr<Instance> create_instance(const Instance_create_info &create_info);
} // namespace Prism::HAL
