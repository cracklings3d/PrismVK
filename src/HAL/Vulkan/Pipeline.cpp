/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#include <vector>

#include "HAL/Vulkan/Descriptor.h"
#include "HAL/Vulkan/Param_converters.h"
#include "HAL/Vulkan/Pipeline.h"
#include "HAL/Vulkan/Render_pass.h"
#include "HAL/Vulkan/Shader.h"
#include "HAL/Vulkan/Viewport.h"

namespace Prism::HAL::Vulkan
{
  VkBlendFactor convert(const HAL::Blend_factor &factor)
  {
    switch (factor)
    {
    case HAL::Blend_factor::Zero:
      return VK_BLEND_FACTOR_ZERO;
    case HAL::Blend_factor::One:
      return VK_BLEND_FACTOR_ONE;
    case HAL::Blend_factor::Src_color:
      return VK_BLEND_FACTOR_SRC_COLOR;
    case HAL::Blend_factor::One_minus_src_color:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
    case HAL::Blend_factor::Dst_color:
      return VK_BLEND_FACTOR_DST_COLOR;
    case HAL::Blend_factor::One_minus_dst_color:
      return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
    case HAL::Blend_factor::Src_alpha:
      return VK_BLEND_FACTOR_SRC_ALPHA;
    case HAL::Blend_factor::One_minus_src_alpha:
      return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    case HAL::Blend_factor::Dst_alpha:
      return VK_BLEND_FACTOR_DST_ALPHA;
    case HAL::Blend_factor::One_minus_dst_alpha:
      return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
    case HAL::Blend_factor::Constant_color:
      return VK_BLEND_FACTOR_CONSTANT_COLOR;
    case HAL::Blend_factor::One_minus_constant_color:
      return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
    case HAL::Blend_factor::Constant_alpha:
      return VK_BLEND_FACTOR_CONSTANT_ALPHA;
    case HAL::Blend_factor::One_minus_constant_alpha:
      return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
    default:
      throw std::runtime_error("Unsupported blend factor");
    }
  }

  VkBlendOp convert(const HAL::Blend_op &op)
  {
    switch (op)
    {
    case HAL::Blend_op::Add:
      return VK_BLEND_OP_ADD;
    case HAL::Blend_op::Subtract:
      return VK_BLEND_OP_SUBTRACT;
    case HAL::Blend_op::Reverse_subtract:
      return VK_BLEND_OP_REVERSE_SUBTRACT;
    case HAL::Blend_op::Min:
      return VK_BLEND_OP_MIN;
    case HAL::Blend_op::Max:
      return VK_BLEND_OP_MAX;
    default:
      throw std::runtime_error("Unsupported blend op");
    }
  }

  VkColorComponentFlags convert(const HAL::Color_component &component)
  {
    switch (component)
    {
    case HAL::Color_component::R:
      return VK_COLOR_COMPONENT_R_BIT;
    case HAL::Color_component::G:
      return VK_COLOR_COMPONENT_G_BIT;
    case HAL::Color_component::B:
      return VK_COLOR_COMPONENT_B_BIT;
    case HAL::Color_component::A:
      return VK_COLOR_COMPONENT_A_BIT;
    default:
      throw std::runtime_error("Unsupported color component");
    }
  }

  VkPrimitiveTopology convert(const HAL::Primitive_topology &topology)
  {
    switch (topology)
    {
    case HAL::Primitive_topology::Point_list:
      return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case HAL::Primitive_topology::Line_list:
      return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case HAL::Primitive_topology::Line_strip:
      return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case HAL::Primitive_topology::Triangle_list:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case HAL::Primitive_topology::Triangle_strip:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    case HAL::Primitive_topology::Triangle_fan:
      return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
    default:
      throw std::runtime_error("Unsupported primitive topology");
    }
  }

  VkPushConstantRange convert(const HAL::Push_constant_range &info)
  {
    VkPushConstantRange vk_info{};

    vk_info.stageFlags = convert(info.stage_flags);
    vk_info.offset     = info.offset;
    vk_info.size       = info.size;

    return vk_info;
  }

  VkVertexInputBindingDescription convert(const HAL::Vertex_input_binding_description &info)
  {
    VkVertexInputBindingDescription vk_info{};

    vk_info.binding   = info.binding;
    vk_info.stride    = info.stride;
    vk_info.inputRate = convert(info.input_rate);

    return vk_info;
  }

  VkVertexInputAttributeDescription convert(const HAL::Vertex_input_attribute_description &info)
  {
    VkVertexInputAttributeDescription vk_info{};

    vk_info.location = info.location;
    vk_info.binding  = info.binding;
    vk_info.format   = convert(info.format);
    vk_info.offset   = info.offset;

    return vk_info;
  }

