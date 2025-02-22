#pragma once

#include <string>
#include <vector>
#include <memory>

#include <vulkan/vulkan.h>

#include "../HAL/HAL.h"


namespace Prism
{
  class Engine
  {
  public:
    explicit Engine(const HAL::Render_api Api) : _render_api(Api) {}

    void initialize();

  private:
    [[nodiscard]] VkShaderModule create_shader_module(const std::string &file_path) const;

    [[nodiscard]] uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) const;

    void create_instance();
    void create_surface();
    void select_physical_device();
    void create_device_and_queue();
    void create_swapchain();
    void create_swapchain_image_views();
    void create_render_pass();
    void create_shader_modules();
    void create_pipeline();
    void create_frame_buffers();
    void create_vertex_buffer();
    void create_command_pool();
    void create_command_buffers();
    void create_index_buffer();
    void create_semaphores();
    void create_fences();


    void handle_input_events();
    void request_frame_buffer();
    void record_command_buffer(VkCommandBuffer command_buffer, VkFramebuffer frame_buffer) const;
    void submit_command_buffer();
    void present_frame_buffer();


    [[nodiscard]] VkFramebuffer   get_current_frame_buffer() const;
    [[nodiscard]] VkCommandBuffer get_current_command_buffer() const;
    [[nodiscard]] const VkFence * get_previous_command_buffer_fence() const;
    [[nodiscard]] const VkFence * get_current_command_buffer_fence() const;

    [[nodiscard]] const VkSemaphore *get_image_available_semaphore() const;
    [[nodiscard]] const VkSemaphore *get_render_finished_semaphore() const;

  private:
    HAL::Render_api _render_api = HAL::Render_api::Unknown;

    std::unique_ptr<HAL::Window>   _window   = nullptr;
    std::unique_ptr<HAL::Instance> _instance = nullptr;

  private:
    VkClearValue clear_color = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

    // vulkan objects and stuff
    VkSurfaceKHR   surface    = nullptr;
    VkSwapchainKHR swap_chain = nullptr;

    uint32_t swap_chain_size = 0;

    // per instance variable
    VkInstance       instance                  = nullptr;
    VkPhysicalDevice physical_device           = nullptr;
    VkDevice         device                    = nullptr;
    VkQueue          graphic_queue             = nullptr;
    float            graphic_queue_priority    = 1.0f;
    VkCommandPool    command_pool              = nullptr;
    VkPipeline       graphics_pipeline         = nullptr;
    VkDeviceMemory   mesh_vertex_buffer_memory = nullptr;

    VkViewport viewport = {};
    VkRect2D   scissor  = {};

    VkPipelineLayout pipeline_layout = nullptr;

    // World data
    VkBuffer mesh_vertex_buffer = nullptr;

    std::vector<VkSemaphore> image_available_semaphores;
    std::vector<VkSemaphore> render_finished_semaphores;

    VkShaderModule vert_shader_module = nullptr;
    VkShaderModule frag_shader_module = nullptr;


    // volatile (per frame) data
    uint32_t     frame_index      = 0;
    uint32_t     swap_chain_index = 0;
    uint32_t     semaphore_index  = 0;
    VkRenderPass render_pass      = nullptr;

    std::vector<VkImage>         swap_chain_images;
    std::vector<VkImageView>     swap_chain_image_views;
    std::vector<VkFramebuffer>   swap_chain_frame_buffers;
    std::vector<VkCommandBuffer> command_buffers;
    std::vector<VkFence>         command_buffer_fences;

    bool should_quit = false;
  };

} // Prism
