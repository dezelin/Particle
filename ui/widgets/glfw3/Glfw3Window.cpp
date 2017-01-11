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

#include "Glfw3Window.h"

#include "events/glfw3/Glfw3EventTranslator.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ui {

namespace widgets {

namespace glfw3 {

using namespace events::glfw3;

struct ClientApiPair {
    WindowOptions::ClientApi clientApi;
    int glfwValue;
};

struct ContextApiPair {
    WindowOptions::ContextApi contextApi;
    int glfwValue;
};

struct ContextRobustnessPair {
    WindowOptions::ContextRobustness robustness;
    int glfwValue;
};

struct ContextReleaseBehaviorPair {
    WindowOptions::ContextReleaseBehavior releaseBehavior;
    int glfwValue;
};

struct StylePair {
    int style;
    int glfwValue;
};

struct ClientApiPair clientApiPairs[] = {
        { WindowOptions::ClientApi::NoApi, GLFW_NO_API },
        { WindowOptions::ClientApi::OpenGLES, GLFW_OPENGL_ES_API },
        { WindowOptions::ClientApi::OpenGL, GLFW_OPENGL_API }
};

struct ContextApiPair contextApiPairs[] = {
        { WindowOptions::ContextApi::EGL, GLFW_EGL_CONTEXT_API },
        { WindowOptions::ContextApi::Native, GLFW_NATIVE_CONTEXT_API }
};

struct ContextRobustnessPair contextRobustnessPairs[] = {
        { WindowOptions::ContextRobustness::LoseContextOnReset, GLFW_LOSE_CONTEXT_ON_RESET },
        { WindowOptions::ContextRobustness::No, GLFW_NO_ROBUSTNESS },
        { WindowOptions::ContextRobustness::NoResetNotification, GLFW_NO_RESET_NOTIFICATION }
};

struct ContextReleaseBehaviorPair releaseBehaviorPairs[] = {
        { WindowOptions::ContextReleaseBehavior::Any, GLFW_ANY_RELEASE_BEHAVIOR },
        { WindowOptions::ContextReleaseBehavior::Flush, GLFW_RELEASE_BEHAVIOR_FLUSH },
        { WindowOptions::ContextReleaseBehavior::None, GLFW_RELEASE_BEHAVIOR_NONE }
};

struct StylePair stylePairs[] = {
        { WindowOptions::WINDOWSTYLE_FOCUSED, GLFW_FOCUSED },
        { WindowOptions::WINDOWSTYLE_ICONIFIED, GLFW_ICONIFIED },
        { WindowOptions::WINDOWSTYLE_RESIZABLE, GLFW_RESIZABLE },
        { WindowOptions::WINDOWSTYLE_VISIBLE, GLFW_VISIBLE },
        { WindowOptions::WINDOWSTYLE_DECORATED, GLFW_DECORATED },
        { WindowOptions::WINDOWSTYLE_AUTO_ICONIFY, GLFW_AUTO_ICONIFY },
        { WindowOptions::WINDOWSTYLE_FLOATING, GLFW_FLOATING },
        { WindowOptions::WINDOWSTYLE_MAXIMIZED, GLFW_MAXIMIZED },
        { WindowOptions::WINDOWSTYLE_STEREO, GLFW_STEREO },
        { WindowOptions::WINDOWSTYLE_SRGB_CAPABLE, GLFW_SRGB_CAPABLE },
        { WindowOptions::WINDOWSTYLE_DOUBLE_BUFFER, GLFW_DOUBLEBUFFER },
        { WindowOptions::WINDOWSTYLE_FORWARD_COMPAT, GLFW_OPENGL_FORWARD_COMPAT },
        { WindowOptions::WINDOWSTYLE_DEBUG_CONTEXT, GLFW_OPENGL_DEBUG_CONTEXT }
};

std::mutex Glfw3Window::mutex;
std::vector<Glfw3Window *> Glfw3Window::windows;

template<typename T, typename Fun>
void preOrderTraverse(const std::unique_ptr<T> &widget, Fun fn) {
    fn(widget);
    for (auto &child : widget->getChildren()) {
        preOrderTraverse(child, fn);
    }
}

Glfw3Window::Glfw3Window(const WindowOptions &options) {
    if (!createWindow(options)) {
        throw std::runtime_error("Failed to create window");
    }

    if (!initializeCallbacks()) {
        destroy();
        throw std::runtime_error("Failed to setup callbacks");
    }

    if (!initializeRenderingContext(options.getOverlayOptions())) {
        destroy();
        throw std::runtime_error("Failed to create rendering context");
    }
}

Glfw3Window::~Glfw3Window() {
    destroy();
}

void Glfw3Window::render() {
    renderingContext->makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (overlay) {
        std::vector<Widget *> zOrderSorted;

        preOrderTraverse(overlay, [&](const std::unique_ptr<Widget> &widget) {
            zOrderSorted.push_back(widget.get());
        });

        std::stable_sort(zOrderSorted.begin(), zOrderSorted.end(),
                         [](const Widget *l, const Widget *r) {
                             return l->getZOrder() < r->getZOrder();
                         });

        for (auto child : zOrderSorted) {
            child->render(*renderingContext);
        }
    }

    renderingContext->swapBuffers();
}

float Glfw3Window::getLeft() const {
    int x;
    glfwGetWindowPos(window, &x, nullptr);
    return x;
}

float Glfw3Window::getRight() const {
    int width;
    glfwGetWindowSize(window, &width, nullptr);
    return getLeft() + width;
}

float Glfw3Window::getTop() const {
    int height;
    glfwGetWindowSize(window, nullptr, &height);
    return getBottom() + height;
}

float Glfw3Window::getBottom() const {
    int y;
    glfwGetWindowPos(window, nullptr, &y);
    return y;
}

Widget *Glfw3Window::getOverlay() const {
    return overlay.get();
}

void Glfw3Window::setOverlay(std::unique_ptr<Widget> _overlay) {
    overlay = std::move(_overlay);
}

bool Glfw3Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Glfw3Window::onWindowResize(int width, int height) {
    if (overlay) {
        overlay->resize(0, 0, width, height);
    }
}

void Glfw3Window::onFramebufferResize(int width, int height) {
    renderingContext->resizeViewPort(width, height);
}

void Glfw3Window::onWindowPosition(int x, int y) {

}

void Glfw3Window::onWindowIconify(bool iconified) {

}

void Glfw3Window::onWindowFocus(bool focused) {
    if (overlay) {
        preOrderTraverse(overlay, [&](const std::unique_ptr<Widget> &widget) {
            if (widget->getCanHoldFocus()) {
                widget->onFocus(focused);
            }
        });
    }
}

void Glfw3Window::onWindowRefresh() {
    render();
}

void Glfw3Window::onCharInput(events::CodePoint codePoint,
                              events::KeyModifiers modifiers) {
    if (overlay) {
        preOrderTraverse(overlay, [&](const std::unique_ptr<Widget> &widget) {
            if (widget->hasFocus()) {
                widget->onCharInput(codePoint, modifiers);
            }
        });
    }
}

void Glfw3Window::onKeyPressed(events::Key key, events::ScanCode scanCode,
                               events::KeyModifiers modifiers) {
    if (overlay) {
        preOrderTraverse(overlay, [&](const std::unique_ptr<Widget> &widget) {
            if (widget->hasFocus()) {
                widget->onKeyPressed(key, scanCode, modifiers);
            }
        });
    }
}

void Glfw3Window::onKeyReleased(events::Key key, events::ScanCode scanCode,
                                events::KeyModifiers modifiers) {
    if (overlay) {
        preOrderTraverse(overlay, [&](const std::unique_ptr<Widget> &widget) {
            if (widget->hasFocus()) {
                widget->onKeyReleased(key, scanCode, modifiers);
            }
        });
    }
}

void Glfw3Window::onKeyRepeat(events::Key key, events::ScanCode scancode,
                              events::KeyModifiers modifiers) {
    if (overlay) {
        preOrderTraverse(overlay, [&](const std::unique_ptr<Widget> &widget) {
            if (widget->hasFocus()) {
                widget->onKeyRepeat(key, scancode, modifiers);
            }
        });
    }
}

bool Glfw3Window::onMouseMove(float xPos, float yPos) {
    const float yInv = getHeight() - yPos;
    Widget *hitWidget = overlayHitTest(xPos, yInv);
    if (hitWidget) {
        return hitWidget->onMouseMove(xPos, yInv);
    } else {
        return false;
    }
}

bool Glfw3Window::onMouseButtonPressed(events::MouseButton button,
                                       events::KeyModifiers mods) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    const float yInv = getHeight() - yPos;

