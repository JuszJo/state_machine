#ifndef PLAYER_H
#define PLAYER_H

#include "entityV2.h"
#include "../utils/image_loader.h"

#include "../game.h"

#include "components/components.h"

#include "animation/Animation.h"
#include "animation/ConcreteAnimationStates.h"

class Player: public EntityV2 {
    private:
        int stride = 5;

    public:
        unsigned int TBO2, TBO3, TBO4, TBO5, TBO6;

        float playerWidth, playerHeight, playerX, playerY;

        enum PlayerState {
            IDLE,
            RIGHT,
            LEFT,
        };

        PlayerState playerState = PlayerState::IDLE;

        bool jump = false;

        // default constructor
        Player() {}

        Player(const char* texturePath): EntityV2() {
            this->addComponent<PlayerComponent>(ComponentType::PLAYER);

            this->addComponent<UpdateComponent>(ComponentType::UPDATE);

            SizeComponent* sizeComponent = this->addComponent<SizeComponent>(ComponentType::SIZE);
            sizeComponent->width = 78.0f;
            sizeComponent->height = 58.0f;

            PositionComponent* positionComponent = this->addComponent<PositionComponent>(ComponentType::POSITION);
            positionComponent->position = glm::vec3(0.0f, 0.0f, 0.0f);

            HitboxComponent* hitboxComponent = this->addComponent<HitboxComponent>(ComponentType::HITBOX);
            hitboxComponent->positionComponent = positionComponent;
            hitboxComponent->offsetX = 15.0f;
            hitboxComponent->offsetY = 14.0f;
            hitboxComponent->size.width = sizeComponent->width - (hitboxComponent->offsetX * 2.0f + 10.0f);
            hitboxComponent->size.height = sizeComponent->height - (hitboxComponent->offsetY * 2.0f);

            MovementComponent* movementComponent = this->addComponent<MovementComponent>(ComponentType::MOVEMENT);
            movementComponent->acceleration = 2.0f;
            movementComponent->speed = glm::vec3(0.0f, 0.0f, 0.0f);

            JumpComponent* jumpComponent = this->addComponent<JumpComponent>(ComponentType::JUMP);
            jumpComponent->jumpForce = 10.0f;
            jumpComponent->canJump = true;

            RenderComponent* renderComponent = this->addComponent<RenderComponent>(ComponentType::RENDER);
            renderComponent->shader = new Shader("shaders\\vertexShader.glsl", "shaders\\fragmentShader.glsl");
            renderComponent->model = glm::mat4(1.0f);

            AnimationComponent* animationComponent = this->addComponent<AnimationComponent>(ComponentType::ANIMATION);
            animationComponent->animation = new Animation();
            renderComponent->TBO = &animationComponent->animation->currentState->TBO;

            GravityComponent* gravityComponent = this->addComponent<GravityComponent>(ComponentType::GRAVITY);

            CollisionComponent* collisionComponent = this->addComponent<CollisionComponent>(ComponentType::COLLISION);

            float vertices[20] = {
                positionComponent->position.x, positionComponent->position.y, 0.0f, 0.0f, 1.0f,
                positionComponent->position.x + sizeComponent->width, positionComponent->position.y, 0.0f, 1.0f, 1.0f,
                positionComponent->position.x, positionComponent->position.y + sizeComponent->height, 0.0f, 0.0f, 0.0f,
                positionComponent->position.x + sizeComponent->width, positionComponent->position.y + sizeComponent->height, 0.0f, 1.0f, 0.0f
            };

            genVertexandBuffers(&renderComponent->VAO, &renderComponent->VBO);
            bindVAO(renderComponent->VAO);

            int verticeSize = sizeof(vertices);
            handleVertexBufferObject(renderComponent->VBO, vertices, verticeSize);

            handleVertexArrayObject(0, 3, stride, 0);
            handleVertexArrayObject(1, 2, stride, 3);

            cleanupBuffers();

            ImageLoader::loadImage(texturePath, renderComponent->TBO);
        }

