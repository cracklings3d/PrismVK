#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "../Render_pass.h"

namespace Prism::HAL::Vulkan
{
  class Render_pass final : public HAL::Render_pass
  {
  public:
    Render_pass(VkRenderPass &&vk_render_pass, VkDevice *vk_device)
        : _vk_render_pass(std::make_unique<VkRenderPass>(vk_render_pass)), _vk_device(vk_device)
    {
    }

    ~Render_pass() override;

    [[nodiscard]] VkRenderPass *get_vk_render_pass() const;

  private:
    std::unique_ptr<VkRenderPass> _vk_render_pass = nullptr;
    VkDevice                     *_vk_device      = nullptr;
  };
} // namespace Prism::HAL::Vulkan 