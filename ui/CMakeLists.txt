cmake_minimum_required(VERSION 3.5)
project(ui)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${GLM_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

set(SOURCE_FILES Window.cpp Window.h display/VideoMode.cpp display/VideoMode.h display/glfw3/Glfw3VideoMode.cpp display/glfw3/Glfw3VideoMode.h display/Monitor.cpp display/Monitor.h display/GammaRamp.cpp display/GammaRamp.h display/MonitorManager.cpp display/MonitorManager.h display/glfw3/Glfw3MonitorManager.cpp display/glfw3/Glfw3MonitorManager.h display/glfw3/Glfw3Monitor.cpp display/glfw3/Glfw3Monitor.h display/MonitorManagerSubscriber.h)
add_library(ui SHARED ${SOURCE_FILES})

target_link_libraries(ui ${OPENGL_gl_LIBRARY})

