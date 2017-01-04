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

#include "Fragment.h"

#include <algorithm>

namespace ui {

namespace frags {

const std::vector<Fragment *> &Fragment::getChildren() const {
    return children;
}

Fragment *Fragment::getParent() {
    return parent;
}

void Fragment::addChild(Fragment *childFragment) {
    auto it = std::find(children.begin(), children.end(), childFragment);
    if(it == children.end()) {
        children.push_back(childFragment);
    }
}

Fragment *Fragment::removeChild(Fragment *childFragment) {
    auto it = std::remove(children.begin(), children.end(), childFragment);
    if(it == children.end()) {
        return nullptr;
    }

    children.erase(it, children.end());
    return *it;
}

void Fragment::draw() {

}

void Fragment::onKeyPressed(const events::KeyboardEvent &event) {

}

void Fragment::onKeyReleased(const events::KeyboardEvent &event) {

}

void Fragment::onKeyRepeat(const events::KeyboardEvent &event) {

}

void Fragment::onMouseMove(const events::MouseEvent &event) {

}

void Fragment::onMouseButtonPressed(const events::MouseButtonEvent &event) {

}

void Fragment::onMouseButtonReleased(const events::MouseButtonEvent &event) {

}

void Fragment::onMouseWheel(const events::MouseWheelEvent &event) {

}
}
}
