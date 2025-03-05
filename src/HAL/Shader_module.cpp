#include "Shader_module.h"
#include "Vulkan/Shader_module.h"

namespace Prism::HAL
{
    std::unique_ptr<Shader_module> create_shader_module(const Shader_module_create_info& create_info)
    {
        // Assuming Vulkan is the only backend for now
        auto vulkan_create_info = Vulkan::convert(create_info);
        return std::make_unique<Vulkan::Shader_module>(/* device */, vulkan_create_info);
        
        // Note: You'll need to pass the VkDevice here. You might want to modify
        // the function signature to include the device or use a factory method
        // on the Device class instead.
    }
} 