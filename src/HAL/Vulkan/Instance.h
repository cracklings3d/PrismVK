// Created by cr on 2/19/25.

#pragma once

#include <memory>
#include <vulkan/vulkan_core.h>
#include "../HAL.h"
#include "../Window.h"
#include "../Instance.h"


namespace Prism::HAL
{
  struct InstanceCreateInfo;
}

namespace Prism::HAL::Vulkan
{
  class Instance final : public HAL::Instance
  {
  public:
    Instance(const InstanceCreateInfo &&instance_create_info, const Window *window);
    ~Instance() override;

    [[nodiscard]] Device create_device() override;

    VkInstance get_vk_instance();

  private:
    VkInstance _vk_instance = nullptr;
  };
}

#pragma once
