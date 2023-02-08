file(GLOB LIST "*.cpp")
file(GLOB Split "../Split.cpp")

set(CMAKE_CXX_STANDARD 20)

add_library(card
    SHARED
    ${LIST}
    ${Split}
)
target_include_directories(card
    PUBLIC ${PROJECT_SOURCE_DIR}/include/internal/card
)