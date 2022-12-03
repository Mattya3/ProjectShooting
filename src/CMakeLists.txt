file(GLOB LIST "*.cpp")

add_library(Setting
    Setting.cpp
)
target_include_directories(Setting
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)