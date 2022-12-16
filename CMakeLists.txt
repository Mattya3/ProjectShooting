cmake_minimum_required(VERSION 3.24)
project(shooting
    VERSION 1.0
    DESCRIPTION "Shooting Game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

include_directories(./include)

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
link_libraries(png)

add_subdirectory(src/component)
add_subdirectory(src/scenes)
add_subdirectory(src)
add_subdirectory(src/internal/battle)
add_subdirectory(src/internal/card)
add_subdirectory(src/GameEngine)

add_executable(main main.cpp)

if(APPLE)
    target_link_libraries(main "-framework OpenGL" glfw)
endif()

if(WIN32)
    target_link_libraries(main opengl32)
    target_link_libraries(main glfw3)
    target_link_libraries(main gdi32)
endif()
target_link_libraries(main Setting)
target_link_libraries(main component)
target_link_libraries(main scene)