    Widget *hitWidget = overlayHitTest(xPos, yInv);
    if (hitWidget) {
        const bool canHoldFocus = hitWidget->getCanHoldFocus();
        if (canHoldFocus) {
            overlay->onFocus(false);
            hitWidget->onFocus(true);
        }

        return hitWidget->onMouseButtonPressed(button, mods);
    } else {
        return false;
    }
}

bool Glfw3Window::onMouseButtonReleased(events::MouseButton button,
                                        events::KeyModifiers mods) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    const float yInv = getHeight() - yPos;

    Widget *hitWidget = overlayHitTest(xPos, yInv);
    if (hitWidget) {
        return hitWidget->onMouseButtonReleased(button, mods);
    } else {
        return false;
    }
}

bool Glfw3Window::onMouseWheel(float xOffset, float yOffset) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    const float yInv = getHeight() - yPos;

    Widget *hitWidget = overlayHitTest(xPos, yInv);
    if (hitWidget) {
        return hitWidget->onMouseWheel(xOffset, yOffset);
    } else {
        return false;
    }
}

Glfw3Window *Glfw3Window::getGlfw3Window(GLFWwindow *window) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = std::find_if(windows.begin(), windows.end(),
                           [&](const Glfw3Window *glfw3Window) {
                               return glfw3Window &&
                                      glfw3Window->window == window;
    });

    if(it == windows.end()) {
        return nullptr;
    } else {
        return *it;
    }
}

