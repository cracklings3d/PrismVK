// Created by cr on 2/19/25.

#pragma once

#include "../Device.h"
#include "../Instance.h"
#include <memory>
#include <vulkan/vulkan_core.h>

namespace Prism::HAL::Vulkan
{
  class Device;

  class Instance final : public HAL::Instance
  {
  public:
    explicit Instance(const HAL::Instance_create_info &instance_create_info);
    ~Instance() override;

    [[nodiscard]] std::vector<std::shared_ptr<HAL::Physical_device>> enumerate_physical_devices() const override;

    [[nodiscard]] std::shared_ptr<HAL::Physical_device> select_discrete_gpu() const override;

    [[nodiscard]] VkInstance *get_vk_instance() const;

  private:
    std::unique_ptr<VkInstance> _vk_instance;
  };

} // namespace Prism::HAL::Vulkan

#pragma once
