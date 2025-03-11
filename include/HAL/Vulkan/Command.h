/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include "HAL/Command.h"
#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Command_buffer : public HAL::Command_buffer
  {
  public:
    explicit Command_buffer(VkCommandBuffer vk_command_buffer, VkCommandPool *vk_command_pool);
    ~Command_buffer() override = default;

    void begin() override;
    void end() override;

    [[nodiscard]] VkCommandBuffer *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkCommandBuffer> _vk_handle;
    VkCommandPool                   *_vk_command_pool;
  };

  class Command_pool : public HAL::Command_pool
  {
  public:
    Command_pool(VkCommandPool command_pool, VkDevice *device);
    ~Command_pool() override;

    std::vector<std::unique_ptr<HAL::Command_buffer>>
    allocate_command_buffers(const Command_buffer_allocate_info &allocate_info) override;

    [[nodiscard]] VkCommandPool *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkCommandPool> _vk_handle;
    VkDevice                      *_vk_device;
  };

  VkCommandBufferLevel        convert(const HAL::Command_buffer_level level);
  VkCommandPoolCreateInfo     convert(const HAL::Command_pool_create_info &create_info);
  VkCommandBufferAllocateInfo convert(const HAL::Command_buffer_allocate_info &allocate_info, VkCommandPool pool);
  VkCommandPoolCreateFlags    convert(const HAL::Command_pool_create_flags flags);
} // namespace Prism::HAL::Vulkan
