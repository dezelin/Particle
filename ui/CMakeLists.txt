cmake_minimum_required(VERSION 3.5)
project(ui)

include_directories(.)

set(GLAD_SOURCE_FILES
		../glad/include/glad/glad.h
		../glad/include/KHR/khrplatform.h
        ../glad/src/glad.c)

source_group("glad" FILES ${GLAD_SOURCE_FILES})
list(APPEND SOURCE_FILES ${GLAD_SOURCE_FILES})

set(APP_SOURCE_FILES
        app/App.cpp
        app/App.h
        app/AppOptions.cpp
        app/AppOptions.h)

source_group("app" FILES ${APP_SOURCE_FILES})
list(APPEND SOURCE_FILES ${APP_SOURCE_FILES})

set(APP_GLFW3_SOURCE_FILES
        app/glfw3/Glfw3App.cpp
        app/glfw3/Glfw3App.h)

source_group("app\\glfw3" FILES ${APP_GLFW3_SOURCE_FILES})
list(APPEND SOURCE_FILES ${APP_GLFW3_SOURCE_FILES})

set(EVENTS_SOURCE_FILES
        events/Event.h
        events/EventHandler.h
        events/KeyboardListener.h
        events/MouseListener.h
        events/Keys.h
        events/Mouse.h)

source_group("events" FILES ${EVENTS_SOURCE_FILES})
list(APPEND SOURCE_FILES ${EVENTS_SOURCE_FILES})

set(EVENTS_GLFW3_SOURCE_FILES
        events/glfw3/Glfw3EventTranslator.cpp
        events/glfw3/Glfw3EventTranslator.h)

source_group("events\\glfw3" FILES ${EVENTS_GLFW3_SOURCE_FILES})
list(APPEND SOURCE_FILES ${EVENTS_GLFW3_SOURCE_FILES})

set(WIDGETS_SOURCE_FILES
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
        widgets/WindowOptions.h)

source_group("widgets" FILES ${WIDGETS_SOURCE_FILES})
list(APPEND SOURCE_FILES ${WIDGETS_SOURCE_FILES})

set(WIDGETS_GLFW3_SOURCE_FILES
        widgets/glfw3/Glfw3RenderingContext.cpp
        widgets/glfw3/Glfw3RenderingContext.h
        widgets/glfw3/Glfw3Window.cpp
        widgets/glfw3/Glfw3Window.h)

source_group("widgets\\glfw3" FILES ${WIDGETS_GLFW3_SOURCE_FILES})
list(APPEND SOURCE_FILES ${WIDGETS_GLFW3_SOURCE_FILES})

set(WIDGETS_IMPL_SOURCE_FILES
        widgets/impl/ButtonImpl.cpp
        widgets/impl/ButtonImpl.h
        widgets/impl/ShaderCompiler.cpp
        widgets/impl/ShaderCompiler.h
        widgets/impl/OverlayImpl.cpp
        widgets/impl/OverlayImpl.h)

source_group("widgets\\impl" FILES ${WIDGETS_IMPL_SOURCE_FILES})
list(APPEND SOURCE_FILES ${WIDGETS_IMPL_SOURCE_FILES})

add_library(ui SHARED ${SOURCE_FILES})

set(link_libraries glfw ${OPENGL_gl_LIBRARY} ${FREETYPE_LIBRARY})

if(UNIX)
	list(APPEND link_libraries dl)
endif()

if(WIN32)
	list(APPEND link_libraries opengl32.lib)
	set(WINDOWS_EXPORT_ALL_SYMBOLS true)
endif()

target_link_libraries(ui ${link_libraries})
