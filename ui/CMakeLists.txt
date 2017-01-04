cmake_minimum_required(VERSION 3.5)
project(ui)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(.)
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

set(SOURCE_FILES
        app/App.cpp
        app/App.h
        app/AppOptions.cpp
        app/AppOptions.h
        app/glfw3/Glfw3App.cpp
        app/glfw3/Glfw3App.h
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
        events/KeyboardEvent.cpp
        events/KeyboardEvent.h
        events/MouseEvent.cpp
        events/MouseEvent.h
        events/MouseButtonEvent.cpp
        events/MouseButtonEvent.h
        events/MouseWheelEvent.cpp
        events/MouseWheelEvent.h
        frags/Drawable.cpp
        frags/Drawable.h
        frags/Fragment.cpp
        frags/Fragment.h
        frags/Window.cpp
        frags/Window.h
        frags/WindowOptions.cpp
        frags/WindowOptions.h
        frags/Component.cpp
        frags/Component.h
        frags/Button.cpp
        frags/Button.h
        frags/ButtonCreationParams.cpp
        frags/ButtonCreationParams.h
        frags/KeyboardInputHandler.h
        frags/MouseInputHandler.h
        frags/RenderingContext.h
        frags/glfw3/Glfw3Window.cpp
        frags/glfw3/Glfw3Window.h
        )

add_library(ui SHARED ${SOURCE_FILES})

target_link_libraries(ui glfw ${OPENGL_gl_LIBRARY})
