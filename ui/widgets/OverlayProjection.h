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

#ifndef PARTICLE_OVERLAYPERSPECTIVE_H
#define PARTICLE_OVERLAYPERSPECTIVE_H

#include <glm/glm.hpp>
#include "Rectangle.h"

namespace ui {

namespace widgets {


class OverlayProjection {
public:

    OverlayProjection();

    const glm::mat4 &getModel() const;

    void setModel(const glm::mat4 &model);

    const glm::mat4 &getView() const;

    void setView(const glm::mat4 &view);

    const glm::mat4 &getProjection() const;

    void setOrthoProjection(float left, float right, float bottom,
                            float top, float zNear, float zFar);

    void
    cameraLookAt(const glm::vec3 &eye, const glm::vec3 &center,
                 const glm::vec3 &up);

    const Rectangle &getViewPort() const;

private:
    Rectangle rect;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

}
}

#endif //PARTICLE_OVERLAY_H
