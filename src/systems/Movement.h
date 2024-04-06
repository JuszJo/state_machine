#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../../utils/my_array.h"
#include "../EntityManager.h"
#include "../components/components.h"

class MovementSystem {
    public:
        MovementSystem() {}
        
        void update() {
            MyArray<MovementComponent*> movementComponents = EntityManager::getComponentsByEntity<MovementComponent>(ComponentType::MOVEMENT);
            
            // movementComponent->speed.x += 0.01;
            // EntityManager::

            // MovementComponent& movement = entity.getComponent<MovementComponent>();

            // Logic to update player movement based on input, etc.
        }
};

#endif
