cmake_minimum_required(VERSION 3.24)
project(shooting
    VERSION 1.0
    DESCRIPTION "Shooting Game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()



include_directories(./include)
include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers)
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)
include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/GLUT.framework/Versions/A/Headers/)
link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib) 
link_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries)
find_package(OpenGL REQUIRED)
set(LIBS glfw GL GLU)

message(STATUS ${OPENGL_LIBRARIES})
message(STATUS ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY})

link_libraries(${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY})
link_libraries(glfw)
# add_subdirectory(src)
add_subdirectory(src/scene)
add_subdirectory(src/component)

link_libraries(${OPENGL})
add_executable(main main.cpp)

target_link_libraries(main component)
target_link_libraries(main scene)
target_link_libraries(main "-framework OpenGL" glfw)
target_link_libraries(main "-framework GLUT")

