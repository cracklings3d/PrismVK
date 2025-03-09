/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 07 2025       *
 *****************************/

#include "HAL/Vulkan/Descriptor.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Param_converters.h"
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

  VkDescriptorType convert(const HAL::Descriptor_type &descriptor_type)
  {
    switch (descriptor_type)
    {
    case Descriptor_type::Sampler:
      return VK_DESCRIPTOR_TYPE_SAMPLER;
    case Descriptor_type::Combined_image_sampler:
      return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    case Descriptor_type::Sampled_image:
      return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    case Descriptor_type::Storage_image:
      return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    case Descriptor_type::Uniform_texel_buffer:
      return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
    case Descriptor_type::Storage_texel_buffer:
      return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
    case Descriptor_type::Uniform_buffer:
      return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    case Descriptor_type::Storage_buffer:
      return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    case Descriptor_type::Uniform_buffer_dynamic:
      return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    case Descriptor_type::Storage_buffer_dynamic:
      return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
    case Descriptor_type::Input_attachment:
      return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
    default:
      throw std::runtime_error("Unsupported descriptor type");
    }
  }

  VkDescriptorSetLayoutBinding convert(const HAL::Descriptor_set_layout_binding &binding)
  {
    VkDescriptorSetLayoutBinding result;

    result.binding            = binding.binding;
    result.descriptorType     = convert(binding.descriptor_type);
    result.descriptorCount    = binding.descriptor_count;
    result.stageFlags         = convert(binding.stage_flags);
    result.pImmutableSamplers = nullptr;

    return result;
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
} // namespace Prism::HAL::Vulkan
