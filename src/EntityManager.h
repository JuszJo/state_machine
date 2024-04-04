#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../utils/my_array.h"
#include "entityV2.h"

class EntityManager {
    public:
        static MyArray<EntityV2*> entity_list;

        EntityManager() {}

        static void addEntity(EntityV2* entity) {
            entity_list.add_element(entity);
        }

        static void removeInactive() {
            int elementsRemoved = 0;

            for(int i = 0; i < entity_list.size(); ++i) {
                if(entity_list[i]->active == false) {
                    entity_list.remove_element(i);
                    
                    --i;
                }
            }
        }

        // Function to get an entity by its component
        template<typename T>
        static EntityV2* getEntityByComponent() {
            for(int i = 0; i < entity_list.size(); ++i) {
                if(entity_list[i]->hasComponent<T>()) {
                    return entity_list[i];
                }
            }
            return nullptr;
        }
};

#endif