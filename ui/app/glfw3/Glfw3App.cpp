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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Glfw3App.h"

#include "widgets/glfw3/Glfw3Window.h"

#include <thread>

namespace ui {

namespace app {

namespace glfw3 {

using namespace ui::widgets;
using namespace ui::widgets::glfw3;

Glfw3App::Glfw3App(const AppOptions &options) {
    if(!glfwInit()) {
        throw std::runtime_error("Failed to compile GLFW");
    }

    auto mainWindow = Window::create(options.getMainWindowOptions());
    if(!mainWindow) {
        throw std::runtime_error("Failed to create main window");
    }

    // Initialize GLAD extension loader
    int gladOk = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!gladOk) {
        throw std::runtime_error("Failed to compile OpenGL context");
    }

    setMainWindow(std::move(mainWindow));
}

Glfw3App::~Glfw3App() {
    glfwTerminate();
}

int Glfw3App::run() {
    Window *mainWindow = getMainWindow();
    if (!mainWindow) {
        return 1;
    }

    while(!mainWindow->shouldClose()) {
        mainWindow->render();
        glfwPollEvents();
    }

    return 0;
}

}
}

}
