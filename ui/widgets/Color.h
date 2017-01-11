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

#ifndef PARTICLE_COLOR_H
#define PARTICLE_COLOR_H

namespace ui {

namespace widgets {

class Color {
public:

    using Rgb = unsigned int;

    enum {
        Black = 0xff000000,
        White = 0xffffffff,
        Red = 0xffff0000,
        Green = 0xff00ff00,
        Blue = 0xff0000ff
    };

    Color() : Color(Color::White) {

    }

    explicit Color(Rgb rgb)
            : Color(Color::fromRgba(rgb)) {

    }

    explicit Color(unsigned char r, unsigned char g, unsigned char b,
                   unsigned char a)
            : red(r), green(g), blue(b), alpha(a) {

    }

    explicit Color(unsigned char r, unsigned char g, unsigned char b)
            : Color(r, g, b, 255) {

    }

    Color(const Color &color)
            : red(color.red), green(color.green), blue(color.blue),
              alpha(color.alpha) {
    }

    unsigned char getRed() const { return red; };

    float getRedF() const { return (float) red / 255; }

    void setRed(unsigned char r) { red = r; }

    unsigned char getGreen() const { return green; }

    float getGreenF() const { return (float) green / 255; }

    void setGreen(unsigned char g) { green = g; }

    unsigned char getBlue() const { return blue; };

    float getBlueF() const { return (float) blue / 255; }

    void setBlue(unsigned char b) { blue = b; }

    unsigned char getAlpha() const { return alpha; }

    float getAlphaF() const { return (float) alpha / 255; }

    void setAlpha(unsigned char a) { alpha = a; }

    static Color fromRgba(Rgb rgb);

    static Rgb toRgba(const Color &color);

private:

    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};



}
}

#endif //PARTICLE_COLOR_H