  VkPipelineVertexInputStateCreateInfo convert(const HAL::Pipeline_vertex_input_state_create_info &info)
  {
    std::vector<VkVertexInputBindingDescription>   vk_bindings;
    std::vector<VkVertexInputAttributeDescription> vk_attributes;

    for (const auto &binding : info.binding_descriptions)
    {
      vk_bindings.push_back(convert(binding));
    }

    for (const auto &attribute : info.attribute_descriptions)
    {
      vk_attributes.push_back(convert(attribute));
    }

    VkPipelineVertexInputStateCreateInfo vk_info{};

    vk_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vk_info.vertexBindingDescriptionCount   = vk_bindings.size();
    vk_info.pVertexBindingDescriptions      = vk_bindings.data();
    vk_info.vertexAttributeDescriptionCount = vk_attributes.size();
    vk_info.pVertexAttributeDescriptions    = vk_attributes.data();

    return vk_info;
  }

  VkPipelineInputAssemblyStateCreateInfo convert(const Pipeline_input_assembly_state_create_info &info)
  {
    VkPipelineInputAssemblyStateCreateInfo vk_info{};
    vk_info.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    vk_info.topology               = convert(info.topology);
    vk_info.primitiveRestartEnable = info.primitive_restart_enable;
    return vk_info;
  }

  VkPipelineViewportStateCreateInfo convert(const HAL::Pipeline_viewport_state_create_info &info)
  {
    std::vector<VkViewport> vk_viewports;
    std::vector<VkRect2D>   vk_scissors;

    for (const HAL::Viewport &viewport : info.viewports)
    {
      vk_viewports.push_back(convert(viewport));
    }

    for (const HAL::Rect2D &scissor : info.scissors)
    {
      vk_scissors.push_back(convert(scissor));
    }

    VkPipelineViewportStateCreateInfo vk_info{};

    vk_info.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vk_info.viewportCount = vk_viewports.size();
    vk_info.pViewports    = vk_viewports.data();
    vk_info.scissorCount  = vk_scissors.size();
    vk_info.pScissors     = vk_scissors.data();

    return vk_info;
  }

  VkPipelineRasterizationStateCreateInfo convert(const HAL::Pipeline_rasterization_state_create_info &info)
  {
    VkPipelineRasterizationStateCreateInfo vk_info{};
    vk_info.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    vk_info.depthClampEnable        = info.depth_clamp_enable;
    vk_info.rasterizerDiscardEnable = info.rasterizer_discard_enable;
    vk_info.polygonMode             = convert(info.polygon_mode);
    vk_info.cullMode                = convert(info.cull_mode);
    vk_info.frontFace               = convert(info.front_face);
    vk_info.depthBiasEnable         = info.depth_bias_enable;
    vk_info.depthBiasConstantFactor = info.depth_bias_constant_factor;
    vk_info.depthBiasClamp          = info.depth_bias_clamp;
    vk_info.depthBiasSlopeFactor    = info.depth_bias_slope_factor;
    vk_info.lineWidth               = info.line_width;
    return vk_info;
  }

  VkPipelineMultisampleStateCreateInfo convert(const HAL::Pipeline_multisample_state_create_info &info)
  {
    VkPipelineMultisampleStateCreateInfo vk_info{};
    vk_info.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    vk_info.rasterizationSamples  = convert(info.rasterization_samples);
    vk_info.sampleShadingEnable   = info.sample_shading_enable;
    vk_info.minSampleShading      = info.min_sample_shading;
    vk_info.pSampleMask           = &info.sample_mask; // Note: might need array conversion if multiple masks
    vk_info.alphaToCoverageEnable = info.alpha_to_coverage_enable;
    vk_info.alphaToOneEnable      = info.alpha_to_one_enable;
    return vk_info;
  }

  VkPipelineColorBlendAttachmentState convert(const HAL::Pipeline_color_blend_attachment_state &info)
  {
    VkPipelineColorBlendAttachmentState vk_info{};
    vk_info.blendEnable         = info.blend_enable;
    vk_info.srcColorBlendFactor = convert(info.src_color_blend_factor);
    vk_info.dstColorBlendFactor = convert(info.dst_color_blend_factor);
    vk_info.colorBlendOp        = convert(info.color_blend_op);
    vk_info.srcAlphaBlendFactor = convert(info.src_alpha_blend_factor);
    vk_info.dstAlphaBlendFactor = convert(info.dst_alpha_blend_factor);
    vk_info.alphaBlendOp        = convert(info.alpha_blend_op);
    vk_info.colorWriteMask      = convert(info.color_write_mask);
    return vk_info;
  }

