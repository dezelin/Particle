cmake_minimum_required(VERSION 3.5)
project(ui)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(.)
include_directories(../glad/include)
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

set(SOURCE_FILES
        ../glad/src/glad.c
        app/App.cpp
        app/App.h
        app/AppOptions.cpp
        app/AppOptions.h
        app/glfw3/Glfw3App.cpp
        app/glfw3/Glfw3App.h
        display/GammaRamp.cpp
        display/GammaRamp.h
        display/Monitor.cpp
        display/Monitor.h
        display/MonitorManagerSubscriber.h
        display/MonitorManager.cpp
        display/MonitorManager.h
        display/VideoMode.cpp
        display/VideoMode.h
        display/glfw3/Glfw3MonitorManager.cpp
        display/glfw3/Glfw3MonitorManager.h
        display/glfw3/Glfw3Monitor.cpp
        display/glfw3/Glfw3Monitor.h
        display/glfw3/Glfw3VideoMode.cpp
        display/glfw3/Glfw3VideoMode.h
        events/Event.h
        events/EventHandler.h
        events/KeyboardListener.h
        events/MouseListener.h
        events/Keys.h
        events/Mouse.h
        events/glfw3/Glfw3EventTranslator.cpp
        events/glfw3/Glfw3EventTranslator.h
        widgets/Button.cpp
        widgets/Button.h
        widgets/ButtonOptions.cpp
        widgets/ButtonOptions.h
        widgets/Color.h
        widgets/Color.cpp
        widgets/Component.h
        widgets/WidgetRenderer.h
        widgets/FocusHolder.h
        widgets/Image.cpp
        widgets/Image.h
        widgets/Label.cpp
        widgets/Label.h
        widgets/OverlayProjection.cpp
        widgets/OverlayProjection.h
        widgets/Overlay.cpp
        widgets/Overlay.h
        widgets/OverlayOptions.cpp
        widgets/OverlayOptions.h
        widgets/OverlayRenderingContext.h
        widgets/OverlayRenderingOptions.cpp
        widgets/OverlayRenderingOptions.h
        widgets/OverlayRenderingContext.cpp
        widgets/Point.cpp
        widgets/Point.h
        widgets/Rectangle.cpp
        widgets/Rectangle.h
        widgets/Widget.cpp
        widgets/Widget.h
        widgets/WidgetOptions.h
        widgets/Window.cpp
        widgets/Window.h
        widgets/WindowOptions.cpp
        widgets/WindowOptions.h
        widgets/impl/ButtonImpl.cpp
        widgets/impl/ButtonImpl.h
        widgets/impl/ShaderCompiler.cpp
        widgets/impl/ShaderCompiler.h
        widgets/impl/OverlayImpl.cpp
        widgets/impl/OverlayImpl.h
        widgets/glfw3/Glfw3RenderingContext.cpp
        widgets/glfw3/Glfw3RenderingContext.h
        widgets/glfw3/Glfw3Window.cpp
        widgets/glfw3/Glfw3Window.h)

add_library(ui SHARED ${SOURCE_FILES})

target_link_libraries(ui dl glfw ${OPENGL_gl_LIBRARY})
