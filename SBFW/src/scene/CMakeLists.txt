file(GLOB LIST "*.cpp")

add_library(sbfw_scene
    SHARED
    ${LIST}
)
include_directories(${PROJECT_SOURCE_DIR}/include/texture)

target_include_directories(sbfw_scene PUBLIC include)

# target_link_libraries(sbfw_scene lodepng)
target_link_libraries(sbfw_scene texture)

#  ライブラリ同士が依存している場合は上記を書く。
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
