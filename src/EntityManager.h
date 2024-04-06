#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../utils/my_array.h"
#include "entityV2.h"
#include "components/components.h"

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

        template<typename T>
        static MyArray<T*> getComponentsByEntity(enum ComponentType type) {
            MyArray<T*> components;

            for(int i = 0; i < entity_list.size(); ++i) {
                EntityV2* currentEntity = entity_list[i];

                if(currentEntity->hasComponent<T>(type)) {
                    T* entityComponent = currentEntity->getComponent<T>(type);

                    if(entityComponent != nullptr) {
                        components.add_element(entityComponent);
                    }
                }
            }
            return components;
        }

        template<typename T>
        static MyArray<EntityV2*> getEntitiesByComponent(enum ComponentType type) {
            MyArray<EntityV2*> entities;

            for(int i = 0; i < entity_list.size(); ++i) {
                EntityV2* currentEntity = entity_list[i];

                if(currentEntity->hasComponent<T>(type)) {
                    entities.add_element(currentEntity);
                }
            }
            return entities;
        }
};

#endif