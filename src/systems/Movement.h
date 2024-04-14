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
                    currentPlayer->hasComponent<MovementComponent>(ComponentType::MOVEMENT) &&
                    currentPlayer->hasComponent<RenderComponent>(ComponentType::RENDER) &&
                    currentPlayer->hasComponent<AnimationComponent>(ComponentType::ANIMATION)
                ) {
                    PositionComponent* positionComponent = currentPlayer->getComponent<PositionComponent>(ComponentType::POSITION);
                    MovementComponent* movementComponent = currentPlayer->getComponent<MovementComponent>(ComponentType::MOVEMENT);
                    RenderComponent* renderComponent = currentPlayer->getComponent<RenderComponent>(ComponentType::RENDER);
                    AnimationComponent* animationComponent = currentPlayer->getComponent<AnimationComponent>(ComponentType::ANIMATION);

                    if(KeyInput::key.a) {
                        movementComponent->speed.x = -movementComponent->acceleration;
                        if(animationComponent->animation->currentState != &RunLeft::getInstance()) {
                            animationComponent->animation->toggleAnimation(RunLeft::getInstance());
                        }
                    }
                    if(KeyInput::key.d) {
                        movementComponent->speed.x = movementComponent->acceleration;
                        if(animationComponent->animation->currentState != &RunRight::getInstance()) {
                            animationComponent->animation->toggleAnimation(RunRight::getInstance());
                        }
                    }
                    if(!KeyInput::key.a && !KeyInput::key.d) {
                        movementComponent->speed.x = 0.0f;
                        if(animationComponent->animation->currentState != &Idle::getInstance()) {
                            animationComponent->animation->toggleAnimation(Idle::getInstance());
                        }
                    }

                    positionComponent->position.x += movementComponent->speed.x;
                    positionComponent->position.y += movementComponent->speed.y;
                }
            }
        }
};

#endif
