#include "HAL/Vulkan/Error.h"

#include <stdexcept>

namespace Prism::HAL::Vulkan
{
  std::string get_message(const VkResult &result)
  {
    switch (result)
    {
    case VK_SUCCESS:
      return "Success";
    case VK_NOT_READY:
      return "Not Ready";
    case VK_TIMEOUT:
      return "Timeout";
    case VK_EVENT_SET:
      return "Event Set";
    case VK_EVENT_RESET:
      return "Event Reset";
    case VK_INCOMPLETE:
      return "Incomplete";
    case VK_ERROR_OUT_OF_HOST_MEMORY:
      return "Out of Host Memory";
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
      return "Out of Device Memory";
    case VK_ERROR_INITIALIZATION_FAILED:
      return "Initialization Failed";
    case VK_ERROR_DEVICE_LOST:
      return "Device Lost";
    case VK_ERROR_MEMORY_MAP_FAILED:
      return "Memory Map Failed";
    case VK_ERROR_LAYER_NOT_PRESENT:
      return "Layer Not Present";
    case VK_ERROR_EXTENSION_NOT_PRESENT:
      return "Extension Not Present";
    case VK_ERROR_FEATURE_NOT_PRESENT:
      return "Feature Not Present";
    case VK_ERROR_INCOMPATIBLE_DRIVER:
      return "Incompatible Driver";
    case VK_ERROR_TOO_MANY_OBJECTS:
      return "Too Many Objects";
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
      return "Format Not Supported";
    case VK_ERROR_FRAGMENTED_POOL:
      return "Fragmented Pool";
    case VK_ERROR_UNKNOWN:
      return "Unknown Error";
    case VK_ERROR_OUT_OF_POOL_MEMORY:
      return "Out of Pool Memory";
    case VK_ERROR_INVALID_EXTERNAL_HANDLE:
      return "Invalid External Handle";
    case VK_ERROR_FRAGMENTATION:
      return "Fragmentation";
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
      return "Invalid Opaque Capture Address";
    case VK_ERROR_SURFACE_LOST_KHR:
      return "Surface Lost";
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
      return "Native Window In Use";
    case VK_SUBOPTIMAL_KHR:
      return "Suboptimal";
    case VK_ERROR_OUT_OF_DATE_KHR:
      return "Out of Date";
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
      return "Incompatible Display";
    case VK_ERROR_VALIDATION_FAILED_EXT:
      return "Validation Failed";
    case VK_ERROR_INVALID_SHADER_NV:
      return "Invalid Shader";
    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
      return "Invalid DRM Format Modifier Plane Layout";
    case VK_ERROR_NOT_PERMITTED_EXT:
      return "Not Permitted";
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
      return "Full Screen Exclusive Mode Lost";
    case VK_THREAD_IDLE_KHR:
      return "Thread Idle";
    case VK_THREAD_DONE_KHR:
      return "Thread Done";
    case VK_OPERATION_DEFERRED_KHR:
      return "Operation Deferred";
    case VK_OPERATION_NOT_DEFERRED_KHR:
      return "Operation Not Deferred";
    case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
      return "Invalid Video STD Parameters";
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
      return "Compression Exhausted";
    case VK_INCOMPATIBLE_SHADER_BINARY_EXT:
      return "Incompatible Shader Binary";
    case VK_PIPELINE_BINARY_MISSING_KHR:
      return "Pipeline Binary Missing";
    case VK_ERROR_NOT_ENOUGH_SPACE_KHR:
      return "Not Enough Space";
    case VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT:
      return "Pipeline Compile Required";
    default:
      return "Unknown Error";
    }
  }

  void check_result(const VkResult &result, const std::string &message)
  {
    if (result != VK_SUCCESS)
      throw std::runtime_error(message + ": " + get_message(result));
  }
} // namespace Prism::HAL::Vulkan