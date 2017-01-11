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

#include "ButtonImpl.h"

#include <iostream>

namespace ui {

namespace widgets {

namespace impl {

enum class ShaderInputs : GLuint {
    Position = 0,
    MVP,
    Color
};

const std::string ButtonImpl::vertexShaderSrc =
        "#version 450\n"
                "layout(location = 0) in vec2 position;"
                "layout(location = 1) uniform mat4 mvp;"
                "void main() {"
                "   gl_Position = mvp * vec4(position, 1.0, 1.0);"
                "}";

const std::string ButtonImpl::fragmentShaderSrc =
        "#version 450\n"
                "layout(location = 2) uniform vec4 color;"
                "out vec4 outColor;"
                "void main() {"
                "outColor = color;"
                "}";

GLuint ButtonImpl::shaderProgram = (GLuint) -1;

ButtonImpl::ButtonImpl(const ButtonOptions &options)
        : bgColor(options.getBgColor()) {
    if (!compile()) {
        throw std::runtime_error("Failed to compile shaders.");
    };

    setRect(options.getRect());
}

void ButtonImpl::render(const OverlayRenderingContext &context) {
    const float left = getLeft();
    const float right = getRight();
    const float top = getTop();
    const float bottom = getBottom();

    const OverlayProjection &perspective = context.getProjection();
    const glm::mat4 &model = perspective.getModel();
    const glm::mat4 &view = perspective.getView();
    const glm::mat4 &projection = perspective.getProjection();

    const glm::mat4 mvp = projection * view * model;

    const glm::vec2 vertices[]{
            {left,  top},
            {left,  bottom},
            {right, top},
            {right, bottom}
    };

    glUseProgram(shaderProgram);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray((GLuint) ShaderInputs::Position);
    glVertexAttribPointer((GLuint) ShaderInputs::Position, 2, GL_FLOAT,
                          GL_FALSE, 0, 0);

    glUniformMatrix4fv((GLuint) ShaderInputs::MVP, 1, GL_FALSE, &mvp[0][0]);

    const glm::vec4 color{
            bgColor.getRedF(),
            bgColor.getGreenF(),
            bgColor.getBlueF(),
            bgColor.getAlphaF()
    };

    glUniform4fv((GLuint) ShaderInputs::Color, 1, &color[0]);

    glEnable(GL_CULL_FACE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisable(GL_CULL_FACE);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray((GLuint) ShaderInputs::Position);
    glUseProgram(0);
}

bool ButtonImpl::compile() {
    if (shaderProgram != -1) {
        return true;
    }

    shaderProgram = compileShaders(vertexShaderSrc, fragmentShaderSrc);
    if (shaderProgram == (GLuint) -1) {
        return false;
    } else {
        return true;
    }
}

}
}
}
