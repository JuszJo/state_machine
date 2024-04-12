#pragma once

#include "State.h"

class State;

class StateMachine {
    public:
        State* currentState;
        
        StateMachine();

        // This will get called by the current state
        void setState(State& state);

        void toggleState(State& state);

        // void update();
};

