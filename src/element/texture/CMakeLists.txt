file(GLOB LIST "*.cpp")

add_library(texture
    SHARED
    ${LIST}
)
target_link_libraries(texture sbfw_lodepng)

target_include_directories(texture
    PUBLIC ${PROJECT_SOURCE_DIR}/include/texture
)