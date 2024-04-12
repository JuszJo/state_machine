#pragma once

// #include "AnimationState.h"

// class AnimationState;

class StateMachine {
    public:
        // AnimationState* currentState;
        
        StateMachine();

        // This will get called by the current state
        void setState(/* AnimationState& newState */);

        void toggleState(/* AnimationState& animationState */);

        // void update();
};

