file(GLOB LIST "*.cpp")

add_library(element
    SHARED
    ${LIST}
)
add_subdirectory(texture)
# add_subdirectory(button)

target_link_libraries(element texture)
# target_link_libraries(element button)
target_include_directories(sbfw PUBLIC )

# ライブラリ同士が依存している場合は上記を書く。
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(element
    PUBLIC ${PROJECT_SOURCE_DIR}/include/
)