file(GLOB LIST "*.cpp")
file(GLOB Split "../Split.cpp")

add_library(battle_inner
    ${LIST}
    ${Split}
)
target_link_libraries(battle_inner card)
target_link_libraries(battle_inner battle)
target_include_directories(battle_inner
    PUBLIC ${PROJECT_SOURCE_DIR}/include/internal/battle_inner
)