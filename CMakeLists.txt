cmake_minimum_required(VERSION 3.24)
projectshooting(
    VERSION 1.0
    DESCRIPTION "Shooting Game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/opt/homebrew/Cellar/gcc/12.2.0/bin/g++-12")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

include_directories(./include)
include_directories(./externsrc)
include_directories(SBFW)
include_directories(SBFW/include/scene)




if(APPLE)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers)
    include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/GLUT.framework/Versions/A/Headers/)
    include_directories(/opt/homebrew/Cellar/libpng/1.6.39/include)

    link_directories(/opt/homebrew/Cellar/libpng/1.6.39/lib)
    link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)
endif()

if(WIN32)
    #link_directories()
    include_directories(C:/Program Files/mingw64/include)
    link_libraries(opengl32)
    link_libraries(glfw3)
    link_libraries(gdi32)
    link_libraries(png)
endif()

find_package(OpenGL REQUIRED)
set(LIBS glfw GL GLU)

link_libraries(${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY})
link_libraries(glfw)

add_subdirectory(externsrc)
add_subdirectory(src/component)
add_subdirectory(src/scenes)
add_subdirectory(src)
add_subdirectory(src/internal/battle)
add_subdirectory(src/internal/card)
add_subdirectory(src/GameEngine)


add_executable(main main.cpp)

add_subdirectory(SBFW)
target_link_libraries(main sbfw)


if(APPLE)
    target_link_libraries(main "-framework OpenGL" glfw)
endif()

if(WIN32)
    target_link_libraries(main opengl32)
    target_link_libraries(main glfw3)
    target_link_libraries(main gdi32)
endif()
target_link_libraries(main )
target_link_libraries(main Setting)
target_link_libraries(main component)
target_link_libraries(main scene) 
