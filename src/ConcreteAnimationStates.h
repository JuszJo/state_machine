#pragma once

#include "AnimationState.h"
#include "Animation.h"

class Idle : public AnimationState {
    public:
        const char* texturePath = "src\\assets\\playeridle.png";

        Idle() {
            name = "idle";

            loadImage(texturePath, &TBO);
        }

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};

class RunRight : public AnimationState {
    public:
        const char* texturePath = "src\\assets\\player.png";

        RunRight() {
            name = "run right";

            loadImage(texturePath, &TBO);
        }

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};