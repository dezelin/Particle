//
// Copyright (c) 2016, Aleksandar Dezelin <dezelin@gmail.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//  contributors may be used to endorse or promote products derived from
//  this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "Glfw3Window.h"

#include <algorithm>

namespace ui {

namespace frags {

namespace glfw3 {

struct ClientApiPair {
    WindowOptions::ClientApi clientApi;
    int glfwValue;
};

struct ContextApiPair {
    WindowOptions::ContextApi contextApi;
    int glfwValue;
};

struct ContextRobustnessPair {
    WindowOptions::ContextRobustness robustness;
    int glfwValue;
};

struct ContextReleaseBehaviorPair {
    WindowOptions::ContextReleaseBehavior releaseBehavior;
    int glfwValue;
};

struct StylePair {
    int style;
    int glfwValue;
};

struct ClientApiPair clientApiPairs[] = {
        { WindowOptions::ClientApi::NoApi, GLFW_NO_API },
        { WindowOptions::ClientApi::OpenGLES, GLFW_OPENGL_ES_API },
        { WindowOptions::ClientApi::OpenGL, GLFW_OPENGL_API }
};

struct ContextApiPair contextApiPairs[] = {
        { WindowOptions::ContextApi::EGL, GLFW_EGL_CONTEXT_API },
        { WindowOptions::ContextApi::Native, GLFW_NATIVE_CONTEXT_API }
};

struct ContextRobustnessPair contextRobustnessPairs[] = {
        { WindowOptions::ContextRobustness::LoseContextOnReset, GLFW_LOSE_CONTEXT_ON_RESET },
        { WindowOptions::ContextRobustness::No, GLFW_NO_ROBUSTNESS },
        { WindowOptions::ContextRobustness::NoResetNotification, GLFW_NO_RESET_NOTIFICATION }
};

struct ContextReleaseBehaviorPair releaseBehaviorPairs[] = {
        { WindowOptions::ContextReleaseBehavior::Any, GLFW_ANY_RELEASE_BEHAVIOR },
        { WindowOptions::ContextReleaseBehavior::Flush, GLFW_RELEASE_BEHAVIOR_FLUSH },
        { WindowOptions::ContextReleaseBehavior::None, GLFW_RELEASE_BEHAVIOR_NONE }
};

struct StylePair stylePairs[] = {
        { WindowOptions::WINDOWSTYLE_FOCUSED, GLFW_FOCUSED },
        { WindowOptions::WINDOWSTYLE_ICONIFIED, GLFW_ICONIFIED },
        { WindowOptions::WINDOWSTYLE_RESIZABLE, GLFW_RESIZABLE },
        { WindowOptions::WINDOWSTYLE_VISIBLE, GLFW_VISIBLE },
        { WindowOptions::WINDOWSTYLE_DECORATED, GLFW_DECORATED },
        { WindowOptions::WINDOWSTYLE_AUTO_ICONIFY, GLFW_AUTO_ICONIFY },
        { WindowOptions::WINDOWSTYLE_FLOATING, GLFW_FLOATING },
        { WindowOptions::WINDOWSTYLE_MAXIMIZED, GLFW_MAXIMIZED },
        { WindowOptions::WINDOWSTYLE_STEREO, GLFW_STEREO },
        { WindowOptions::WINDOWSTYLE_SRGB_CAPABLE, GLFW_SRGB_CAPABLE },
        { WindowOptions::WINDOWSTYLE_DOUBLE_BUFFER, GLFW_DOUBLEBUFFER },
        { WindowOptions::WINDOWSTYLE_FORWARD_COMPAT, GLFW_OPENGL_FORWARD_COMPAT },
        { WindowOptions::WINDOWSTYLE_DEBUG_CONTEXT, GLFW_OPENGL_DEBUG_CONTEXT }
};

std::mutex Glfw3Window::mutex;
std::vector<std::unique_ptr<Glfw3Window>> Glfw3Window::windows;

Glfw3Window::Glfw3Window(const WindowOptions &options) {
    initialize(options);
}

Glfw3Window::~Glfw3Window() {

}

Widget *Glfw3Window::getRootFragment() {
    return nullptr;
}

void Glfw3Window::activateContext() {
    glfwMakeContextCurrent(window);
}

void Glfw3Window::setBufferSwapInterval(int interval) {
    glfwSwapInterval(interval);
}

void Glfw3Window::render() const {

}

void Glfw3Window::onWindowResize(int width, int height) {

}

void Glfw3Window::onFramebufferResize(int width, int height) {

}

void Glfw3Window::onWindowPosition(int x, int y) {

}

void Glfw3Window::onWindowIconify(bool iconified) {

}

void Glfw3Window::onWindowFocus(bool focused) {

}

void Glfw3Window::onWindowRefresh() {

}

Glfw3Window *Glfw3Window::findWindow(GLFWwindow *window) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = std::find_if(windows.begin(), windows.end(),
                           [&](const std::unique_ptr<Glfw3Window>& glfw3Window) {
       return glfw3Window.get()->getHandle() == window;
    });

