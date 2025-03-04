function(CLASS_FILE DIRECTORY OUTPUT_VARIABLE)
  file(GLOB class_files_list
    "${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}/*.cpp"
  )
  set(${OUTPUT_VARIABLE} ${class_files_list} PARENT_SCOPE)
endfunction()

add_library(Prism SHARED)

CLASS_FILE(Core CORE)
CLASS_FILE(HAL HAL)
CLASS_FILE(HAL/Vulkan HAL_VULKAN)

target_sources(Prism PUBLIC
  ${HAL}
  ${HAL_VULKAN}
  ${CORE}
)

add_library(Prism::Prism ALIAS Prism)

#include directories
target_include_directories(Prism PUBLIC ${Vulkan_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

# link libraries
target_link_libraries(Prism ${Vulkan_LIBRARIES} ${SDL2_LIBRARIES})
