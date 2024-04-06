#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <glm/glm.hpp>

#include "../../utils/my_array.h"

#include "../keyinput.h"

#include "../EntityManager.h"
#include "../components/components.h"

class MovementSystem {
    public:
        MovementSystem() {}
        
        void update() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<PlayerComponent>(ComponentType::PLAYER);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentPlayer = entities[i];

                if(
                    currentPlayer->hasComponent<PositionComponent>(ComponentType::POSITION) &&
                    currentPlayer->hasComponent<MovementComponent>(ComponentType::MOVEMENT)
                ) {
                    PositionComponent* positionComponent = currentPlayer->getComponent<PositionComponent>(ComponentType::POSITION);
                    MovementComponent* movementComponent = currentPlayer->getComponent<MovementComponent>(ComponentType::MOVEMENT);
                    RenderComponent* renderComponent = currentPlayer->getComponent<RenderComponent>(ComponentType::RENDER);

                    if(KeyInput::key.a) {
                        movementComponent->speed.x = -movementComponent->acceleration;
                    }
                    if(KeyInput::key.d) {
                        movementComponent->speed.x = movementComponent->acceleration;
                    }
                    if(!KeyInput::key.a && !KeyInput::key.d) {
                        movementComponent->speed.x = 0.0f;
                    }

                    positionComponent->position.x += movementComponent->speed.x;
                    positionComponent->position.y += movementComponent->speed.y;

                    renderComponent->model = glm::mat4(1.0f);
                    renderComponent->model = glm::translate(renderComponent->model, glm::vec3(positionComponent->position.x, positionComponent->position.y, 0.0f));
                }
            }
        }
};

#endif
