/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 12 2025       *
 *****************************/

#include "HAL/Vulkan/Sync.h"
#include "HAL/Vulkan/Error.h"

namespace Prism::HAL::Vulkan
{
  Semaphore::Semaphore(VkSemaphore semaphore, VkDevice* device)
      : _vk_handle(std::make_unique<VkSemaphore>(semaphore))
      , _vk_device(device)
  {
  }

  Semaphore::~Semaphore()
  {
    if (_vk_handle != nullptr && _vk_device != nullptr)
    {
      vkDestroySemaphore(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  Fence::Fence(VkFence fence, VkDevice* device)
      : _vk_handle(std::make_unique<VkFence>(fence))
      , _vk_device(device)
  {
  }

  Fence::~Fence()
  {
    if (_vk_handle != nullptr && _vk_device != nullptr)
    {
      vkDestroyFence(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  void Fence::wait(uint64_t timeout)
  {
    VkResult result = vkWaitForFences(*_vk_device, 1, _vk_handle.get(), VK_TRUE, timeout);
    check_result(result, __func__);
  }

  void Fence::reset()
  {
    VkResult result = vkResetFences(*_vk_device, 1, _vk_handle.get());
    check_result(result, __func__);
  }

  VkSemaphoreCreateInfo convert(const HAL::Semaphore_create_info& create_info)
  {
    VkSemaphoreCreateInfo vk_create_info{};
    vk_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return vk_create_info;
  }

  VkFenceCreateInfo convert(const HAL::Fence_create_info& create_info)
  {
    VkFenceCreateInfo vk_create_info{};
    vk_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vk_create_info.flags = create_info.signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;
    return vk_create_info;
  }
} 