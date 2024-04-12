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

        // default constructor
        Player() {}

        Player(const char* texturePath): EntityV2() {
            this->addComponent<PlayerComponent>(ComponentType::PLAYER);

            SizeComponent* sizeComponent = this->addComponent<SizeComponent>(ComponentType::SIZE);
            sizeComponent->width = 78.0f;
            sizeComponent->height = 58.0f;

            PositionComponent* positionComponent = this->addComponent<PositionComponent>(ComponentType::POSITION);
            positionComponent->position = glm::vec3(0.0f, 0.0f, 0.0f);

            MovementComponent* movementComponent = this->addComponent<MovementComponent>(ComponentType::MOVEMENT);
            movementComponent->acceleration = 2.0f;
            movementComponent->speed = glm::vec3(0.0f, 0.0f, 0.0f);

            RenderComponent* renderComponent = this->addComponent<RenderComponent>(ComponentType::RENDER);
            renderComponent->shader = new Shader("shaders\\vertexShader.glsl", "shaders\\fragmentShader.glsl");
            renderComponent->model = glm::mat4(1.0f);

            AnimationComponent* animationComponent = this->addComponent<AnimationComponent>(ComponentType::ANIMATION);
            animationComponent->animation = new Animation();
            renderComponent->TBO = &animationComponent->animation->currentState->TBO;

            GravityComponent* gravityComponent = this->addComponent<GravityComponent>(ComponentType::GRAVITY);
            gravityComponent->gForce = glm::vec3(0.0f, 0.3f, 0.0f);

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
            
            /* genVertexandBuffers(&VAO, &VBO);
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