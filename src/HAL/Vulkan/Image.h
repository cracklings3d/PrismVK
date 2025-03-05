#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "../Image.h"

namespace Prism::HAL
{
  struct Image_create_info;
  struct Image_view_create_info;
} // namespace Prism::HAL

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

    [[nodiscard]] HAL::Image_view create_view(const Image_view_create_info &create_info) const override;

    [[nodiscard]] VkImage *get_vk_image() const;

  private:
    std::unique_ptr<VkImage> _vk_image  = nullptr;
    VkDevice                *_vk_device = nullptr;
  };
} // namespace Prism::HAL::Vulkan