  VkPipelineColorBlendStateCreateInfo convert(const HAL::Pipeline_color_blend_state_create_info &info)
  {
    std::vector<VkPipelineColorBlendAttachmentState> vk_attachments;

    for (const auto &attachment : info.attachments)
    {
      vk_attachments.push_back(convert(attachment));
    }

    VkPipelineColorBlendStateCreateInfo vk_info{};

    vk_info.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    vk_info.logicOpEnable   = info.logic_op_enable;
    vk_info.logicOp         = convert(info.logic_op);
    vk_info.attachmentCount = vk_attachments.size();
    vk_info.pAttachments    = vk_attachments.data();
    std::copy(std::begin(info.blend_constants), std::end(info.blend_constants), vk_info.blendConstants);

    return vk_info;
  }

  VkPipelineShaderStageCreateInfo convert(const Pipeline_shader_stage_create_info &info)
  {
    VkPipelineShaderStageCreateInfo vk_info{};
    vk_info.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vk_info.stage  = convert(info.shader_stage);
    vk_info.module = *static_cast<Vulkan::Shader_module *>(info.module)->get_vk_handle();
    vk_info.pName  = info.entry_point.c_str();
    return vk_info;
  }

  VkGraphicsPipelineCreateInfo convert(const HAL::Graphics_pipeline_create_info &info)
  {
    VkGraphicsPipelineCreateInfo vk_info{};
    vk_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

    // Convert shader stages
    std::vector<VkPipelineShaderStageCreateInfo> vk_stages;

    for (const auto &stage : info.stages)
    {
      vk_stages.push_back(convert(stage));
    }

    vk_info.stageCount = vk_stages.size();
    vk_info.pStages    = vk_stages.data();

    // Convert all pipeline states
    auto vk_vertex_input_state   = convert(*info.vertex_input_state);
    auto vk_input_assembly_state = convert(*info.input_assembly_state);
    auto vk_viewport_state       = convert(*info.viewport_state);
    auto vk_rasterization_state  = convert(*info.rasterization_state);
    auto vk_multisample_state    = convert(*info.multisample_state);
    auto vk_color_blend_state    = convert(*info.color_blend_state);

    vk_info.pVertexInputState   = &vk_vertex_input_state;
    vk_info.pInputAssemblyState = &vk_input_assembly_state;
    vk_info.pViewportState      = &vk_viewport_state;
    vk_info.pRasterizationState = &vk_rasterization_state;
    vk_info.pMultisampleState   = &vk_multisample_state;
    vk_info.pColorBlendState    = &vk_color_blend_state;
    vk_info.pDynamicState       = nullptr; // Add if needed

    // Convert handles
    vk_info.layout             = *static_cast<Vulkan::Pipeline_layout *>(info.layout)->get_vk_handle();
    vk_info.renderPass         = *static_cast<Vulkan::Render_pass *>(info.render_pass)->get_vk_handle();
    vk_info.subpass            = info.subpass;
    vk_info.basePipelineHandle = VK_NULL_HANDLE;
    vk_info.basePipelineIndex  = -1;

    return vk_info;
  }

  VkPipelineLayoutCreateInfo convert(const HAL::Pipeline_layout_create_info &info)
  {
    std::vector<VkDescriptorSetLayout> vk_descriptor_set_layouts;
    std::vector<VkPushConstantRange>   vk_push_constant_ranges;

    for (const auto &descriptor_set_layout : info.descriptor_set_layouts)
    {
      auto vulkan_layout = static_cast<Vulkan::Descriptor_set_layout *>(descriptor_set_layout);
      vk_descriptor_set_layouts.push_back(vulkan_layout->get_vk_handle());
    }


    for (const auto &push_constant_range : info.push_constant_ranges)
    {
      vk_push_constant_ranges.push_back(convert(push_constant_range));
    }

    VkPipelineLayoutCreateInfo vk_info{};

    vk_info.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    vk_info.setLayoutCount         = vk_descriptor_set_layouts.size();
    vk_info.pSetLayouts            = vk_descriptor_set_layouts.data();
    vk_info.pushConstantRangeCount = vk_push_constant_ranges.size();
    vk_info.pPushConstantRanges    = vk_push_constant_ranges.data();

    return vk_info;
  }

  Color_component operator|(Color_component a, Color_component b)
  {
    return static_cast<Color_component>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
  }

  Pipeline::~Pipeline()
  {
    if (_vk_handle != nullptr && _vk_device != nullptr)
    {
      vkDestroyPipeline(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = nullptr;
    }
  }
} // namespace Prism::HAL::Vulkan
