/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once

#include "../Pipeline.h"
#include <memory>
#include <vulkan/vulkan.h>

namespace Prism::HAL::Vulkan
{
  // Basic type conversions
  VkVertexInputRate     convert(const HAL::Vertex_input_rate &rate);
  VkPolygonMode         convert(const HAL::Polygon_mode &mode);
  VkCullModeFlags       convert(const HAL::Cull_mode &mode);
  VkFrontFace           convert(const HAL::Front_face &face);
  VkSampleCountFlagBits convert(const HAL::Sample_count &samples);
  VkBlendFactor         convert(const HAL::Blend_factor &factor);
  VkBlendOp             convert(const HAL::Blend_op &op);
  VkLogicOp             convert(const HAL::Logic_op &op);
  VkColorComponentFlags convert(const HAL::Color_component &component);
  VkPrimitiveTopology   convert(const HAL::Primitive_topology &topology);

  // Pipeline state conversions
  VkPushConstantRange                    convert(const HAL::Push_constant_range &info);
  VkVertexInputBindingDescription        convert(const HAL::Vertex_input_binding_description &info);
  VkVertexInputAttributeDescription      convert(const HAL::Vertex_input_attribute_description &info);
  VkPipelineVertexInputStateCreateInfo   convert(const HAL::Pipeline_vertex_input_state_create_info &info);
  VkPipelineInputAssemblyStateCreateInfo convert(const HAL::Pipeline_input_assembly_state_create_info &info);
  VkPipelineViewportStateCreateInfo      convert(const HAL::Pipeline_viewport_state_create_info &info);
  VkPipelineRasterizationStateCreateInfo convert(const HAL::Pipeline_rasterization_state_create_info &info);
  VkPipelineMultisampleStateCreateInfo   convert(const HAL::Pipeline_multisample_state_create_info &info);
  VkPipelineColorBlendAttachmentState    convert(const HAL::Pipeline_color_blend_attachment_state &info);
  VkPipelineColorBlendStateCreateInfo    convert(const HAL::Pipeline_color_blend_state_create_info &info);
  VkPipelineShaderStageCreateInfo        convert(const HAL::Pipeline_shader_stage_create_info &info);
  VkGraphicsPipelineCreateInfo           convert(const HAL::Graphics_pipeline_create_info &info);
  VkPipelineLayoutCreateInfo             convert(const HAL::Pipeline_layout_create_info &info);

  // Vulkan-specific implementations
  class Pipeline_layout final : public HAL::Pipeline_layout
  {
  public:
    Pipeline_layout(VkPipelineLayout &&vk_handle, VkDevice *vk_device)
        : _vk_handle(std::make_unique<VkPipelineLayout>(vk_handle)), _vk_device(vk_device)
    {}

    [[nodiscard]] VkPipelineLayout *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkPipelineLayout> _vk_handle;
    VkDevice                         *_vk_device;
  };

  class Pipeline final : public HAL::Pipeline
  {
  public:
    Pipeline(VkPipeline &&vk_handle, VkDevice *vk_device)
        : _vk_handle(std::make_unique<VkPipeline>(vk_handle)), _vk_device(vk_device)
    {}

    ~Pipeline() override;

    [[nodiscard]] VkPipeline *get_vk_handle() const { return _vk_handle.get(); }

  private:
    std::unique_ptr<VkPipeline> _vk_handle = nullptr;
    VkDevice                   *_vk_device = nullptr;
  };
} // namespace Prism::HAL::Vulkan
