#pragma once

#include "../../utils/my_array.h"

#include "../EntityManager.h"
#include "../components/components.h"

class GravitySystem {
    public:
        GravitySystem() {}

        void update() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<GravityComponent>(ComponentType::GRAVITY);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];

                if(currentEntity->hasComponent<MovementComponent>(ComponentType::MOVEMENT)) {
                    GravityComponent* gravityComponent = currentEntity->getComponent<GravityComponent>(ComponentType::GRAVITY);
                    MovementComponent* movementComponent = currentEntity->getComponent<MovementComponent>(ComponentType::MOVEMENT);

                    movementComponent->speed -= gravityComponent->gForce;
                }
            }
        }
};