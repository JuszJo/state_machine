#pragma once

#include <vector>

#include "events.h"

class Event {
    public:
        GameEvents eventType;

        Event(GameEvents event) {
            this->eventType = event;
        }
};

class EventManager {
    public:
        static const std::vector<Event> events;
        
        EventManager() {};

        static addEvent(Event event) const {
            events.push_back(event);
        }
};

