/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#include "HAL/Vulkan/Buffer.h"

#include "HAL/Vulkan/Common.h"

#include <cstring>

namespace Prism::HAL::Vulkan
{
  Buffer::Buffer(VkBuffer buffer, VkDeviceMemory memory, VkDevice *device)
      : _vk_handle(std::make_unique<VkBuffer>(buffer)),
        _vk_memory(std::make_unique<VkDeviceMemory>(memory)),
        _vk_device(device)
  {}

  Buffer::~Buffer()
  {
    if (_vk_handle != nullptr && _vk_device != nullptr)
    {
      vkDestroyBuffer(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
    if (_vk_memory != nullptr && _vk_device != nullptr)
    {
      vkFreeMemory(*_vk_device, *_vk_memory, nullptr);
      _vk_memory = nullptr;
    }
  }

  void Buffer::stage(void *data, size_t size, size_t offset)
  {
    void *staging_data;
    vkMapMemory(*_vk_device, *_vk_memory, offset, size, 0, &staging_data);
    memcpy(staging_data, data, size);
    vkUnmapMemory(*_vk_device, *_vk_memory);
  }

  Buffer_view::Buffer_view(VkBufferView buffer_view, VkDevice *device)
      : _vk_handle(std::make_unique<VkBufferView>(buffer_view)), _vk_device(device)
  {}

  Buffer_view::~Buffer_view()
  {
    if (_vk_handle != nullptr && _vk_device != nullptr)
    {
      vkDestroyBufferView(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  VkSharingMode convert(const HAL::Sharing_mode sharing_mode)
  {
    switch (sharing_mode)
    {
    case HAL::Sharing_mode::Exclusive:
      return VK_SHARING_MODE_EXCLUSIVE;
    case HAL::Sharing_mode::Concurrent:
      return VK_SHARING_MODE_CONCURRENT;
    default:
      throw std::runtime_error("Unsupported sharing mode");
    }
  }

  VkBufferCreateInfo convert(const HAL::Buffer_create_info &create_info)
  {
    VkBufferCreateInfo vk_create_info{};
    vk_create_info.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    vk_create_info.size        = create_info.size;
    vk_create_info.usage       = convert_enum<VkBufferUsageFlags>(create_info.usage);
    vk_create_info.sharingMode = convert_enum<VkSharingMode>(create_info.sharing_mode);
    return vk_create_info;
  }

  VkBufferViewCreateInfo convert(const HAL::Buffer_view_create_info &create_info)
  {
    VkBufferViewCreateInfo vk_create_info{};
    vk_create_info.sType  = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    vk_create_info.buffer = *static_cast<Vulkan::Buffer *>(create_info.buffer)->get_vk_handle();
    vk_create_info.offset = create_info.offset;
    vk_create_info.range  = create_info.range;
    return vk_create_info;
  }
} // namespace Prism::HAL::Vulkan
