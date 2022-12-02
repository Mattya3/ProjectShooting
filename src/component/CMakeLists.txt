file(GLOB LIST "*.cpp")

add_library(component
    SHARED
    ${LIST}
)
message(STATUS "!!! this is ${LIST}")
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(component
    PUBLIC ${PROJECT_SOURCE_DIR}/include/component
)