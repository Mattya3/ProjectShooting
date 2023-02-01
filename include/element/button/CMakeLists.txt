file(GLOB LIST "*.cpp")

add_library(button
    SHARED
    ${LIST}
)

