#include "Shader_module.h"
#include "Error.h"

namespace Prism::HAL::Vulkan
{
  VkShaderModuleCreateInfo convert(const HAL::Shader_module_create_info &hal_create_info)
  {
    VkShaderModuleCreateInfo result;

    result.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    result.codeSize = hal_create_info.code.size();
    result.pCode    = reinterpret_cast<const uint32_t *>(hal_create_info.code.data());

    return result;
  }

  Shader_module::Shader_module(VkShaderModule shader_module, VkDevice *device)
      : _vk_shader_module(std::make_unique<VkShaderModule>(shader_module)), _vk_device(device)
  {
  }

  Shader_module::~Shader_module()
  {
    if (_vk_shader_module != VK_NULL_HANDLE)
    {
      vkDestroyShaderModule(*_vk_device, *_vk_shader_module, nullptr);
      _vk_shader_module = VK_NULL_HANDLE;
    }
  }
} // namespace Prism::HAL::Vulkan
