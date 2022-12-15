file(GLOB LIST "*.cpp")

set(CMAKE_CXX_STANDARD 20)

add_library(card
    SHARED
    ${LIST}
)
target_link_libraries(card component)

target_include_directories(card
    PUBLIC ${PROJECT_SOURCE_DIR}/include/internal/card
)