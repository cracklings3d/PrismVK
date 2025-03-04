#pragma once

#include "../Queue.h"
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

  private:
    std::unique_ptr<VkQueue> _vk_queue;
  };
} // namespace Prism::HAL::Vulkan
