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

#include "Widget.h"

#include <iostream>

namespace ui {

namespace widgets {

Widget::Widget()
        : parent(nullptr), zOrder(0), canHoldFocus(false) {

}

const std::vector<std::unique_ptr<Widget>> &Widget::getChildren() const {
    return children;
}

Widget *Widget::getParent() {
    return parent;
}

void Widget::setParent(Widget *parent) {
    parent = parent;
}

void Widget::addChild(Widget *childWidget) {
    auto it = std::find_if(children.begin(), children.end(),
                           [&](const std::unique_ptr<Widget> &widget) {
                               return widget.get() == childWidget;
                           });

    if (it == children.end()) {
        childWidget->setParent(this);
        children.push_back(std::unique_ptr<Widget>(childWidget));
    }
}

Widget *Widget::removeChild(Widget *childWidget) {
    auto it = std::remove_if(children.begin(), children.end(),
                             [&](const std::unique_ptr<Widget> &widget) {
                                 return widget.get() == childWidget;
                             });

    if (it == children.end()) {
        return nullptr;
    }

    children.erase(it, children.end());
    return it->get();
}

void Widget::render(const OverlayRenderingContext &context) {
}

float Widget::getLeft() const {
    return rect.getLeft();
}

float Widget::getRight() const {
    return rect.getRight();
}

float Widget::getTop() const {
    return rect.getTop();
}

float Widget::getBottom() const {
    return rect.getBottom();
}

float Widget::getWidth() const {
    return rect.getWidth();
}

float Widget::getHeight() const {
    return rect.getHeight();
}

int Widget::getZOrder() const {
    return zOrder;
}

void Widget::setZOrder(int _zOrder) {
    zOrder = _zOrder;
}

const Rectangle &Widget::getRect() const {
    return rect;
}

void Widget::setRect(const Rectangle &_rect) {
    rect = _rect;
}

void Widget::resize(float width, float height) {
    rect.setWidth(width);
    rect.setHeight(height);
}

void Widget::resize(float left, float top, float right, float bottom) {
    rect.setLeft(left);
    rect.setTop(top);
    rect.setRight(right);
    rect.setBottom(bottom);
}

bool Widget::getCanHoldFocus() const {
    if (canHoldFocus) {
        return true;
    }

    for (const auto &child : children) {
        if (child->getCanHoldFocus()) {
            return true;
        }
    }

    return false;
}

void Widget::setCanHoldFocus(bool focusable) {
    canHoldFocus = focusable;
}

bool Widget::hasFocus() const {
    for (const auto &child : children) {
        if (child->hasFocus()) {
            return true;
        }
    }

    return false;
}

void Widget::onFocus(bool focused) {
}

void Widget::onCharInput(events::CodePoint codePoint,
                         events::KeyModifiers modifiers) {
    for (auto &child : children) {
        if (child->getCanHoldFocus() && child->hasFocus()) {
            child->onCharInput(codePoint, modifiers);
        }
    }
}

void Widget::onKeyPressed(events::Key key, events::ScanCode scanCode,
                          events::KeyModifiers modifiers) {
    for (auto &child : children) {
        if (child->getCanHoldFocus() && child->hasFocus()) {
            child->onKeyPressed(key, scanCode, modifiers);
        }
    }
}

void Widget::onKeyReleased(events::Key key, events::ScanCode scanCode,
                           events::KeyModifiers modifiers) {
    for (auto &child : children) {
        if (child->getCanHoldFocus() && child->hasFocus()) {
            child->onKeyReleased(key, scanCode, modifiers);
        }
    }
}

void Widget::onKeyRepeat(events::Key key, events::ScanCode scanCode,
                         events::KeyModifiers modifiers) {
    for (auto &child : children) {
        if (child->getCanHoldFocus() && child->hasFocus()) {
            child->onKeyRepeat(key, scanCode, modifiers);
        }
    }
}

bool Widget::onMouseMove(float xPos, float yPos) {
    return false;
}

bool Widget::onMouseButtonPressed(events::MouseButton button,
                                  events::KeyModifiers modifiers) {
    return false;
}

bool Widget::onMouseButtonReleased(events::MouseButton button,
                                   events::KeyModifiers modifiers) {
    return false;
}

bool Widget::onMouseWheel(float xOffset, float yOffset) {
    return false;
}

}
}
