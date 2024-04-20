#pragma once

#include <vector>

#include "events.h"

class Event {
    public:

        Event() {}
};

class EventManager {
    public:
        static const std::vector<Event> events;
        
        EventManager() {};
};

