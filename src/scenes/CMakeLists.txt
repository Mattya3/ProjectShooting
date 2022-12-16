file(GLOB LIST "*.cpp")

add_library(scene
    SHARED
    ${LIST}
)
include_directories(${PROJECT_SOURCE_DIR}/include/component)
include_directories(${PROJECT_SOURCE_DIR}/include/internal/card)
include_directories(${PROJECT_SOURCE_DIR}/include/GameEngine)

target_link_libraries(scene component)
target_link_libraries(scene card)
target_link_libraries(scene GameEngine)
#  ライブラリ同士が依存している場合は上記を書く。
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(scene
    PUBLIC ${PROJECT_SOURCE_DIR}/include/scene
)