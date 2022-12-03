file(GLOB LIST "*.cpp")

add_library(setting
    SHARED
    utility.cpp
)

# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(setting
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)