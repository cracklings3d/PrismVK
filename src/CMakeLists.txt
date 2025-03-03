
# add compile unit
add_library(PrismVk SHARED
    Core/Engine.cpp
    Core/Engine.h
    Resource/TriangleMesh.h
    HAL/Vulkan/Instance.h
    HAL/Vulkan/Instance.cpp
    HAL/HAL.h
    HAL/Vulkan/Window_Sdl2.cpp
    HAL/Vulkan/Window_Sdl2.h
    HAL/HAL.cpp
    HAL/Window.cpp
    HAL/Window.h
    HAL/Instance.cpp
    HAL/Instance.h
    HAL/Vulkan/Surface.cpp
    HAL/Vulkan/Surface.h
    HAL/Vulkan/Physical_device.cpp
    HAL/Vulkan/Physical_device.h
    HAL/Physical_device.h
    HAL/Surface.cpp
    HAL/Surface.h
    HAL/Device.cpp
    HAL/Device.h
    HAL/Vulkan/Device.cpp
    HAL/Vulkan/Device.h
)


#include directories
target_include_directories(PrismVk PUBLIC ${Vulkan_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

# link libraries
target_link_libraries(PrismVk ${Vulkan_LIBRARIES} ${SDL2_LIBRARIES})
