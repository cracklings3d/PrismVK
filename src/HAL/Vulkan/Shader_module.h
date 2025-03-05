#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "../Shader_module.h"

namespace Prism::HAL::Vulkan
{
  VkShaderModuleCreateInfo convert(const HAL::Shader_module_create_info &hal_create_info);

  class Shader_module : public HAL::Shader_module
  {
  public:
    Shader_module(VkShaderModule shader_module, VkDevice *device);
    ~Shader_module() override;

  private:
    VkDevice                       *_vk_device;
    std::unique_ptr<VkShaderModule> _vk_shader_module;
  };
} // namespace Prism::HAL::Vulkan
