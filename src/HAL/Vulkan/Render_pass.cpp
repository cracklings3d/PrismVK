#include "Render_pass.h"
#include "Param_converters.h"

namespace Prism::HAL::Vulkan
{
  Render_pass::~Render_pass()
  {
    if (_vk_render_pass != nullptr)
    {
      vkDestroyRenderPass(*_vk_device, *_vk_render_pass, nullptr);
      _vk_render_pass = nullptr;
    }
  }

  VkRenderPass *Render_pass::get_vk_render_pass() const
  {
    return _vk_render_pass.get();
  }
} // namespace Prism::HAL::Vulkan 