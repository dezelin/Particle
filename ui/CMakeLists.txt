cmake_minimum_required(VERSION 3.5)
project(ui)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${GLM_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

set(SOURCE_FILES
        Window.cpp
        Window.h
        display/VideoMode.cpp
        display/VideoMode.h
        display/Monitor.cpp
        display/Monitor.h
        display/GammaRamp.cpp
        display/GammaRamp.h
        display/MonitorManagerSubscriber.h
        display/MonitorManager.cpp
        display/MonitorManager.h
        display/glfw3/Glfw3MonitorManager.cpp
        display/glfw3/Glfw3MonitorManager.h
        display/glfw3/Glfw3Monitor.cpp
        display/glfw3/Glfw3Monitor.h
        display/glfw3/Glfw3VideoMode.cpp
        display/glfw3/Glfw3VideoMode.h
        events/Event.h
        events/EventHandler.h
        frags/Drawable.cpp
        frags/Drawable.h
        frags/Fragment.cpp
        frags/Fragment.h frags/Window.cpp frags/Window.h frags/WindowOptions.cpp frags/WindowOptions.h frags/Component.cpp frags/Component.h frags/Button.cpp frags/Button.h frags/FragmentContext.cpp frags/FragmentContext.h frags/ButtonCreationParams.cpp frags/ButtonCreationParams.h events/KeyboardEvent.cpp events/KeyboardEvent.h events/MouseEvent.cpp events/MouseEvent.h frags/KeyboardInputHandler.h frags/MouseInputHandler.h events/MouseButtonEvent.cpp events/MouseButtonEvent.h events/MouseWheelEvent.cpp events/MouseWheelEvent.h)

add_library(ui SHARED ${SOURCE_FILES})

target_link_libraries(ui ${OPENGL_gl_LIBRARY})

