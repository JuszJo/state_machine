#pragma once

#include "AnimationState.h"
#include "Animation.h"

class Idle : public AnimationState {
    public:
        Idle() {
            name = "idle";
        }

        const char* texturePath = "src\\assets\\playeridle.png";

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};

class RunRight : public AnimationState {
    public:
        RunRight() {
            name = "run right";
        }

        const char* texturePath = "src\\assets\\player.png";

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};