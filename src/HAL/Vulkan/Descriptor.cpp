/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 07 2025       *
 *****************************/

#include "HAL/Vulkan/Descriptor.h"

#include "HAL/Vulkan/Common.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Shader.h"

#include <algorithm>

namespace Prism::HAL::Vulkan
{
  Descriptor_set_layout::Descriptor_set_layout(VkDescriptorSetLayout &&vk_layout, VkDevice *vk_device)
      : _vk_handle(std::make_unique<VkDescriptorSetLayout>(vk_layout)), _vk_device(vk_device)
  {}

  Descriptor_set_layout::~Descriptor_set_layout()
  {
    if (_vk_handle != nullptr)
    {
      vkDestroyDescriptorSetLayout(*_vk_device, *_vk_handle, nullptr);
    }
  }

  VkDescriptorSetLayoutCreateInfo convert(const HAL::Descriptor_set_layout_create_info &create_info)
  {
    VkDescriptorSetLayoutCreateInfo result;

    auto bindings = std::vector<VkDescriptorSetLayoutBinding>();
    // std::transform(create_info.bindings.begin(), create_info.bindings.end(), std::back_inserter(bindings), convert);
    for (const auto &binding : create_info.bindings)
    {
      bindings.push_back(convert(binding));
    }

    result.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    result.pNext        = nullptr;
    result.flags        = 0;
    result.bindingCount = bindings.size();
    result.pBindings    = bindings.data();

    return result;
  }

  VkDescriptorSetLayoutBinding convert(const HAL::Descriptor_set_layout_binding &binding)
  {
    VkDescriptorSetLayoutBinding result;

    result.binding            = binding.binding;
    result.descriptorType     = convert_enum<VkDescriptorType>(binding.descriptor_type);
    result.descriptorCount    = binding.descriptor_count;
    result.stageFlags         = convert_enum<VkShaderStageFlags>(binding.stage_flags);
    result.pImmutableSamplers = nullptr;

    return result;
  }
} // namespace Prism::HAL::Vulkan
