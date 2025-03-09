/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 07 2025       *
 *****************************/

#pragma once

#include "HAL/Descriptor.h"
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Descriptor_set_layout final : public HAL::Descriptor_set_layout
  {
  public:
    explicit Descriptor_set_layout(VkDescriptorSetLayout &&layout, VkDevice *device);
    ~Descriptor_set_layout() override;

    Descriptor_set_layout(const Descriptor_set_layout &)            = delete;
    Descriptor_set_layout &operator=(const Descriptor_set_layout &) = delete;

    Descriptor_set_layout(Descriptor_set_layout &&other) noexcept            = default;
    Descriptor_set_layout &operator=(Descriptor_set_layout &&other) noexcept = default;

    [[nodiscard]] inline VkDescriptorSetLayout get_vk_handle() const { return *_vk_handle; }

  private:
    VkDevice                              *_vk_device;
    std::unique_ptr<VkDescriptorSetLayout> _vk_handle;
  };

  VkDescriptorType                convert(const HAL::Descriptor_type &descriptor_type);
  VkDescriptorSetLayoutBinding    convert(const HAL::Descriptor_set_layout_binding &binding);
  VkDescriptorSetLayoutCreateInfo convert(const HAL::Descriptor_set_layout_create_info &create_info);
} // namespace Prism::HAL::Vulkan
