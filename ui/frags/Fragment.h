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

#ifndef PARTICLE_FRAG_H
#define PARTICLE_FRAG_H

#include "Component.h"
#include "Drawable.h"
#include "KeyboardInputHandler.h"
#include "MouseInputHandler.h"

#include <vector>

namespace ui {

namespace frags {

class Fragment
        : public Component<Fragment>,
          public Drawable,
          public KeyboardInputHandler,
          public MouseInputHandler {
public:
    const std::vector<Fragment *> &getChildren() const override;

    Fragment *getParent() override;

    void addChild(Fragment *childFragment) override;

    Fragment *removeChild(Fragment *childFragment) override;

    void draw() override;

    void onKeyPressed(const events::KeyboardEvent &event) override;

    void onKeyReleased(const events::KeyboardEvent &event) override;

    void onKeyRepeat(const events::KeyboardEvent &event) override;

    void onMouseMove(const events::MouseEvent &event) override;

    void onMouseButtonPressed(const events::MouseButtonEvent &event) override;

    void onMouseButtonReleased(const events::MouseButtonEvent &event) override;

    void onMouseWheel(const events::MouseWheelEvent &event) override;
};

}
}

#endif //PARTICLE_FRAG_H
