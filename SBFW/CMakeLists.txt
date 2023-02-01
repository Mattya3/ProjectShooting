file(GLOB LIST "*/*.cpp")
set(CMAKE_CXX_COMPILER "/opt/homebrew/Cellar/gcc/12.2.0/bin/g++-12")

add_library(sbfw
    SHARED
    ${LIST}
)
include_directories(${PROJECT_SOURCE_DIR}/include/texture)

include_directories(./include)
include_directories(include)
include_directories(./ext_math)
include_directories(./lodepng)

if(APPLE)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers)
    include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/GLUT.framework/Versions/A/Headers/)
    link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

link_libraries(${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY})
link_libraries(glfw)

add_subdirectory(src/element)
add_subdirectory(src/scene)
add_subdirectory(ext_math)
add_subdirectory(lodepng)

target_include_directories(sbfw PUBLIC ext_math)
target_include_directories(sbfw PUBLIC include)

if(APPLE)
    target_link_libraries(sbfw "-framework OpenGL")
endif()

target_link_libraries(sbfw sbfw_scene)
target_link_libraries(sbfw element)
target_link_libraries(sbfw sbfw_lodepng)
