cmake_minimum_required(VERSION 3.30)
project(Prism)

set(CMAKE_CXX_STANDARD 23)

# add src/ as subdir
add_subdirectory(src)

# find vulkan, include and link
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

# find sdl2, include and link
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(PrismApp app.cpp)

target_link_libraries(PrismApp ${Vulkan_LIBRARIES} ${SDL2_LIBRARIES})
target_link_libraries(PrismApp Prism::Prism)
