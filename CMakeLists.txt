cmake_minimum_required(VERSION 3.5)
project(Particle)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(freetype2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(glad/include)
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${FREETYPE_INCLUDE_DIR})

add_subdirectory(ui)
include_directories(ui)

set(SOURCE_FILES main.cpp glad/src/glad.c)
add_executable(Particle ${SOURCE_FILES})

target_link_libraries(Particle ui)

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	add_custom_command(
            TARGET Particle
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ui/libui.dll ${CMAKE_BINARY_DIR})
    add_custom_command(
            TARGET Particle
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $ENV{glfw3_DIR}/../../glfw3.dll ${CMAKE_BINARY_DIR})
endif()