bool Glfw3Window::createWindow(const WindowOptions &options) {

    for(auto& p : clientApiPairs) {
        if(p.clientApi == options.getClientApi()) {
            glfwWindowHint(GLFW_CLIENT_API, p.glfwValue);
            break;
        }
    }

    for(auto& p : contextApiPairs) {
        if(p.contextApi == options.getContextApi()) {
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, p.glfwValue);
            break;
        }
    }

    for(auto& p : contextRobustnessPairs) {
        if(p.robustness == options.getContextRobustness()) {
            glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, p.glfwValue);
            break;
        }
    }

    for(auto& p : releaseBehaviorPairs) {
        if(p.releaseBehavior == options.getContextReleaseBehavior()) {
            glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, p.glfwValue);
            break;
        }
    }

    const uint16_t style = options.getStyle();
    for(auto &p : stylePairs) {
        if(style & p.style) {
            glfwWindowHint(p.glfwValue, true);
        }
    }

    glfwWindowHint(GLFW_RED_BITS, options.getRedBits());
    glfwWindowHint(GLFW_GREEN_BITS, options.getGreenBits());
    glfwWindowHint(GLFW_BLUE_BITS, options.getBlueBits());
    glfwWindowHint(GLFW_ALPHA_BITS, options.getAlphaBits());
    glfwWindowHint(GLFW_DEPTH_BITS, options.getDepthBits());
    glfwWindowHint(GLFW_STENCIL_BITS, options.getStencilBits());
    glfwWindowHint(GLFW_SAMPLES, options.getSamples());
    glfwWindowHint(GLFW_REFRESH_RATE, options.getRefreshRate());

    int width;
    int height;
    GLFWmonitor *monitor = nullptr;

    if (options.isFullScreen()) {
        int count;
        const int selectedMonitor = options.getMonitor();
        GLFWmonitor **monitors = glfwGetMonitors(&count);
        if(!monitors || count == 0 || selectedMonitor >= count) {
            return false;
        }

        monitor = monitors[selectedMonitor];
        if(!monitor) {
            return false;
        }

        const GLFWvidmode *currentMode = glfwGetVideoMode(monitor);
        if(!currentMode) {
            return false;
        }

        width = currentMode->width;
        height = currentMode->height;
    } else {
        width = options.getWidth();
        height = options.getHeight();
    }

    window = glfwCreateWindow(width, height, options.getTitle().c_str(), monitor, nullptr);

    if (!window) {
        return false;
    }

    std::lock_guard<std::mutex> lock(mutex);
    windows.push_back(this);

    return true;
}

