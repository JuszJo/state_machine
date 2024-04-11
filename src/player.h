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
            PlayerComponent* playerComponent = new PlayerComponent;
            playerComponent->base.type = ComponentType::PLAYER;
            this->components[ComponentType::PLAYER] = (BaseComponent*)playerComponent;

            SizeComponent* sizeComponent = new SizeComponent;
            sizeComponent->base.type = ComponentType::SIZE;
            sizeComponent->width = 78.0f;
            sizeComponent->height = 58.0f;
            this->components[ComponentType::SIZE] = (BaseComponent*)sizeComponent;

            PositionComponent* positionComponent = new PositionComponent;
            positionComponent->base.type = ComponentType::POSITION;
            positionComponent->position = glm::vec3(0.0f, 0.0f, 0.0f);
            this->components[ComponentType::POSITION] = (BaseComponent*)positionComponent;

            MovementComponent* move = new MovementComponent;
            move->base.type = ComponentType::MOVEMENT;
            move->acceleration = 2.0f;
            move->speed = glm::vec3(0.0f, 0.0f, 0.0f);
            this->components[ComponentType::MOVEMENT] = (BaseComponent*)move;

            RenderComponent* render = new RenderComponent;
            render->base.type = ComponentType::RENDER;
            render->shader = new Shader("shaders\\vertexShader.glsl", "shaders\\fragmentShader.glsl");
            render->model = glm::mat4(1.0f);
            render->VAO = 1;
            render->VBO = 2;
            this->components[ComponentType::RENDER] = (BaseComponent*)render;

            AnimationComponent* animationComponent = new AnimationComponent;
            animationComponent->animation = new Animation();
            animationComponent->base.type = ComponentType::ANIMATION;
            render->TBO = &animationComponent->animation->currentState->TBO;
            this->components[ComponentType::ANIMATION] = (BaseComponent*)animationComponent;

            GravityComponent* gravityComponent = new GravityComponent;
            gravityComponent->base.type = ComponentType::GRAVITY;
            gravityComponent->gForce = glm::vec3(0.0f, 0.1f, 0.0f);
            this->components[ComponentType::GRAVITY] = (BaseComponent*)gravityComponent;

            float vertices[20] = {
                positionComponent->position.x, positionComponent->position.y, 0.0f, 0.0f, 1.0f,
                positionComponent->position.x + sizeComponent->width, positionComponent->position.y, 0.0f, 1.0f, 1.0f,
                positionComponent->position.x, positionComponent->position.y + sizeComponent->height, 0.0f, 0.0f, 0.0f,
                positionComponent->position.x + sizeComponent->width, positionComponent->position.y + sizeComponent->height, 0.0f, 1.0f, 0.0f
            };

            genVertexandBuffers(&render->VAO, &render->VBO);
            bindVAO(render->VAO);

            int verticeSize = sizeof(vertices);
            handleVertexBufferObject(render->VBO, vertices, verticeSize);

            handleVertexArrayObject(0, 3, stride, 0);
            handleVertexArrayObject(1, 2, stride, 3);

            cleanupBuffers();

            ImageLoader::loadImage(texturePath, render->TBO);
            
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