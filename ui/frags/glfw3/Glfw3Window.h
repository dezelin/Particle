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

#ifndef PARTICLE_GLFW3WINDOW_H
#define PARTICLE_GLFW3WINDOW_H

#include "frags/Window.h"

#include <GLFW/glfw3.h>
#include <mutex>

namespace ui {

namespace frags {

namespace glfw3 {

class Glfw3Window : public Window {
public:
    Glfw3Window(const WindowOptions& options);

    virtual ~Glfw3Window();

    Fragment *getRootFragment() override;

    bool shouldClose() const override;

    void activateContext() override;

    void setBufferSwapInterval(int interval) override;

    void render() const override;

    void onWindowResize(int width, int height) override;

    void onFramebufferResize(int width, int height) override;

    void onWindowPosition(int x, int y) override;

    void onWindowIconify(bool iconified) override;

    void onWindowFocus(bool focused) override;

    void onWindowRefresh() override;

private:

    GLFWwindow* getHandle() { return window; }

    static std::mutex mutex;
    static std::vector<std::unique_ptr<Glfw3Window>> windows;

    static Glfw3Window* findWindow(GLFWwindow *window);
    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
    static void windowIconifyCallback(GLFWwindow *window, int iconified);
    static void windowFocusCallback(GLFWwindow *window, int focused);
    static void windowPositionCallback(GLFWwindow *window, int x, int y);
    static void windowRefreshCallback(GLFWwindow *window);
    static void windowSizeCallback(GLFWwindow *window, int width, int height);

private:
    GLFWwindow *window;
};

}
}
}

#endif //PARTICLE_GLFW3WINDOW_H
