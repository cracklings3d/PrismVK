/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include "HAL/Command.h"
#include "HAL/Queue.h"

#include <memory>
#include <vulkan/vulkan_core.h>

namespace Prism::HAL::Vulkan
{
  class Queue : public HAL::Queue
  {
  public:
    Queue(const VkQueue &vk_queue);

    // Lifetime of VKQueue is bound to the VkDevice, so we don't need to destroy it explicitly

    [[nodiscard]] VkQueue *get_vk_queue() const;

    void present(const HAL::Present_info &present_info) override;
    void submit(const std::vector<HAL::Submit_info> &submit_info, HAL::Fence *fence) override;

  private:
    std::unique_ptr<VkQueue> _vk_queue;
  };

  const VkSubmitInfo convert(const HAL::Submit_info &submit_info);
} // namespace Prism::HAL::Vulkan
