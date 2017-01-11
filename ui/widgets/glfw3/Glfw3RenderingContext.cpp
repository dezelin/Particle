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

#include "Glfw3RenderingContext.h"

namespace ui {

namespace widgets {

namespace glfw3 {

Glfw3RenderingContext::Glfw3RenderingContext(ContextHandle contextHandle,
                                             const OverlayRenderingOptions &options)
        : window(reinterpret_cast<GLFWwindow *>(contextHandle)),
          swapInterval(options.getSwapInterval()) {

}

OverlayRenderingContext::ContextHandle Glfw3RenderingContext::getHandle() {
    return reinterpret_cast<OverlayRenderingContext::ContextHandle>(window);
}

void Glfw3RenderingContext::makeCurrent() {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(swapInterval);
}

void Glfw3RenderingContext::resizeViewPort(int width, int height) {
    glViewport(0, 0, width, height);

    projection.setOrthoProjection(0.0f, width, 0.0f, height, -1.0f, 1.0f);

    viewPort.setWidth(width);
    viewPort.setHeight(height);
}

void Glfw3RenderingContext::swapBuffers() {
    glfwSwapBuffers(window);
}

const Rectangle &Glfw3RenderingContext::getViewPort() const {
    return viewPort;
}

OverlayProjection &Glfw3RenderingContext::getProjection() {
    return projection;
}

const OverlayProjection &Glfw3RenderingContext::getProjection() const {
    return projection;
}

}
}
}
