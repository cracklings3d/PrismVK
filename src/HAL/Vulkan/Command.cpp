/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 11 2025       *
 *****************************/

#include "HAL/Vulkan/Command.h"
#include "HAL/Vulkan/Error.h"
#include <stdexcept>

namespace Prism::HAL::Vulkan
{
  Command_buffer::Command_buffer(VkCommandBuffer vk_command_buffer, VkCommandPool *vk_command_pool)
      : _vk_handle(std::make_unique<VkCommandBuffer>(vk_command_buffer)), _vk_command_pool(vk_command_pool)
  {}

  void Command_buffer::begin()
  {
    VkCommandBufferBeginInfo begin_info{};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    VkResult result = vkBeginCommandBuffer(*_vk_handle, &begin_info);
    check_result(result, __func__);
  }

  void Command_buffer::end()
  {
    VkResult result = vkEndCommandBuffer(*_vk_handle);
    check_result(result, __func__);
  }

  Command_pool::Command_pool(VkCommandPool command_pool, VkDevice *device)
      : _vk_handle(std::make_unique<VkCommandPool>(command_pool)), _vk_device(device)
  {}

  Command_pool::~Command_pool()
  {
    if (_vk_handle != nullptr && _vk_device != nullptr)
    {
      vkDestroyCommandPool(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }

  std::vector<std::unique_ptr<HAL::Command_buffer>>
  Command_pool::allocate_command_buffers(const HAL::Command_buffer_allocate_info &allocate_info)
  {
    VkCommandBufferAllocateInfo  vk_allocate_info = convert(allocate_info, *_vk_handle);
    std::vector<VkCommandBuffer> command_buffers(allocate_info.count);

    VkResult result = vkAllocateCommandBuffers(*_vk_device, &vk_allocate_info, command_buffers.data());
    check_result(result, __func__);

    std::vector<std::unique_ptr<HAL::Command_buffer>> hal_command_buffers;
    hal_command_buffers.reserve(command_buffers.size());

    for (auto &command_buffer : command_buffers)
    {
      hal_command_buffers.push_back(std::make_unique<Vulkan::Command_buffer>(command_buffer, _vk_handle.get()));
    }

    return hal_command_buffers;
  }

  const VkCommandBufferLevel convert(const HAL::Command_buffer_level level)
  {
    return static_cast<VkCommandBufferLevel>(static_cast<uint32_t>(level));
  }

  const VkCommandPoolCreateInfo convert(const HAL::Command_pool_create_info &create_info)
  {
    VkCommandPoolCreateInfo vk_create_info{};

    vk_create_info.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    vk_create_info.flags            = convert(create_info.flags);
    vk_create_info.queueFamilyIndex = create_info.queue_family_index;

    return vk_create_info;
  }

  const VkCommandBufferAllocateInfo convert(const HAL::Command_buffer_allocate_info &allocate_info, VkCommandPool pool)
  {
    VkCommandBufferAllocateInfo vk_allocate_info{};

    vk_allocate_info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    vk_allocate_info.commandPool        = pool;
    vk_allocate_info.level              = convert(allocate_info.level);
    vk_allocate_info.commandBufferCount = allocate_info.count;

    return vk_allocate_info;
  }

  const VkCommandPoolCreateFlags convert(const HAL::Command_pool_create_flags flags)
  {
    VkCommandPoolCreateFlags result = 0;

    if (static_cast<uint32_t>(flags) & static_cast<uint32_t>(Command_pool_create_flags::Transient))
    {
      result |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    }
    if (static_cast<uint32_t>(flags) & static_cast<uint32_t>(Command_pool_create_flags::Reset_command_buffer))
    {
      result |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    }

    return result;
  }
} // namespace Prism::HAL::Vulkan
