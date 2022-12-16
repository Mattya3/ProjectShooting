file(GLOB LIST "*.cpp")

add_library(GameEngine
    SHARED
    ${LIST}
)
include_directories(${PROJECT_SOURCE_DIR}/include/component)

target_link_libraries(GameEngine component)
target_include_directories(GameEngine
    PUBLIC ${PROJECT_SOURCE_DIR}/include/GameEngine
)