    if(it == windows.end()) {
        return nullptr;
    } else {
        return it->get();
    }
}

bool Glfw3Window::shouldClose() const {
    return false;
}

void Glfw3Window::initialize(const WindowOptions &options) {
    glfwWindowHint(GLFW_RED_BITS, options.getRedBits());
    glfwWindowHint(GLFW_GREEN_BITS, options.getGreenBits());
    glfwWindowHint(GLFW_BLUE_BITS, options.getBlueBits());
    glfwWindowHint(GLFW_ALPHA_BITS, options.getAlphaBits());
    glfwWindowHint(GLFW_DEPTH_BITS, options.getDepthBits());
    glfwWindowHint(GLFW_STENCIL_BITS, options.getStencilBits());
    glfwWindowHint(GLFW_SAMPLES, options.getSamples());
    glfwWindowHint(GLFW_REFRESH_RATE, options.getRefreshRate());

    for(auto& p : clientApiPairs) {
        if(p.clientApi == options.getClientApi()) {
            glfwWindowHint(GLFW_CLIENT_API, p.glfwValue);
            break;
        }
    }

    for(auto& p : contextApiPairs) {
        if(p.contextApi == options.getContextApi()) {
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, p.glfwValue);
            break;
        }
    }

    for(auto& p : contextRobustnessPairs) {
        if(p.robustness == options.getContextRobustness()) {
            glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, p.glfwValue);
            break;
        }
    }

    for(auto& p : releaseBehaviorPairs) {
        if(p.releaseBehavior == options.getContextReleaseBehavior()) {
            glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, p.glfwValue);
            break;
        }
    }

    const uint16_t style = options.getStyle();
    for(auto &p : stylePairs) {
        if(style & p.style) {
            glfwWindowHint(p.glfwValue, true);
        }
    }

    int width, height;
    GLFWmonitor *monitor = nullptr;
    if(!options.isFullScreen()) {
        width = options.getWidth();
        height = options.getHeight();
    }
    else {
        int count;
        const int selectedMonitor = options.getMonitor();
        GLFWmonitor ** monitors = glfwGetMonitors(&count);
        if(!monitors || count == 0 || selectedMonitor >= count) {
            throw std::runtime_error("Unable to select monitor");
        }

        monitor = monitors[selectedMonitor];
        if(!monitor) {
            throw std::runtime_error("Unable to get primary monitor info");
        }

        const GLFWvidmode *currentMode = glfwGetVideoMode(monitor);
        if(!currentMode) {
            throw std::runtime_error("Unable to get primary monitor video mode");
        }

        width = currentMode->width;
        height = currentMode->height;
    }

    window = glfwCreateWindow(width, height, options.getTitle().c_str(), monitor, nullptr);

    glfwSetFramebufferSizeCallback(window, Glfw3Window::framebufferSizeCallback);
    glfwSetWindowIconifyCallback(window, Glfw3Window::windowIconifyCallback);
    glfwSetWindowFocusCallback(window, Glfw3Window::windowFocusCallback);
    glfwSetWindowPosCallback(window, Glfw3Window::windowPositionCallback);
    glfwSetWindowRefreshCallback(window, Glfw3Window::windowRefreshCallback);
    glfwSetWindowSizeCallback(window, Glfw3Window::windowSizeCallback);
}

void Glfw3Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    auto glfw3Window = findWindow(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onFramebufferResize(width, height);
}

void Glfw3Window::windowIconifyCallback(GLFWwindow *window, int iconified) {
    auto glfw3Window = findWindow(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowIconify(iconified);
}

void Glfw3Window::windowFocusCallback(GLFWwindow *window, int focused) {
    auto glfw3Window = findWindow(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowFocus(focused);
}

void Glfw3Window::windowPositionCallback(GLFWwindow *window, int x, int y) {
    auto glfw3Window = findWindow(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowPosition(x, y);
}

void Glfw3Window::windowRefreshCallback(GLFWwindow *window) {
    auto glfw3Window = findWindow(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowRefresh();
}

void Glfw3Window::windowSizeCallback(GLFWwindow *window, int width, int height) {
    auto glfw3Window = findWindow(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowResize(width, height);
}

}
}
}
