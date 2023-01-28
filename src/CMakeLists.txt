add_library(Setting
    Setting.cpp internal/Split.cpp
)
target_include_directories(Setting
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_include_directories(Setting PUBLIC ${PROJECT_SOURCE_DIR}/SBFW)
target_link_libraries(Setting sbfw)
