#pragma once

#include "HAL/Pipeline.h"
#include "HAL/Shader.h"
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  class Shader_module : public HAL::Shader_module
  {
  public:
    Shader_module(VkShaderModule shader_module, VkDevice *device);
    ~Shader_module() override;

    VkShaderModule *get_vk_handle();

  private:
    VkDevice *                      _vk_device;
    std::unique_ptr<VkShaderModule> _vk_handle;
  };

  VkShaderStageFlagBits    convert(HAL::Shader_stage stage);
  VkShaderModuleCreateInfo convert(const HAL::Shader_module_create_info &hal_create_info);
} // namespace Prism::HAL::Vulkan
