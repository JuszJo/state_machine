#ifndef RENDER_H
#define RENDER_H

#include "../../utils/my_array.h"

#include "../EntityManager.h"
#include "../components/components.h"

class RenderSystem {
    public:
        RenderSystem() {}
        
        void update() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<RenderComponent>(ComponentType::RENDER);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];

                currentEntity->render();
            }
        }
};

#endif
