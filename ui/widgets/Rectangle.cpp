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

#include <glm/common.hpp>
#include "Rectangle.h"

namespace ui {

namespace widgets {

Rectangle::Rectangle() : Rectangle(0, 0, 0, 0) {

}

Rectangle::Rectangle(float _left, float _bottom, float _right, float _top)
        : left(_left, _bottom), right(_right, _top) {

}

Rectangle::Rectangle(const Point &_left, const Point &_right)
        : left(_left), right(_right) {

}

bool Rectangle::operator==(const Rectangle &other) const {
    return left == other.left && right == other.right;
}

bool Rectangle::operator!=(const Rectangle &other) const {
    return left != other.left || right != other.right;
}

float Rectangle::getLeft() const {
    return left.getX();
}

void Rectangle::setLeft(float _left) {
    left.setX(_left);
}

float Rectangle::getRight() const {
    return right.getX();
}

void Rectangle::setRight(float _right) {
    right.setX(_right);
}

float Rectangle::getTop() const {
    return right.getY();
}

void Rectangle::setTop(float top) {
    right.setY(top);
}

float Rectangle::getBottom() const {
    return left.getY();
}

void Rectangle::setBottom(float bottom) {
    left.setY(bottom);
}

float Rectangle::getWidth() const {
    return right.getX() - left.getX();
}

void Rectangle::setWidth(float width) {
    right.setX(left.getX() + width);
}

float Rectangle::getHeight() const {
    return right.getY() - left.getY();
}

void Rectangle::setHeight(float height) {
    right.setY(left.getY() + height);
}

bool Rectangle::isEmpty() const {
    return getWidth() <= 0 || getHeight() <= 0;
}

bool Rectangle::isInside(Point point) const {
    const float x = point.getX();
    const float y = point.getY();
    return left.getX() <= x && right.getX() >= x && left.getY() <= y &&
           right.getY() >= y;
}

}
}
