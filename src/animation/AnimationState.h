#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include "../libs/stb_image.h"

#include "Animation.h"

class Animation;

class AnimationState {
    public:
        const char* name;
        unsigned int TBO;
        int frameBuffer;
        float totalFrames;
        float currentFrame;
        virtual void enter(Animation* animation) = 0;
        virtual void toggleAnimation(Animation* animation, AnimationState& animationState) = 0;
        virtual void exit(Animation* animation) = 0;

        virtual ~AnimationState(){};
};