bool Glfw3Window::initializeCallbacks() {
    if (!window) {
        return false;
    }

    glfwSetCharModsCallback(window, Glfw3Window::characterCallback);
    glfwSetCursorPosCallback(window, Glfw3Window::cursorPositionCallback);
    glfwSetFramebufferSizeCallback(window, Glfw3Window::framebufferSizeCallback);
    glfwSetKeyCallback(window, Glfw3Window::keyCallback);
    glfwSetMouseButtonCallback(window, Glfw3Window::mouseButtonCallback);
    glfwSetScrollCallback(window, Glfw3Window::scrollCallback);
    glfwSetWindowIconifyCallback(window, Glfw3Window::windowIconifyCallback);
    glfwSetWindowFocusCallback(window, Glfw3Window::windowFocusCallback);
    glfwSetWindowPosCallback(window, Glfw3Window::windowPositionCallback);
    glfwSetWindowRefreshCallback(window, Glfw3Window::windowRefreshCallback);
    glfwSetWindowSizeCallback(window, Glfw3Window::windowSizeCallback);

    return true;
}

bool Glfw3Window::initializeRenderingContext(
        const OverlayRenderingOptions &options) {
    if (!window) {
        return false;
    }

    using ContextHandle = OverlayRenderingContext::ContextHandle;
    const ContextHandle contextHandle = reinterpret_cast<ContextHandle>(window);
    renderingContext = OverlayRenderingContext::create(contextHandle, options);
    if (!renderingContext) {
        return false;
    }

    renderingContext->makeCurrent();

    int width;
    int height;

    glfwGetFramebufferSize(window, &width, &height);

    renderingContext->resizeViewPort(width, height);

    const glm::vec3 eye(0.0f, 0.0f, 1.0f);
    const glm::vec3 center(0.0f);
    const glm::vec3 up(0.0f, 1.0f, 0.0f);
    renderingContext->getProjection().cameraLookAt(eye, center, up);

    return true;
}

void Glfw3Window::destroy() {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = std::remove(windows.begin(), windows.end(), this);
    if (it != windows.end()) {
        windows.erase(it);
    }

    glfwSetCharModsCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);
    glfwSetFramebufferSizeCallback(window, nullptr);
    glfwSetKeyCallback(window, nullptr);
    glfwSetMouseButtonCallback(window, nullptr);
    glfwSetScrollCallback(window, nullptr);
    glfwSetWindowIconifyCallback(window, nullptr);
    glfwSetWindowFocusCallback(window, nullptr);
    glfwSetWindowPosCallback(window, nullptr);
    glfwSetWindowRefreshCallback(window, nullptr);
    glfwSetWindowSizeCallback(window, nullptr);

    glfwDestroyWindow(window);
}

