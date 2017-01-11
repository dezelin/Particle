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

#include "widgets/OverlayProjection.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ui {

namespace widgets {


OverlayProjection::OverlayProjection() {

}

const glm::mat4 &OverlayProjection::getModel() const {
    return model;
}

void OverlayProjection::setModel(const glm::mat4 &_model) {
    model = _model;
}

const glm::mat4 &OverlayProjection::getView() const {
    return view;
}

void OverlayProjection::setView(const glm::mat4 &_view) {
    view = _view;
}

const glm::mat4 &OverlayProjection::getProjection() const {
    return projection;
}

void
OverlayProjection::setOrthoProjection(float left, float right, float bottom,
                                      float top, float zNear, float zFar) {
    rect.setLeft(left);
    rect.setRight(right);
    rect.setTop(top);
    rect.setBottom(bottom);

    projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void
OverlayProjection::cameraLookAt(const glm::vec3 &eye, const glm::vec3 &center,
                                const glm::vec3 &up) {
    view = glm::lookAt(eye, center, up);
}

const Rectangle &OverlayProjection::getViewPort() const {
    return rect;
}

}
}
