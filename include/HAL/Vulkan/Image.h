#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "HAL/Image.h"

namespace Prism::HAL
{} // namespace Prism::HAL

namespace Prism::HAL::Vulkan
{
  class Image_view final : public HAL::Image_view
  {
  public:
    Image_view(VkImageView &&vk_image_view, VkDevice *vk_device)
        : _vk_handle(std::make_unique<VkImageView>(vk_image_view)), _vk_device(vk_device)
    {}

    ~Image_view() override;

    [[nodiscard]] VkImageView *get_vk_handle() const;

  private:
    std::unique_ptr<VkImageView> _vk_handle = nullptr;
    VkDevice                    *_vk_device = nullptr;
  };

  class Image final : public HAL::Image
  {
  public:
    Image(VkImage &&vk_image, VkDevice *vk_device)
        : _vk_handle(std::make_unique<VkImage>(vk_image)), _vk_device(vk_device)
    {}

    ~Image() override;

    [[nodiscard]] std::unique_ptr<HAL::Image_view>
    create_view(const Image_view_create_info &create_info) const override;

    [[nodiscard]] VkImage *get_vk_handle() const;

  private:
    std::unique_ptr<VkImage> _vk_handle = nullptr;
    VkDevice                *_vk_device = nullptr;
  };

  VkImageUsageFlags convert(const HAL::Image_usage &image_usage);
} // namespace Prism::HAL::Vulkan
