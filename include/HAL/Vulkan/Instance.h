/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 19 2025      *
 *****************************/

#pragma once

#include "HAL/Instance.h"

#include <memory>
#include <vulkan/vulkan_core.h>

namespace Prism::HAL::Vulkan
{
  class Device;

  class Instance final : public HAL::Instance
  {
  public:
    explicit Instance(VkInstance &&vk_handle);
    ~Instance() override;

    [[nodiscard]] std::vector<std::shared_ptr<HAL::Physical_device>> enumerate_physical_devices() const override;

    [[nodiscard]] std::shared_ptr<HAL::Physical_device> select_discrete_gpu() const override;

    [[nodiscard]] VkInstance *get_vk_handle() const;

  private:
    std::unique_ptr<VkInstance> _vk_handle;
  };

  std::unique_ptr<Instance> create_instance(const HAL::Instance_create_info &instance_create_info);

  VkInstanceCreateInfo convert(const HAL::Instance_create_info &instance_create_info);
} // namespace Prism::HAL::Vulkan
