include(${PROJECT_SOURCE_DIR}/FindSrc.cmake)

add_library(Prism.HAL.Vulkan SHARED)

set(CMAKE_CXX_STANDARD 23)

find_src(HAL_VULKAN_CPP)
find_src_at(${PROJECT_SOURCE_DIR}/include/HAL/Vulkan HAL_VULKAN_H)

target_sources(Prism.HAL.Vulkan PUBLIC ${HAL_VULKAN_CPP} ${HAL_VULKAN_H})
target_link_libraries(Prism.HAL.Vulkan PUBLIC Vulkan SDL2)
# Force code to write either #include "HAL/Vulkan/Device.h" or #include "Device.h"
target_include_directories(Prism.HAL.Vulkan PUBLIC ${PROJECT_SOURCE_DIR}/include)
message(STATUS ${PROJECT_SOURCE_DIR}/include)
