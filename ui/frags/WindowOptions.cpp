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

#include "WindowOptions.h"

#include <GLFW/glfw3.h>

namespace ui {

namespace frags {

const uint8_t kDefaultColorBits = 8;
const uint8_t kDefaultStencilBits = 8;
const uint8_t kDefaultDepthBits = 24;
const uint8_t kDefaultSamplesNum = 0;
const uint8_t kDefaultRefreshRate = -1;

const uint16_t kDefaultStyle =
        WindowOptions::WINDOWSTYLE_RESIZABLE
        | WindowOptions::WINDOWSTYLE_VISIBLE
        | WindowOptions::WINDOWSTYLE_DECORATED
        | WindowOptions::WINDOWSTYLE_FOCUSED
        | WindowOptions::WINDOWSTYLE_AUTO_ICONIFY
        | WindowOptions::WINDOWSTYLE_DOUBLE_BUFFER;

WindowOptions::WindowOptions(int _width, int _height, const std::string& _title)
        : title(_title)
        , width(_width)
        , height(_height)
        , redBits(kDefaultColorBits)
        , greenBits(kDefaultColorBits)
        , blueBits(kDefaultColorBits)
        , alphaBits(kDefaultColorBits)
        , depthBits(kDefaultDepthBits)
        , stencilBits(kDefaultStencilBits)
        , samples(kDefaultSamplesNum)
        , refreshRate(kDefaultRefreshRate)
        , clientApi(ClientApi::OpenGL)
        , contextApi(ContextApi::Native)
        , contextApiVersion(ContextApiVersion::Latest)
        , contextRobustness(ContextRobustness::No)
        , contextReleaseBehavior(ContextReleaseBehavior::Any)
        , profile(OpenGLProfile::Any)
        , style(kDefaultStyle)
{
    initialize();
}

const std::string &WindowOptions::getTitle() const {
    return title;
}

void WindowOptions::setTitle(const std::string &_title) {
    title = _title;
}

int WindowOptions::getWidth() const {
    return width;
}

void WindowOptions::setWidth(int _width) {
    width = _width;
}

int WindowOptions::getHeight() const {
    return height;
}

void WindowOptions::setHeight(int _height) {
    height = _height;
}

uint8_t WindowOptions::getRedBits() const {
    return redBits;
}

void WindowOptions::setRedBits(uint8_t _redBits) {
    redBits = _redBits;
}

uint8_t WindowOptions::getGreenBits() const {
    return greenBits;
}

void WindowOptions::setGreenBits(uint8_t _greenBits) {
    greenBits = _greenBits;
}

uint8_t WindowOptions::getBlueBits() const {
    return blueBits;
}

void WindowOptions::setBlueBits(uint8_t _blueBits) {
    blueBits = _blueBits;
}

uint8_t WindowOptions::getDepthBits() const {
    return depthBits;
}

void WindowOptions::setDepthBits(uint8_t _depthBits) {
    depthBits = _depthBits;
}

uint8_t WindowOptions::getAlphaBits() const {
    return alphaBits;
}

void WindowOptions::setAlphaBits(uint8_t _alphaBits) {
    alphaBits = _alphaBits;
}

uint8_t WindowOptions::getStencilBits() const {
    return stencilBits;
}

void WindowOptions::setStencilBits(uint8_t _stencilBits) {
    stencilBits = _stencilBits;
}

uint8_t WindowOptions::getSamples() const {
    return samples;
}

void WindowOptions::setSamples(uint8_t _samples) {
    samples = _samples;
}

uint8_t WindowOptions::getRefreshRate() const {
    return refreshRate;
}

void WindowOptions::setRefreshRate(uint8_t _refreshRate) {
    refreshRate = _refreshRate;
}

WindowOptions::ClientApi WindowOptions::getClientApi() const {
    return clientApi;
}

void WindowOptions::setClientApi(WindowOptions::ClientApi _clientApi) {
    clientApi = _clientApi;
}

WindowOptions::ContextApi WindowOptions::getContextApi() const {
    return contextApi;
}

void WindowOptions::setContextApi(WindowOptions::ContextApi _contextApi) {
    contextApi = _contextApi;
}

WindowOptions::ContextApiVersion WindowOptions::getContextApiVersion() const {
    return contextApiVersion;
}

void WindowOptions::setContextApiVersion(WindowOptions::ContextApiVersion _contextApiVersion) {
    contextApiVersion = _contextApiVersion;
}

WindowOptions::ContextRobustness WindowOptions::getContextRobustness() const {
    return contextRobustness;
}

void WindowOptions::setContextRobustness(WindowOptions::ContextRobustness _contextRobustness) {
    contextRobustness = _contextRobustness;
}

WindowOptions::ContextReleaseBehavior WindowOptions::getContextReleaseBehavior() const {
    return contextReleaseBehavior;
}

void WindowOptions::setContextReleaseBehavior(WindowOptions::ContextReleaseBehavior _contextReleaseBehavior) {
    contextReleaseBehavior = _contextReleaseBehavior;
}

WindowOptions::OpenGLProfile WindowOptions::getProfile() const {
    return profile;
}

void WindowOptions::setProfile(WindowOptions::OpenGLProfile _profile) {
    profile = _profile;
}

void WindowOptions::initialize() {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    if(!monitor) {
        return;
    }

    const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);
    if(!vidmode) {
        return;
    }

    redBits = vidmode->redBits;
    greenBits = vidmode->greenBits;
    blueBits = vidmode->blueBits;
    refreshRate = vidmode->refreshRate;
}

}
}