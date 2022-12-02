file(GLOB LIST "*.cpp")

add_library(scene
    SHARED
    ${LIST}
)

# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(scene
    PUBLIC ${PROJECT_SOURCE_DIR}/include/scene
)