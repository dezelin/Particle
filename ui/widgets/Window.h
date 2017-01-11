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

#ifndef PARTICLE_WINDOW_H
#define PARTICLE_WINDOW_H

#include "Overlay.h"
#include "Rectangle.h"
#include "WindowOptions.h"

#include "events/MouseListener.h"
#include "events/KeyboardListener.h"

#include <memory>

namespace ui {

namespace widgets {

class Window : public events::KeyboardListener,
               public events::MouseListener {
public:
    static std::unique_ptr<Window> create(const WindowOptions& options);

    virtual ~Window() { }

    virtual void render() = 0;

    virtual float getLeft() const = 0;

    virtual float getRight() const = 0;

    virtual float getTop() const = 0;

    virtual float getBottom() const = 0;

    float getWidth() const { return getRight() - getLeft(); }

    float getHeight() const { return getTop() - getBottom(); };

    virtual Widget *getOverlay() const = 0;

    virtual void setOverlay(std::unique_ptr<Widget> overlay) = 0;

    virtual bool shouldClose() const = 0;

    virtual void onWindowResize(int width, int height) = 0;

    virtual void onFramebufferResize(int width, int height) = 0;

    virtual void onWindowPosition(int x, int y) = 0;

    virtual void onWindowIconify(bool iconified) = 0;

    virtual void onWindowFocus(bool focused) = 0;

    virtual void onWindowRefresh() = 0;
};

}
}

#endif //PARTICLE_WINDOW_H