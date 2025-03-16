function(find_src OUTPUT_VARIABLE)
  file(GLOB class_files_list
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  )
  set(${OUTPUT_VARIABLE} ${class_files_list} PARENT_SCOPE)
endfunction()

function(find_src_at DIRECTORY OUTPUT_VARIABLE)
  file(GLOB class_files_list
    "${DIRECTORY}/*.h"
    "${DIRECTORY}/*.cpp"
  )
  set(${OUTPUT_VARIABLE} ${class_files_list} PARENT_SCOPE)
endfunction()
