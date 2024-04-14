#ifndef UPDATE_H
#define UPDATE_H

#include <glm/glm.hpp>

#include "../../utils/my_array.h"

#include "../keyinput.h"

#include "../EntityManager.h"
#include "../components/components.h"

class UpdateSystem {
    public:
        UpdateSystem() {}
        
        void update() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<UpdateComponent>(ComponentType::UPDATE);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];

                currentEntity->update();
            }
        }
};

#endif
