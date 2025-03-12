/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 12 2025       *
 *****************************/

#pragma once

#include "HAL/Sync.h"

#include <vulkan/vulkan.h>
#include <memory>

namespace Prism::HAL::Vulkan
{
  class Semaphore : public HAL::Semaphore
  {
  public:
    Semaphore(VkSemaphore semaphore, VkDevice* device);
    ~Semaphore() override;

    [[nodiscard]] VkSemaphore* get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkSemaphore> _vk_handle;
    VkDevice* _vk_device;
  };

  class Fence : public HAL::Fence
  {
  public:
    Fence(VkFence fence, VkDevice* device);
    ~Fence() override;

    void wait(uint64_t timeout = UINT64_MAX) override;
    void reset() override;

    [[nodiscard]] VkFence* get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkFence> _vk_handle;
    VkDevice* _vk_device;
  };

  VkSemaphoreCreateInfo convert(const HAL::Semaphore_create_info& create_info);
  VkFenceCreateInfo convert(const HAL::Fence_create_info& create_info);
} 