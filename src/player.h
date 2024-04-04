#ifndef PLAYER_H
#define PLAYER_H

#include "entityV2.h"

#include "../game.h"

#include "keyinput.h"

#include "animation/Animation.h"
#include "animation/ConcreteAnimationStates.h"

class Player: public EntityV2 {
    private:
        int stride = 5;

    public:
        unsigned int TBO2, TBO3, TBO4, TBO5, TBO6;

        float playerWidth, playerHeight, playerX, playerY;

        // default constructor
        Player() {}

        Player(const char* texturePath, float xPos, float yPos, float playerWidth, float playerHeight) {
            /* x = xPos;
            y = yPos;
            width = playerWidth;
            height = playerHeight;

            float vertices[20] = {
                x, y, 0.0f, 0.0f, 1.0f,
                x + width, y, 0.0f, 1.0f, 1.0f,
                x, y + height, 0.0f, 0.0f, 0.0f,
                x + width, y + height, 0.0f, 1.0f, 0.0f
            };
            genVertexandBuffers(&VAO, &VBO);
            bindVAO(VAO);

            int verticeSize = sizeof(vertices);
            handleVertexBufferObject(VBO, vertices, verticeSize);

            handleVertexArrayObject(0, 3, stride, 0);
            handleVertexArrayObject(1, 2, stride, 3);

            cleanupBuffers();

            loadImage(texturePath, &TBO); */
        }
};

#endif