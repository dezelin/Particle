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
#include "WidgetRenderer.h"
#include "FocusHolder.h"
#include "Rectangle.h"

#include "events/KeyboardListener.h"
#include "events/MouseListener.h"

#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

namespace ui {

namespace widgets {

class Widget :
        public FocusHolder,
        public WidgetRenderer,
        public events::KeyboardListener,
        public events::MouseListener {

public:

    Widget();
    virtual ~Widget() { }

    const std::vector<std::unique_ptr<Widget>> &getChildren() const;

    Widget *getParent();

    void setParent(Widget *parent);

    void addChild(Widget *childWidget);

    template<typename T>
    void addChild(std::unique_ptr<T> &&childWidget);

    Widget *removeChild(Widget *childWidget);

    float getLeft() const;

    float getRight() const;

    float getTop() const;

    float getBottom() const;

    float getWidth() const;

    float getHeight() const;

    int getZOrder() const;

    void setZOrder(int zOrder);

    const Rectangle &getRect() const;

    void setRect(const Rectangle &rect);

    void resize(float width, float height);

    void resize(float left, float top, float right, float bottom);

    bool getCanHoldFocus() const;

    void setCanHoldFocus(bool focusable);

    bool hasFocus() const override;

    void onFocus(bool focused) override;

    void render(const OverlayRenderingContext &context) override;

    void onCharInput(events::CodePoint codePoint,
                     events::KeyModifiers modifiers) override;

    void onKeyPressed(events::Key key, events::ScanCode scancode,
                      events::KeyModifiers modifiers) override;

    void onKeyReleased(events::Key key, events::ScanCode scancode,
                       events::KeyModifiers modifiers) override;

    void onKeyRepeat(events::Key key, events::ScanCode scancode,
                     events::KeyModifiers modifiers) override;

    bool onMouseMove(float xPos, float yPos) override;

    bool onMouseButtonPressed(events::MouseButton button,
                              events::KeyModifiers modifiers) override;

    bool onMouseButtonReleased(events::MouseButton button,
                               events::KeyModifiers modifiers) override;

    bool onMouseWheel(float xOffset, float yOffset) override;

private:
    Widget *parent;
    std::vector<std::unique_ptr<Widget>> children;

    int zOrder;
    Rectangle rect;
    bool canHoldFocus;
};

template<typename T>
void Widget::addChild(std::unique_ptr<T> &&childWidget) {
    auto it = std::find_if(children.begin(), children.end(),
                           [&](const std::unique_ptr<Widget> &widget) {
                               return childWidget.get() == widget.get();
                           });

    if (it == children.end()) {
        childWidget->setParent(this);
        children.push_back(std::unique_ptr<Widget>(childWidget.release()));
    }
}

}
}

#endif //PARTICLE_FRAG_H
