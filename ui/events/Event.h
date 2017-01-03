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

#ifndef PARTICLE_EVENT_H
#define PARTICLE_EVENT_H

#include "EventHandler.h"

#include <algorithm>
#include <vector>

namespace ui {

namespace events {

template <typename ...Args>
class Event {
public:
    std::vector<EventHandlerBase<Args...>*> handlers;

    template<typename Listener>
    void attach(Listener *listener, void (Listener::*member)(Args...)) {
        handlers.push_back(new EventHandler<Listener, Args...>(listener, member));
    }

    template<typename Listener>
    void detach(Listener *listener, void (Listener::*member)(Args...)) {
        auto it = std::remove_if(handlers.begin(), handlers.end(),
                                 [&](EventHandlerBase<Args...> *callable) {

            EventHandler<Listener, Args...> *handler =
                    static_cast<EventHandler<Listener, Args...>*>(callable);
            return handler != nullptr
                   && handler->getListener() == listener
                   && handler->getMember() == member;
        });

        handlers.erase(it);
    }

    void notify(Args ...args) const {
        for(auto handler : handlers) {
            if(handler) {
                handler->notify(args...);
            }
        }
    }

};

}
}

#endif //PARTICLE_EVENT_H
