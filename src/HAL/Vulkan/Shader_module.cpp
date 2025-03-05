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

  Shader_module::Shader_module(VkDevice device, const HAL::Shader_module_create_info &hal_create_info)
      : _device(device), _shader_module(VK_NULL_HANDLE)
  {
  }

  Shader_module::~Shader_module()
  {
    if (_shader_module != VK_NULL_HANDLE)
    {
      vkDestroyShaderModule(_device, _shader_module, nullptr);
      _shader_module = VK_NULL_HANDLE;
    }
  }

  void *Shader_module::get_native_handle() const { return (void *)_shader_module; }
} // namespace Prism::HAL::Vulkan
