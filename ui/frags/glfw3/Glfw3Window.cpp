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

std::mutex Glfw3Window::mutex;
std::vector<std::unique_ptr<Glfw3Window>> Glfw3Window::windows;

Glfw3Window::Glfw3Window(const WindowOptions &options) {

}

Glfw3Window::~Glfw3Window() {

}

Fragment *Glfw3Window::getRootFragment() {
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

    auto it = std::find_if(windows.begin(), windows.end(), [&](const std::unique_ptr<Glfw3Window>& glfw3Window) {
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
