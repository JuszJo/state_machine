#pragma once

#include "AnimationState.h"

class AnimationState;

class Animation {
    public:
        AnimationState* currentState;
        
        Animation();

        void nextState();

        // This will get called by the current state
        void setState(AnimationState& newState);

        void toggle();
};

