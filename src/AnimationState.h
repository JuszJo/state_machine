#pragma once

#include "Animation.h"

class Animation;

class AnimationState {
    public:
        const char* name;
        virtual void enter(Animation* animation) = 0;
        virtual void toggleAnimation(Animation* animation, AnimationState& animationState) = 0;
        virtual void exit(Animation* animation) = 0;

        virtual ~AnimationState(){};
};