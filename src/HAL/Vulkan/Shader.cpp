/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 05 2025       *
 *****************************/

#include "HAL/Vulkan/Shader.h"

#include "HAL/Vulkan/Error.h"

namespace Prism::HAL::Vulkan
{
  VkShaderStageFlagBits convert(HAL::Shader_stage stage)
  {
    switch (stage)
    {
    case HAL::Shader_stage::Vertex:
      return VK_SHADER_STAGE_VERTEX_BIT;
    case HAL::Shader_stage::Fragment:
      return VK_SHADER_STAGE_FRAGMENT_BIT;
    case HAL::Shader_stage::Compute:
      return VK_SHADER_STAGE_COMPUTE_BIT;
    case HAL::Shader_stage::Tessellation_control:
      return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
    case HAL::Shader_stage::Tessellation_evaluation:
      return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
    case HAL::Shader_stage::Geometry:
      return VK_SHADER_STAGE_GEOMETRY_BIT;
    case HAL::Shader_stage::All_graphics:
      return VK_SHADER_STAGE_ALL_GRAPHICS;
    case HAL::Shader_stage::All:
      return VK_SHADER_STAGE_ALL;
    case HAL::Shader_stage::Raygen:
      return VK_SHADER_STAGE_RAYGEN_BIT_KHR;
    case HAL::Shader_stage::Any_hit:
      return VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
    case HAL::Shader_stage::Closest_hit:
      return VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
    case HAL::Shader_stage::Miss:
      return VK_SHADER_STAGE_MISS_BIT_KHR;
    case HAL::Shader_stage::Intersection:
      return VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
    case HAL::Shader_stage::Callable:
      return VK_SHADER_STAGE_CALLABLE_BIT_KHR;
    case HAL::Shader_stage::Task:
      return VK_SHADER_STAGE_TASK_BIT_EXT;
    case HAL::Shader_stage::Mesh:
      return VK_SHADER_STAGE_MESH_BIT_EXT;
    case HAL::Shader_stage::Subpass_shading:
      return VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI;
    case HAL::Shader_stage::Cluster_culling:
      return VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI;
    default:
      throw std::runtime_error("Unsupported shader stage");
    }
  }

  VkShaderModuleCreateInfo convert(const HAL::Shader_module_create_info &hal_create_info)
  {
    VkShaderModuleCreateInfo result;

    result.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    result.codeSize = hal_create_info.code.size();
    result.pCode    = reinterpret_cast<const uint32_t *>(hal_create_info.code.data());

    return result;
  }

  Shader_module::Shader_module(VkShaderModule shader_module, VkDevice *device)
    : _vk_handle(std::make_unique<VkShaderModule>(shader_module)), _vk_device(device) {}

  Shader_module::~Shader_module()
  {
    if (_vk_handle != VK_NULL_HANDLE)
    {
      vkDestroyShaderModule(*_vk_device, *_vk_handle, nullptr);
      _vk_handle = VK_NULL_HANDLE;
    }
  }

  VkShaderModule *Shader_module::get_vk_handle()
  {
    return _vk_handle.get();
  }
} // namespace Prism::HAL::Vulkan
