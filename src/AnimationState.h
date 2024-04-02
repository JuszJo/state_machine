#pragma once

#include "Animation.h"

class Animation;

class AnimationState {
    public:
        virtual void enter(Animation* animation) = 0;
        virtual void toggleAnimation(Animation* animation) = 0;
        virtual void exit(Animation* animation) = 0;

        virtual ~AnimationState(){};
};