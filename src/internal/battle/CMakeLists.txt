file(GLOB LIST "*.cpp")

add_library(battle_inner
    SHARED
    ${LIST}
)
target_link_libraries(battle_inner card)
target_link_libraries(battle_inner Setting)

target_include_directories(battle_inner
    PUBLIC ${PROJECT_SOURCE_DIR}/include/internal/battle_inner
)