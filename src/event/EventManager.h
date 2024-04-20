#pragma once

#include <vector>

class Event {
    public:
};

class EventManager {
    public:
        static const std::vector<Event> events;
        
        EventManager() {};
};

