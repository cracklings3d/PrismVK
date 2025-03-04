#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "../Image.h"

namespace Prism::HAL::Vulkan
{
  class Image final : public HAL::Image
  {
  public:
    Image(VkImage &&vk_image, VkDevice *vk_device)
        : _vk_image(std::make_unique<VkImage>(vk_image)), _vk_device(vk_device)
    {
    }

    ~Image() override;

    [[nodiscard]] Image_view create_image_view(const Image_view_create_info &create_info) const;

    [[nodiscard]] VkImage *get_vk_image() const;

  private:
    std::unique_ptr<VkImage> _vk_image  = nullptr;
    VkDevice                *_vk_device = nullptr;
  };
} // namespace Prism::HAL::Vulkan