Widget *Glfw3Window::overlayHitTest(float xPos, float yPos) {
    if (!overlay) {
        return nullptr;

    }

    const Point p(xPos, yPos);
    std::vector<Widget *> hitChildren;

    if (overlay) {
        preOrderTraverse(overlay, [&](const std::unique_ptr<Widget> &widget) {
            if (widget->getRect().isInside(p)) {
                hitChildren.push_back(widget.get());
            }
        });
    }

    if (hitChildren.size() > 0) {
        Widget *topChild = hitChildren[0];
        for (const auto child : hitChildren) {
            if (child->getZOrder() >= topChild->getZOrder()) {
                topChild = child;
            }
        }

        return topChild;
    }

    return overlay.get();
}

void Glfw3Window::characterCallback(GLFWwindow *window, unsigned int codePoint,
                                    int mods) {
    auto glfw3Window = getGlfw3Window(window);
    if (!glfw3Window) {
        return;
    }

    glfw3Window->onCharInput(codePoint,
                             Glfw3EventTranslator::translateModifiers(mods));
}

void Glfw3Window::cursorPositionCallback(GLFWwindow *window, double xPos,
                                         double yPos) {
    auto glfw3Window = getGlfw3Window(window);
    if (!glfw3Window) {
        return;
    }

    glfw3Window->onMouseMove(xPos, yPos);
}

void Glfw3Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    auto glfw3Window = getGlfw3Window(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onFramebufferResize(width, height);
}

void
Glfw3Window::keyCallback(GLFWwindow *window, int key, int scanCode, int action,
                         int mods) {
    auto glfw3Window = getGlfw3Window(window);
    if (!glfw3Window) {
        return;
    }

    const events::Key translatedKey = Glfw3EventTranslator::translateKey(key);
    const events::KeyModifiers translatedModifiers = Glfw3EventTranslator::translateModifiers(
            mods);

    if (action == GLFW_PRESS) {
        glfw3Window->onKeyPressed(translatedKey, scanCode, translatedModifiers);
    } else if (action == GLFW_RELEASE) {
        glfw3Window->onKeyReleased(translatedKey, scanCode,
                                   translatedModifiers);
    } else if (action == GLFW_REPEAT) {
        glfw3Window->onKeyRepeat(translatedKey, scanCode, translatedModifiers);
    }
}

void
Glfw3Window::mouseButtonCallback(GLFWwindow *window, int button, int action,
                                 int mods) {
    auto glfw3Window = getGlfw3Window(window);
    if (!glfw3Window) {
        return;
    }

    const events::MouseButton translatedButton = Glfw3EventTranslator::translateMouseButton(
            button);
    const events::KeyModifiers translatedModifiers = Glfw3EventTranslator::translateModifiers(
            mods);

    if (action == GLFW_PRESS) {
        glfw3Window->onMouseButtonPressed(translatedButton,
                                          translatedModifiers);
    } else {
        glfw3Window->onMouseButtonReleased(translatedButton,
                                           translatedModifiers);
    }
}

void Glfw3Window::scrollCallback(GLFWwindow *window, double xOffset,
                                 double yOffset) {
    auto glfw3Window = getGlfw3Window(window);
    if (!glfw3Window) {
        return;
    }

    glfw3Window->onMouseWheel(xOffset, yOffset);
}

void Glfw3Window::windowIconifyCallback(GLFWwindow *window, int iconified) {
    auto glfw3Window = getGlfw3Window(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowIconify(iconified);
}

void Glfw3Window::windowFocusCallback(GLFWwindow *window, int focused) {
    auto glfw3Window = getGlfw3Window(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowFocus(focused);
}

void Glfw3Window::windowPositionCallback(GLFWwindow *window, int x, int y) {
    auto glfw3Window = getGlfw3Window(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowPosition(x, y);
}

void Glfw3Window::windowRefreshCallback(GLFWwindow *window) {
    auto glfw3Window = getGlfw3Window(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowRefresh();
}

void Glfw3Window::windowSizeCallback(GLFWwindow *window, int width, int height) {
    auto glfw3Window = getGlfw3Window(window);
    if(!glfw3Window) {
        return;
    }

    glfw3Window->onWindowResize(width, height);
}

}
}
}
