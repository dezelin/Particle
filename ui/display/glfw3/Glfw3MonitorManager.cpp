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

#include "Glfw3MonitorManager.h"

#include <algorithm>

namespace ui {

namespace display {

Glfw3MonitorManager::Glfw3MonitorManager() {
    initialize();
}

Glfw3MonitorManager::~Glfw3MonitorManager() {
    destroy();
}

std::unique_ptr<Monitor> Glfw3MonitorManager::getPrimaryMonitor() const {
    GLFWmonitor *primary = glfwGetPrimaryMonitor();
    if(!primary) {
        return nullptr;
    }

    return std::make_unique<Glfw3Monitor>(primary, 0);
}

int Glfw3MonitorManager::getMonitorCount() const {
    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
    return monitors ? monitorCount : 0;
}

std::unique_ptr<Monitor> Glfw3MonitorManager::getMonitor(unsigned index) const {
    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
    if(!monitors || monitorCount <= 0) {
        return nullptr;
    }

    if(index >= monitorCount) {
        throw nullptr;
    }

    return std::make_unique<Glfw3Monitor>(monitors[index], index);
}

void Glfw3MonitorManager::initialize() {
    glfwSetMonitorCallback(monitorCallback);
}

void Glfw3MonitorManager::destroy() {
    glfwSetMonitorCallback(nullptr);
}

void Glfw3MonitorManager::monitorCallback(GLFWmonitor *monitor, int event) {
    if(!monitor) {
        return;
    }

    unsigned index = 0;
    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

    if(monitors) {
        for (int i = 0; i < monitorCount; ++i) {
            if (monitors[i] != monitor) {
                index++;
            } else {
                break;
            }
        }
    }

    Glfw3Monitor mon(monitor, index);

    const Glfw3MonitorManager& manager = static_cast<Glfw3MonitorManager&>(getInstance());

    if (event == GLFW_CONNECTED) {
        for(auto subscriber : manager.subscribers) {
            subscriber->onMonitorConnected(&mon);
        }
    }
    else if (event == GLFW_DISCONNECTED) {
        for(auto subscriber : manager.subscribers) {
            subscriber->onMonitorDisconnected(&mon);
        }
    }
}

void Glfw3MonitorManager::subscribe(MonitorManagerSubscriber *subscriber) {
    subscribers.push_back(subscriber);
}

void Glfw3MonitorManager::unsubscribe(MonitorManagerSubscriber *subscriber) {
    auto it = std::remove(subscribers.begin(), subscribers.end(), subscriber);
    subscribers.erase(it);
}

}
}
