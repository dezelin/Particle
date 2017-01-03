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

#include "Glfw3Monitor.h"
#include "Glfw3VideoMode.h"

namespace ui {

namespace display {

Glfw3Monitor::Glfw3Monitor(GLFWmonitor *_monitor, unsigned _id)
    : id(_id), monitor(_monitor) {
}

unsigned Glfw3Monitor::getId() const {
    return id;
}

std::unique_ptr<const VideoMode> Glfw3Monitor::getCurrentVideoMode() const {
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    if(!mode) {
        return nullptr;
    }

    return std::make_unique<const Glfw3VideoMode>(mode);
}

int Glfw3Monitor::getVideoModesCount() const {
    int modesCount;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &modesCount);
    if(!modes) {
        return 0;
    }

    return modesCount;
}

std::unique_ptr<const VideoMode> Glfw3Monitor::getVideoMode(unsigned index) {
    int modesCount;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &modesCount);
    if(!modes) {
        return nullptr;
    }

    if(modesCount == 0 || index >= modesCount) {
        return nullptr;
    }

    return std::make_unique<const Glfw3VideoMode>(modes + index);
}

const GLFWmonitor *Glfw3Monitor::getPtr() const {
    return monitor;
}

}
}
