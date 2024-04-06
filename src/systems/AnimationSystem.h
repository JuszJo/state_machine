#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "../../utils/my_array.h"

#include "../EntityManager.h"
// #include "../keyinput.h"
#include "../components/components.h"

// #include "../animation/Animation.h"
// #include "../animation/ConcreteAnimationStates.h"

class AnimationSystem {
    public:
        AnimationSystem() {}
        
        void update() {
            
            // MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<AnimationComponent>(ComponentType::ANIMATION);
            MyArray<AnimationComponent*> components = EntityManager::getComponentsByEntity<AnimationComponent>(ComponentType::ANIMATION);

            for(int i = 0; i < components.size(); ++i) {
                AnimationComponent* animationComponent = components[i];

                animationComponent->animation->animate();
            }
        }
};

#endif
