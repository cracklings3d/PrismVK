include(${PROJECT_SOURCE_DIR}/FindSrc.cmake)

add_library(Prism.Core SHARED)

find_src(CORE_CPP)
find_src_at(${PROJECT_SOURCE_DIR}/include/Core CORE_H)

target_sources(Prism.Core PUBLIC ${CORE_CPP} ${CORE_H})

target_include_directories(Prism.Core PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Prism.Core PUBLIC Prism.HAL)
