file(GLOB LIST "*.cpp")

add_library(opt
    SHARED
    ${LIST}
)

