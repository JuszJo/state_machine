#ifndef PLAYER_H
#define PLAYER_H

#include "entityV2.h"

#include "../game.h"

#include "keyinput.h"

#include "animation/Animation.h"
#include "animation/ConcreteAnimationStates.h"

// #include "entity.h"
// #include "animation.h"
// #include "gravity.h"
// #include "collision.h"
// #include "hitbox.h"
// #include "enemy.h"
// #include "enemyFactory.h"

class Player: public EntityV2 {
    private:
        int stride = 5;

    public:
        unsigned int TBO2, TBO3, TBO4, TBO5, TBO6;

        float playerWidth, playerHeight, playerX, playerY;

        glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f);

        float acceleration = 2.0f;

        Animation animation;

        // default constructor
        Player() {}

        Player(const char* texturePath, float xPos, float yPos, float playerWidth, float playerHeight) {
            x = xPos;
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

            loadImage(texturePath, &TBO);

            // Hitbox newHitbox(x, y, 30.0f, height);

            // newHitbox.defineOffset(18.0f, 10.0f);

            // hitbox = newHitbox;

            // Hitbox newAttackHitbox(x, y, 50.0f, 40.0f);

            // newAttackHitbox.defineOffset(18.0f, 10.0f);

            // attackHitbox = newAttackHitbox;
        }

        void checkKeyInput() {
            if(KeyInput::key.a) {
                // std::cout << "left\n";
                // currentState = LEFT
            }
            if(KeyInput::key.d) {
                if(animation.currentState != &RunRight::getInstance()) {
                    std::cout << "right\n";
                    speed = glm::vec3(acceleration, speed.y, 0.0f);
                    animation.setState(RunRight::getInstance());
                }
                // currentState = RIGHT;
            }
            if(!KeyInput::key.a && !KeyInput::key.d && !KeyInput::key.w && !KeyInput::key.s) {
                if(animation.currentState != &Idle::getInstance()) {
                    std::cout << "idle\n";
                    speed = glm::vec3(0.0f, speed.y, 0.0f);
                    animation.setState(Idle::getInstance());
                }
                // currentState = IDLE;
            }
        }


        void checkState() {
            // switch (currentState) {
            //     case LEFT:
            //         speed = glm::vec3(-acceleration, speed.y, 0.0f);
                    
            //         break;

            //     case RIGHT:
            //         speed = glm::vec3(acceleration, speed.y, 0.0f);
                    
            //         break;

            //     case DOWN:
            //         speed = glm::vec3(0.0f, -acceleration, 0.0f);
                    
            //         break;

            //     case UP:
            //         speed = glm::vec3(0.0f, acceleration, 0.0f);
                    
            //         break;

            //     case IDLE:
            //         // speed = glm::vec3(0.0f, 0.0f, 0.0f);
            //         speed = glm::vec3(0.0f, speed.y, 0.0f);
                    
            //         break;
                
            //     default:
            //         break;
            // }
        }

        void move() {
            x += speed.x;
            y += speed.y;

            // printf("x: %f, y: %f\n", playerX, playerY);
        }

        void updatePosition(float newPlayerX, float newPlayerY) {
            x = newPlayerX;
            y = newPlayerY;
        }

        void updateSize(float newPlayerWidth, float newPlayerHeight) {
            width = newPlayerWidth;
            height = newPlayerHeight;
        }

        void render(glm::mat4 projection) override {
            shader->use();
            glUniformMatrix4fv(glGetUniformLocation(shader -> shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            // glUniformMatrix4fv(glGetUniformLocation(shader -> shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shader -> shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
            setUniform1f(shader, "totalFrames", animation.currentState->totalFrames);
            setUniform1f(shader, "currentFrame", animation.currentState->currentFrame);
            glBindTexture(GL_TEXTURE_2D, animation.currentState->TBO);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        void update() {
            checkKeyInput();
            animation.animate();
            // checkState();
            move();

            model = glm::mat4(1.0f);

            model = glm::translate(model, glm::vec3(x, y, 0.0f));
        }

        void resetModel() {
            model = glm::mat4(1.0f);
        }
};

#endif