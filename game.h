#pragma once

#include <glm/glm.hpp>

#include "utils/my_array.h"

// #include "src/EntityManager.h"
// #include "src/entityV2.h"

class Game {
    public:
        // MyArray<EntityV2*> EntityManager::entity_list;
        int* display_w;
        int *display_h;
        glm::mat4 projection;

        Game(int* display_w, int* display_h);

        void initEntities();
        void run();
};