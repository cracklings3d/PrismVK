/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#include "HAL/Vulkan/Queue.h"

#include "HAL/Vulkan/Command.h"
#include "HAL/Vulkan/Common.h"
#include "HAL/Vulkan/Error.h"
#include "HAL/Vulkan/Pipeline.h"
#include "HAL/Vulkan/Swapchain.h"
#include "HAL/Vulkan/Sync.h"

#include <vulkan/vulkan_core.h>

namespace Prism::HAL::Vulkan
{
  Queue::Queue(const VkQueue &vk_queue) : _vk_queue(std::make_unique<VkQueue>(vk_queue)) {}

  [[nodiscard]] VkQueue *Queue::get_vk_queue() const { return _vk_queue.get(); }

  void Queue::present(const HAL::Present_info &present_info)
  {
    std::vector<VkSemaphore>    vk_wait_semaphores;
    std::vector<VkSwapchainKHR> vk_swapchains;

    vk_wait_semaphores.reserve(present_info.wait_semaphores.size());
    vk_swapchains.reserve(present_info.swapchains.size());

    for (auto *semaphore : present_info.wait_semaphores)
    {
      vk_wait_semaphores.push_back(*static_cast<Vulkan::Semaphore *>(semaphore)->get_vk_handle());
    }

    for (auto *swapchain : present_info.swapchains)
    {
      vk_swapchains.push_back(*static_cast<Vulkan::Swapchain *>(swapchain)->get_vk_handle());
    }

    VkPresentInfoKHR vk_present_info{};

    vk_present_info.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    vk_present_info.waitSemaphoreCount = vk_wait_semaphores.size();
    vk_present_info.pWaitSemaphores    = vk_wait_semaphores.data();
    vk_present_info.swapchainCount     = vk_swapchains.size();
    vk_present_info.pSwapchains        = vk_swapchains.data();
    vk_present_info.pImageIndices      = present_info.image_indices.data();

    VkResult result = vkQueuePresentKHR(*_vk_queue, &vk_present_info);
    check_result(result, __func__);
  }

  void Queue::submit(const std::vector<HAL::Submit_info> &submit_infos, HAL::Fence *fence)
  {
    std::vector<VkSubmitInfo> vk_submit_infos;

    for (auto &submit_info : submit_infos)
    {
      vk_submit_infos.push_back(convert(submit_info));
    }

    VkResult result = vkQueueSubmit(
        *_vk_queue, vk_submit_infos.size(), vk_submit_infos.data(),
        *static_cast<Vulkan::Fence *>(fence)->get_vk_handle());
    check_result(result, __func__);
  }

  const VkSubmitInfo convert(const HAL::Submit_info &submit_info)
  {
    VkSubmitInfo vk_submit_info{};

    vk_submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    std::vector<VkSemaphore>          vk_wait_semaphores;
    std::vector<VkCommandBuffer>      vk_command_buffers;
    std::vector<VkSemaphore>          vk_signal_semaphores;
    std::vector<VkPipelineStageFlags> vk_wait_stage;

    vk_wait_semaphores.reserve(submit_info.wait_semaphores.size());
    vk_command_buffers.reserve(submit_info.command_buffers.size());
    vk_signal_semaphores.reserve(submit_info.signal_semaphores.size());
    vk_wait_stage.reserve(submit_info.wait_stages.size());

    for (auto *semaphore : submit_info.wait_semaphores)
    {
      vk_wait_semaphores.push_back(*static_cast<Vulkan::Semaphore *>(semaphore)->get_vk_handle());
    }

    for (auto *command_buffer : submit_info.command_buffers)
    {
      vk_command_buffers.push_back(*static_cast<Vulkan::Command_buffer *>(command_buffer)->get_vk_handle());
    }

    for (auto *semaphore : submit_info.signal_semaphores)
    {
      vk_signal_semaphores.push_back(*static_cast<Vulkan::Semaphore *>(semaphore)->get_vk_handle());
    }

    for (auto stage : submit_info.wait_stages)
    {
      vk_wait_stage.push_back(convert_enum<VkPipelineStageFlags>(stage));
    }

    vk_submit_info.waitSemaphoreCount   = vk_wait_semaphores.size();
    vk_submit_info.pWaitSemaphores      = vk_wait_semaphores.data();
    vk_submit_info.commandBufferCount   = vk_command_buffers.size();
    vk_submit_info.pCommandBuffers      = vk_command_buffers.data();
    vk_submit_info.signalSemaphoreCount = vk_signal_semaphores.size();
    vk_submit_info.pSignalSemaphores    = vk_signal_semaphores.data();
    vk_submit_info.pWaitDstStageMask    = vk_wait_stage.data();

    return vk_submit_info;
  }
} // namespace Prism::HAL::Vulkan
