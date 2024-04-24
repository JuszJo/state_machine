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
        static std::vector<Event> events;
        
        EventManager() {};

        static void addEvent(Event event) {
            events.push_back(event);
        }
};

