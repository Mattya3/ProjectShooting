file(GLOB LIST "*.cpp")

add_library(component
    SHARED
    ${LIST}
)
include_directories(/opt/homebrew/Cellar/libpng/1.6.39/include/libpng16)
link_directories(/opt/homebrew/Cellar/libpng/1.6.39/lib)

target_include_directories(component PUBLIC ${PROJECT_SOURCE_DIR}/SBFW)
target_link_libraries(component sbfw)

target_include_directories(component
    PUBLIC ${PROJECT_SOURCE_DIR}/include/component
)
target_link_libraries(component sbfw)
