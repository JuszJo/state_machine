#pragma once

#include "../../utils/my_array.h"

#include "../EntityManager.h"
#include "../event/EventManager.h"
#include "../components/components.h"

class CollisionSystem {
    public:
        CollisionSystem() {}

        bool didCollide(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
            if(
                x1 + w1 > x2 &&
                x1 < x2 + w2 &&
                y1 + h1 > y2 &&
                y1 < y2 + h2
            ) {
                return true;
            }
            else {
                return false;
            }
        }

        void update() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<CollisionComponent>(ComponentType::COLLISION);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];
                for(int j = 0; j < entities.size(); ++j) {
                    EntityV2* nextEntity = entities[j];

                    if(currentEntity == nextEntity) continue;

                    if(
                        currentEntity->hasComponent<SizeComponent>(ComponentType::SIZE) &&
                        currentEntity->hasComponent<PositionComponent>(ComponentType::POSITION) &&
                        nextEntity->hasComponent<SizeComponent>(ComponentType::SIZE) &&
                        nextEntity->hasComponent<PositionComponent>(ComponentType::POSITION)
                    ) {
                        SizeComponent* sizeComponent1 = currentEntity->getComponent<SizeComponent>(ComponentType::SIZE);
                        PositionComponent* positionComponent1 = currentEntity->getComponent<PositionComponent>(ComponentType::POSITION);
                        SizeComponent* sizeComponent2 = nextEntity->getComponent<SizeComponent>(ComponentType::SIZE);
                        PositionComponent* positionComponent2 = nextEntity->getComponent<PositionComponent>(ComponentType::POSITION);

                        float x1 = positionComponent1->position.x;
                        float y1 = positionComponent1->position.y;
                        float w1 = sizeComponent1->width;
                        float h1 = sizeComponent1->height;

                        float x2 = positionComponent2->position.x;
                        float y2 = positionComponent2->position.y;
                        float w2 = sizeComponent2->width;
                        float h2 = sizeComponent2->height;

                        bool collisionOccured = this->didCollide(x1, y1, w1, h1, x2, y2, w2, h2);
                    }
                }
            }
        }

        void checkWallCollision() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<CollisionComponent>(ComponentType::COLLISION);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];

                if(
                    currentEntity->hasComponent<SizeComponent>(ComponentType::SIZE) &&
                    currentEntity->hasComponent<PositionComponent>(ComponentType::POSITION) &&
                    currentEntity->hasComponent<MovementComponent>(ComponentType::MOVEMENT) &&
                    currentEntity->hasComponent<HitboxComponent>(ComponentType::HITBOX)
                ) {
                    SizeComponent* sizeComponent = currentEntity->getComponent<SizeComponent>(ComponentType::SIZE);
                    PositionComponent* positionComponent = currentEntity->getComponent<PositionComponent>(ComponentType::POSITION);
                    MovementComponent* movementComponent = currentEntity->getComponent<MovementComponent>(ComponentType::MOVEMENT);
                    HitboxComponent* hitboxComponent = currentEntity->getComponent<HitboxComponent>(ComponentType::HITBOX);

                    // float x = positionComponent->position.x;
                    // float y = positionComponent->position.y;
                    // float width = sizeComponent->width;
                    // float height = sizeComponent->height;

                    float x = hitboxComponent->positionComponent->position.x + hitboxComponent->offsetX;
                    float y = hitboxComponent->positionComponent->position.y + hitboxComponent->offsetY;
                    float width = hitboxComponent->size.width;
                    float height = hitboxComponent->size.height;

                    if(x < 0.0f) {
                        positionComponent->position.x = 0.0f - hitboxComponent->offsetX;
                        movementComponent->speed.x = 0.0f;
                    }
                    if(x + width > 800.0f) {
                        positionComponent->position.x = 800.0f - hitboxComponent->offsetX - width;
                        movementComponent->speed.x = 0.0f;
                    }
                    if(y < 0.0f) {
                        Event* event = new Event(GameEvents::PLAYER_GROUND_COLLISION);
                        EventManager::addEvent(*event);

                        delete event;

                        positionComponent->position.y = 0.0f - hitboxComponent->offsetY;
                        movementComponent->speed.y = 0.0f;

                        if(currentEntity->hasComponent<JumpComponent>(ComponentType::JUMP)) {
                            JumpComponent* jumpComponent = currentEntity->getComponent<JumpComponent>(ComponentType::JUMP);

                            jumpComponent->canJump = true;
                        }
                    }
                    if(y + height > 600.0f) {
                        positionComponent->position.y = 600.0f - hitboxComponent->offsetY - height;
                        movementComponent->speed.y = 0.0f;
                    }
                }
            
            }
        }
};