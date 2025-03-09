include(${PROJECT_SOURCE_DIR}/FindSrc.cmake)

add_library(Prism.HAL INTERFACE)

find_src(HAL_CPP)
find_src_at(${PROJECT_SOURCE_DIR}/include/HAL HAL_H)

target_sources(Prism.HAL INTERFACE ${HAL_CPP} ${HAL_H})

target_include_directories(Prism.HAL INTERFACE
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Prism.HAL INTERFACE Prism.HAL.Vulkan)