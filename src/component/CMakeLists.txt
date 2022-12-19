file(GLOB LIST "*.cpp")

add_library(component
    SHARED
    ${LIST}
)
include_directories(/opt/homebrew/Cellar/libpng/1.6.39/include/libpng16)
link_directories(/opt/homebrew/Cellar/libpng/1.6.39/lib)
# link_libraries(png)

message(STATUS "!!! this is ${LIST}")
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(component
    PUBLIC ${PROJECT_SOURCE_DIR}/include/component
)
target_link_libraries(component lodepng)
