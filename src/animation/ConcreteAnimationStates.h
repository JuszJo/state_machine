#pragma once

#include "AnimationState.h"
#include "Animation.h"

class Idle : public AnimationState {
    public:
        const char* texturePath = "src\\assets\\playeridle.png";

        Idle();

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};

class RunRight : public AnimationState {
    public:
        const char* texturePath = "src\\assets\\player.png";

        RunRight();

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};

class RunLeft : public AnimationState {
    public:
        const char* texturePath = "src\\assets\\player2.png";

        RunLeft();

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};

class Up : public AnimationState {
    public:
        const char* texturePath = "src\\assets\\playerup.png";

        Up();

        void enter(Animation* animation);
        void toggleAnimation(Animation* animation, AnimationState& animationState);
        void exit(Animation* animation);
        static AnimationState& getInstance();
};