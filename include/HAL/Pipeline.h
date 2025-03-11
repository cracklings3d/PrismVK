/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 04 2025       *
 *****************************/

#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "HAL/Descriptor.h"
#include "HAL/Image.h"
#include "HAL/Primitive.h"

namespace Prism::HAL
{
  /********************** + Forward Declarations + **********************/
  class Render_pass;
  class Shader_module;
  class Viewport;
  class Rect2D;
  class Pipeline_layout;
  /********************** - Forward Declarations - **********************/

  /********************** + Enums + **********************/
  /**
   * @brief The rate at which vertex attributes are updated.
   */
  enum class Vertex_input_rate : uint32_t
  {
    Vertex,
    Instance
  };

  /**
   * @brief The blend factor for a color attachment.
   */
  enum class Blend_factor
  {
    Unknown,
    Zero,
    One,
    Src_color,
    One_minus_src_color,
    Dst_color,
    One_minus_dst_color,
    Src_alpha,
    One_minus_src_alpha,
    Dst_alpha,
    One_minus_dst_alpha,
    Constant_color,
    One_minus_constant_color,
    Constant_alpha,
    One_minus_constant_alpha,
  };

  /**
   * @brief The blend operation for a color attachment.
   */
  enum class Blend_op
  {
    Unknown,
    Add,
    Subtract,
    Reverse_subtract,
    Min,
    Max,
  };

  enum class Logic_op
  {
    Clear         = 0,
    And           = 1,
    And_reverse   = 2,
    Copy          = 3,
    And_inverted  = 4,
    No_op         = 5,
    Xor           = 6,
    Or            = 7,
    Nor           = 8,
    Equivalent    = 9,
    Invert        = 10,
    Or_reverse    = 11,
    Copy_inverted = 12,
    Or_inverted   = 13,
    Nand          = 14,
    Set           = 15
  };

  enum class Color_component : uint32_t
  {
    R = 0x01,
    G = 0x02,
    B = 0x04,
    A = 0x08
  };

  inline Color_component operator|(Color_component a, Color_component b)
  {
    return static_cast<Color_component>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
  }

  /**
   * @brief The number of samples for multisampling.
   */
  enum class Sample_count
  {
    Unknown,
    Count_1,
    Count_2,
    Count_4,
    Count_8,
    Count_16,
  };

  /**
   * @brief The sample mask for multisampling.
   */
  using Sample_mask = uint32_t;

  /********************** - Enums - **********************/

  /********************** + Structs + **********************/
  /**
   * @brief A range of memory that can be used to pass data to a shader.
   */
  struct Push_constant_range
  {
    Shader_stage stage_flags;
    uint32_t     offset;
    uint32_t     size;
  };

  /**
   * @brief The description of a vertex input binding.
   */
  struct Vertex_input_binding_description
  {
    uint32_t          binding;
    uint32_t          stride;
    Vertex_input_rate input_rate;
  };

  /**
   * @brief The description of a vertex input attribute.
   */
  struct Vertex_input_attribute_description
  {
    uint32_t     location;
    uint32_t     binding;
    Image_format format;
    uint32_t     offset;
  };

  /**
   * @brief The description of a pipeline vertex input state.
   */
  struct Pipeline_vertex_input_state_create_info
  {
    std::vector<Vertex_input_binding_description>   binding_descriptions;
    std::vector<Vertex_input_attribute_description> attribute_descriptions;
  };

  /**
   * @brief The description of a pipeline input assembly state.
   */
  struct Pipeline_input_assembly_state_create_info
  {
    Primitive_topology topology;
    bool               primitive_restart_enable;
  };

  /**
   * @brief The description of a pipeline viewport state.
   */
  struct Pipeline_viewport_state_create_info
  {
    std::vector<Viewport> viewports;
    std::vector<Rect2D>   scissors;
  };

  /**
   * @brief The description of a pipeline rasterization state.
   */
  struct Pipeline_rasterization_state_create_info
  {
    bool         depth_clamp_enable;
    bool         rasterizer_discard_enable;
    Polygon_mode polygon_mode;
    Cull_mode    cull_mode;
    Front_face   front_face;
    bool         depth_bias_enable;
    float        depth_bias_constant_factor;
    float        depth_bias_clamp;
    float        depth_bias_slope_factor;
    float        line_width;
  };

  /**
   * @brief The description of a pipeline multisample state.
   */
  struct Pipeline_multisample_state_create_info
  {
    Sample_count rasterization_samples;
    bool         sample_shading_enable;
    float        min_sample_shading;
    Sample_mask  sample_mask;
    bool         alpha_to_coverage_enable;
    bool         alpha_to_one_enable;
  };

  /**
   * @brief The description of a pipeline color blend attachment state.
   */
  struct Pipeline_color_blend_attachment_state
  {
    bool            blend_enable;
    Blend_factor    src_color_blend_factor;
    Blend_factor    dst_color_blend_factor;
    Blend_op        color_blend_op;
    Blend_factor    src_alpha_blend_factor;
    Blend_factor    dst_alpha_blend_factor;
    Blend_op        alpha_blend_op;
    Color_component color_write_mask;
  };

  /**
   * @brief The description of a pipeline color blend state.
   */
  struct Pipeline_color_blend_state_create_info
  {
    bool                                               logic_op_enable;
    Logic_op                                           logic_op;
    std::vector<Pipeline_color_blend_attachment_state> attachments;
    float                                              blend_constants[4];
  };

  /**
   * @brief The description of a pipeline shader stage.
   */
  struct Pipeline_shader_stage_create_info
  {
    Shader_module *module;
    Shader_stage   shader_stage;
    std::string    entry_point;
  };

  /**
   * @brief The description of a graphics pipeline.
   */
  struct Graphics_pipeline_create_info
  {
    std::vector<Pipeline_shader_stage_create_info> stages;
    Pipeline_vertex_input_state_create_info       *vertex_input_state;
    Pipeline_input_assembly_state_create_info     *input_assembly_state;
    Pipeline_viewport_state_create_info           *viewport_state;
    Pipeline_rasterization_state_create_info      *rasterization_state;
    Pipeline_multisample_state_create_info        *multisample_state;
    Pipeline_color_blend_state_create_info        *color_blend_state;
    Pipeline_layout                               *layout;
    Render_pass                                   *render_pass;
    uint32_t                                       subpass;
  };

  /**
   * @brief The description of a pipeline layout.
   */
  struct Pipeline_layout_create_info
  {
    std::vector<Descriptor_set_layout *> descriptor_set_layouts;
    std::vector<Push_constant_range>     push_constant_ranges;
  };

  /********************** - Structs - **********************/

  /********************** + Objects + **********************/
  /**
   * @brief A pipeline layout is a collection of descriptor set layouts and push constant ranges.
   */
  class Pipeline_layout
  {
  public:
    virtual ~Pipeline_layout() = default;
  };

  /**
   * @brief A pipeline is a collection of shader stages, vertex input state, input assembly state, viewport state,
   * rasterization state, multisample state, color blend state, and layout.
   */
  class Pipeline
  {
  public:
    virtual ~Pipeline() = default;
  };

  /********************** - Objects - **********************/
} // namespace Prism::HAL