        void updatePositionComponent() {
            if(
                !this->hasComponent<PositionComponent>(ComponentType::POSITION) ||
                !this->hasComponent<MovementComponent>(ComponentType::MOVEMENT)
            ) return;

            PositionComponent* positionComponent = this->getComponent<PositionComponent>(ComponentType::POSITION);
            MovementComponent* movementComponent = this->getComponent<MovementComponent>(ComponentType::MOVEMENT);

            positionComponent->position.x += movementComponent->speed.x;
            positionComponent->position.y += movementComponent->speed.y;
        }

        void switchState(PlayerState state) {
            playerState = state;
        }

        void listenToInput() {
            if(KeyInput::key.a) {
                if(playerState != PlayerState::LEFT) switchState(PlayerState::LEFT);
            }
            if(KeyInput::key.d) {
                if(playerState != PlayerState::RIGHT) switchState(PlayerState::RIGHT);
            }
            if(!KeyInput::key.a && !KeyInput::key.d) {
                if(playerState != PlayerState::IDLE)
                switchState(PlayerState::IDLE);
            }
        }

        void listenForJump() {
            JumpComponent* jumpComponent = this->getComponent<JumpComponent>(ComponentType::JUMP);
            MovementComponent* movementComponent = this->getComponent<MovementComponent>(ComponentType::MOVEMENT);

            if(KeyInput::key.w && jumpComponent->canJump) {
                movementComponent->speed.y = 10.0f;
                jumpComponent->canJump = false;
            }
        }

        void checkState() {
            if(
                !this->hasComponent<RenderComponent>(ComponentType::RENDER) ||
                !this->hasComponent<AnimationComponent>(ComponentType::ANIMATION)
            ) return;

            MovementComponent* movementComponent = this->getComponent<MovementComponent>(ComponentType::MOVEMENT);
            AnimationComponent* animationComponent = this->getComponent<AnimationComponent>(ComponentType::ANIMATION);

            switch(playerState) {
                case PlayerState::IDLE:
                    movementComponent->speed.x = 0.0f;

                    if(animationComponent->animation->currentState != &Idle::getInstance()) {
                        animationComponent->animation->toggleAnimation(Idle::getInstance());
                    }
                    break;

                case PlayerState::RIGHT:
                    movementComponent->speed.x = movementComponent->acceleration;

                    if(animationComponent->animation->currentState != &RunRight::getInstance()) {
                        animationComponent->animation->toggleAnimation(RunRight::getInstance());
                    }
                    break;

                case PlayerState::LEFT:
                    movementComponent->speed.x = -movementComponent->acceleration;

                    if(animationComponent->animation->currentState != &RunLeft::getInstance()) {
                        animationComponent->animation->toggleAnimation(RunLeft::getInstance());
                    }
                    break;
                
                default:
                    break;
            }
        }

        void render() override {
            RenderComponent* renderComponent = this->getComponent<RenderComponent>(ComponentType::RENDER);

            if(this->hasComponent<PositionComponent>(ComponentType::POSITION)) {
                PositionComponent* positionComponent = this->getComponent<PositionComponent>(ComponentType::POSITION);
                renderComponent->model = glm::mat4(1.0f);
                renderComponent->model = glm::translate(renderComponent->model, glm::vec3(positionComponent->position.x, positionComponent->position.y, 0.0f));
            }

            renderComponent->shader->use();

            this->setUniformMatrix4fv(renderComponent->shader, "projection", *renderComponent->projection);
            // this->setUniformMatrix4fv(renderComponent->shader, "view", *renderComponent->view);
            this->setUniformMatrix4fv(renderComponent->shader, "model", renderComponent->model);

            if(this->hasComponent<AnimationComponent>(ComponentType::ANIMATION)) {
                AnimationComponent* animationComponent = this->getComponent<AnimationComponent>(ComponentType::ANIMATION);
                this->setUniform1i(renderComponent->shader, "totalFrames", animationComponent->animation->currentState->totalFrames);
                this->setUniform1i(renderComponent->shader, "currentFrame", animationComponent->animation->currentState->currentFrame);
                glBindTexture(GL_TEXTURE_2D, animationComponent->animation->currentState->TBO);
            }
            else {
                glBindTexture(GL_TEXTURE_2D, *renderComponent->TBO);
            }

            glBindVertexArray(renderComponent->VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        void update() override {
            listenToInput();
            checkState();
            listenForJump();
            updatePositionComponent();
        }
};

#endif