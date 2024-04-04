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

        void loadImage(const char* path, unsigned int* TBO) {
            int width, height, nChannels;

            stbi_uc* imageData = stbi_load(path, &width, &height, &nChannels, 0);

            if(!imageData) {
                const char* reason = stbi_failure_reason();

                std::cout << reason << std::endl;
            }

            glGenTextures(1, TBO);
            glBindTexture(GL_TEXTURE_2D, *TBO);

            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            if(nChannels > 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            }

            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(imageData);
        }
};