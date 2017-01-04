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

#ifndef PARTICLE_WINDOWOPTIONS_H
#define PARTICLE_WINDOWOPTIONS_H

#include <cstdint>
#include <string>

namespace ui {

namespace frags {

struct WindowOptions {

    enum class ClientApi : uint8_t {
        NoApi,
        OpenGL,
        OpenGLES,
    };

    enum class ContextApi : uint8_t {
        Native,
        EGL
    };

    enum class ContextApiVersion : uint8_t {
        Latest
    };

    enum class ContextRobustness : uint8_t {
        No,
        NoResetNotification,
        LoseContextOnReset
    };

    enum class ContextReleaseBehavior : uint8_t {
        None,
        Any,
        Flush
    };

    enum OpenGLProfile : uint8_t {
        Any,
        Compat,
        Core
    };

    enum WindowStyles {
        WINDOWSTYLE_FOCUSED = 1 << 0,
        WINDOWSTYLE_ICONIFIED = 1 << 1,
        WINDOWSTYLE_RESIZABLE = 1 << 2,
        WINDOWSTYLE_VISIBLE = 1 << 3,
        WINDOWSTYLE_DECORATED = 1 << 4,
        WINDOWSTYLE_AUTO_ICONIFY = 1 << 5,
        WINDOWSTYLE_FLOATING = 1 << 6,
        WINDOWSTYLE_MAXIMIZED = 1 << 7,
        WINDOWSTYLE_STEREO = 1 << 8,
        WINDOWSTYLE_SRGB_CAPABLE = 1 << 9,
        WINDOWSTYLE_DOUBLE_BUFFER = 1 << 10,
        WINDOWSTYLE_FORWARD_COMPAT = 1 << 11,
        WINDOWSTYLE_DEBUG_CONTEXT = 1 << 12,
        WINDOWSTYLE_FULL_SCREEN = 1 << 13
    };

    WindowOptions();

    WindowOptions(const std::string& title);

    WindowOptions(int width, int height, const std::string& title);

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    bool isFullScreen() const;

    void setFullScreen(bool fullScreen);

    uint8_t getRedBits() const;

    void setRedBits(uint8_t redBits);

    uint8_t getGreenBits() const;

    void setGreenBits(uint8_t greenBits);

    uint8_t getBlueBits() const;

    void setBlueBits(uint8_t blueBits);

    uint8_t getDepthBits() const;

    void setDepthBits(uint8_t depthBits);

    uint8_t getAlphaBits() const;

    void setAlphaBits(uint8_t alphaBits);

    uint8_t getStencilBits() const;

    void setStencilBits(uint8_t stencilBits);

    uint8_t getSamples() const;

    void setSamples(uint8_t samples);

    uint8_t getRefreshRate() const;

    void setRefreshRate(uint8_t refreshRate);

    ClientApi getClientApi() const;

    void setClientApi(ClientApi clientApi);

    ContextApi getContextApi() const;

    void setContextApi(ContextApi contextApi);

    ContextApiVersion getContextApiVersion() const;

    void setContextApiVersion(ContextApiVersion contextApiVersion);

    ContextRobustness getContextRobustness() const;

    void setContextRobustness(ContextRobustness contextRobustness);

    ContextReleaseBehavior getContextReleaseBehavior() const;

    void setContextReleaseBehavior(ContextReleaseBehavior contextReleaseBehavior);

    OpenGLProfile getProfile() const;

    void setProfile(OpenGLProfile profile);

private:
    std::string title;
    int width;
    int height;
    bool fullScreen;

    uint8_t redBits;
    uint8_t greenBits;
    uint8_t blueBits;
    uint8_t depthBits;
    uint8_t alphaBits;
    uint8_t stencilBits;
    uint8_t samples;
    uint8_t refreshRate;

    ClientApi clientApi;
    ContextApi contextApi;
    ContextApiVersion contextApiVersion;
    ContextRobustness contextRobustness;
    ContextReleaseBehavior contextReleaseBehavior;
    OpenGLProfile profile;

    uint16_t style;
};

}
}

#endif //PARTICLE_WINDOWOPTIONS_H
