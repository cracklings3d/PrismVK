#include "HAL/Vulkan/Render_pass.h"
#include "HAL/Vulkan/Param_converters.h"

namespace Prism::HAL::Vulkan
{
  Render_pass::~Render_pass()
  {
    if (_vk_handle != nullptr)
    {
      vkDestroyRenderPass(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }
} // namespace Prism::HAL::Vulkan
