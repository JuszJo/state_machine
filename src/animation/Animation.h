#pragma once

#include "AnimationState.h"

class AnimationState;

class Animation {
    public:
        int elapsedFrames = 0;
        
        AnimationState* currentState;
        
        Animation();

        // This will get called by the current state
        void setState(AnimationState& newState);

        void toggleAnimation(AnimationState& animationState);

        void animate();
};

