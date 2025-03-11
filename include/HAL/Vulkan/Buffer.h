/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include "HAL/Buffer.h"
#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Buffer : public HAL::Buffer
  {
  public:
    Buffer(VkBuffer buffer, VkDeviceMemory memory, VkDevice *device);
    ~Buffer() override;

    void stage(void *data, size_t size, size_t offset = 0) override;

    [[nodiscard]] VkBuffer *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkBuffer>       _vk_handle;
    std::unique_ptr<VkDeviceMemory> _vk_memory;
    VkDevice                       *_vk_device;
  };

  class Buffer_view : public HAL::Buffer_view
  {
  public:
    Buffer_view(VkBufferView buffer_view, VkDevice *device);
    ~Buffer_view() override;

    [[nodiscard]] VkBufferView *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkBufferView> _vk_handle;
    VkDevice                     *_vk_device;
  };

  VkBufferCreateInfo     convert(const HAL::Buffer_create_info &create_info);
  VkBufferViewCreateInfo convert(const HAL::Buffer_view_create_info &create_info);
  VkBufferUsageFlags     convert(const HAL::Buffer_usage usage);
  VkMemoryPropertyFlags  convert(const HAL::Memory_property property);
} // namespace Prism::HAL::Vulkan
