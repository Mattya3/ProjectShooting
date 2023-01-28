file(GLOB LIST "lodepng.cpp")

add_library(sbfw_lodepng
    SHARED
    ${LIST}
)

target_include_directories(sbfw_lodepng
    PUBLIC ${PROJECT_SOURCE_DIR}/extern
)
