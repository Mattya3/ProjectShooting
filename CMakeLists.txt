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

if(APPLE)
    find_package(GLUT REQUIRED)
    find_package(GLU REQUIRED)
    find_package(OPENGL REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR}  ${OPENGL_INCLUDE_DIRS})
    if(NOT GLUT_FOUND)
        message(ERROR "GLUT not found!")
    endif(NOT GLUT_FOUND)
endif()

include_directories(./include)

add_subdirectory(./src)

add_executable(main main.cpp)

target_link_libraries(main lib ${OPENGL_LIBRARIES} ${GLU_LIBRARIES} ${GLUT_LIBRARIES})
