cmake_minimum_required(VERSION 3.30)
project(Prism)

set(CMAKE_CXX_STANDARD 23)

set(CORE_SRC_DIR src/Core)
set(HAL_SRC_DIR src/HAL)
set(HAL_VULKAN_SRC_DIR src/HAL/Vulkan)

# add src/ as subdir
add_subdirectory(${CORE_SRC_DIR})
add_subdirectory(${HAL_SRC_DIR})
add_subdirectory(${HAL_VULKAN_SRC_DIR})

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(PrismApp app.cpp)
target_include_directories(PrismApp PUBLIC ${PROJECT_SOURCE_DIR}/include)

# target_link_libraries(PrismApp ${Vulkan_LIBRARIES} ${SDL2_LIBRARIES})
target_link_libraries(PrismApp Prism.Core)
