/*****************************
 * Copyright 2025 Cracklings *
 * Created Feb 26 2025       *
 *****************************/

#pragma once

#include "HAL/Device.h"
#include "HAL/Queue.h"
#include "Util/Util.h"

#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Physical_device;
  class Render_pass;
  class Render_pass_create_info;

  class Device : public HAL::Device
  {
  public:
    ~Device() override;
    explicit Device(const VkDevice &vk_device, VkPhysicalDevice *vk_physical_device);

    [[nodiscard]] virtual std::unique_ptr<HAL::Queue> get_graphics_queue() const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Swapchain>
    create_swapchain(const HAL::Swapchain_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Render_pass>
    create_render_pass(const HAL::Render_pass_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Shader_module>
    create_shader_module(const HAL::Shader_module_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Descriptor_set_layout>
    create_descriptor_set_layout(const HAL::Descriptor_set_layout_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Pipeline_layout>
    create_pipeline_layout(const HAL::Pipeline_layout_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Pipeline>
    create_graphics_pipeline(const HAL::Graphics_pipeline_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Framebuffer>
    create_framebuffer(const HAL::Framebuffer_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Buffer>
    create_buffer(const HAL::Buffer_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Buffer_view>
    create_buffer_view(const HAL::Buffer_view_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Command_pool>
    create_command_pool(const HAL::Command_pool_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Semaphore>
    create_semaphore(const HAL::Semaphore_create_info &create_info) const override;
    [[nodiscard]] virtual std::unique_ptr<HAL::Fence>
    create_fence(const HAL::Fence_create_info &create_info) const override;

    virtual void wait_idle() const override;

    [[nodiscard]] VkDevice *get_vk_handle() const { return _vk_handle.get(); }

  private:
    uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) const;

  private:
    std::unique_ptr<VkDevice> _vk_handle = nullptr;

    VkPhysicalDevice *_vk_physical_device = nullptr;

    [[nodiscard]] std::unique_ptr<HAL::Queue> get_queue(uint32_t queue_family_index, uint32_t queue_index) const;
  };

  constexpr auto DEVICE_SWAPCHAIN_EXTENSIONS = std::array{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  using VkScopedDeviceQueueCreateInfo = Util::Scoped<VkDeviceQueueCreateInfo, std::vector<float>>;
  using VkScopedDeviceCreateInfo      = Util::Scoped<VkDeviceCreateInfo, std::vector<VkScopedDeviceQueueCreateInfo>, std::vector<const char *>>;

  VkScopedDeviceQueueCreateInfo convert(const HAL::Device_queue_create_info &device_queue_create_info);
  VkScopedDeviceCreateInfo      convert(const HAL::Device_create_info &device_create_info);
} // namespace Prism::HAL::Vulkan
