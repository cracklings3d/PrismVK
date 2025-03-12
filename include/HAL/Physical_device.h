/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 23 2025       *
 *****************************/

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Prism::HAL
{
  struct Device_create_info;
}

namespace Prism::HAL
{
  namespace Vulkan
  {
    class Physical_device;
  }

  class Device;

  struct Physical_device_properties
  {
    uint32_t    api_version;
    uint32_t    driver_version;
    uint32_t    vendor_id;
    uint32_t    device_id;
    uint32_t    device_type;
    std::string device_name;
  };

  class Physical_device
  {
  public:
    virtual ~Physical_device() = default;

    [[nodiscard]] virtual Physical_device_properties get_device_properties() const                                = 0;
    [[nodiscard]] virtual std::unique_ptr<Device>    create_device(const Device_create_info &device_create_info)  = 0;
  };
} // namespace Prism::HAL
