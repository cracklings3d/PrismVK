#pragma once

#include <string>
#include <vulkan/vulkan_core.h>

namespace Prism::HAL::Vulkan
{
  std::string get_message(const VkResult &result);
  void        check_result(const VkResult &result, const std::string &message);
} // namespace Prism::HAL::Vulkan
