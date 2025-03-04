#include "Queue.h"

namespace Prism::HAL::Vulkan
{
  Queue::Queue(const VkQueue &vk_queue) : _vk_queue(std::make_unique<VkQueue>(vk_queue)) {}

  [[nodiscard]] VkQueue *Queue::get_vk_queue() const { return _vk_queue.get(); }
} // namespace Prism::HAL::Vulkan
