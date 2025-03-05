#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "../Shader_module.h"

namespace Prism::HAL::Vulkan
{
  // Convert from HAL to Vulkan-specific create info
  VkShaderModuleCreateInfo convert(const HAL::Shader_module_create_info &hal_create_info);

  class Shader_module : public HAL::Shader_module
  {
  public:
    Shader_module(VkShaderModule shader_module, VkDevice *device);
    ~Shader_module() override;

    void *get_native_handle() const override;

  private:
    VkDevice                       *_device;
    std::unique_ptr<VkShaderModule> _shader_module;
  };
} // namespace Prism::HAL::Vulkan
