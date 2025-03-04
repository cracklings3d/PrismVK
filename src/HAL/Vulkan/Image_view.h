#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "../Image_view.h"

namespace Prism::HAL::Vulkan
{
  class Image_view final : public HAL::Image_view
  {
  public:
    Image_view(VkImageView &&vk_image_view, VkDevice *vk_device)
        : _vk_image_view(std::make_unique<VkImageView>(vk_image_view)), _vk_device(vk_device)
    {
    }

    ~Image_view() override;

    [[nodiscard]] VkImageView *get_vk_image_view() const;

  private:
    std::unique_ptr<VkImageView> _vk_image_view = nullptr;
    VkDevice                    *_vk_device     = nullptr;
  };
} // namespace Prism::HAL::Vulkan 