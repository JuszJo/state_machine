#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/my_array.h"
#include "src/entityV2.h"

#include "src/keyinput.h"
#include "src/Animation.h"
#include "src/AnimationState.h"
#include "src/ConcreteAnimationStates.h"

class Game {
    public:
        MyArray<EntityV2*> entities;
        int* display_w;
        int *display_h;
        glm::mat4 projection;
        KeyInput keyInput;

        Animation animation;

        Game(int* display_w, int* display_h);

        void initEntities();
        void run();
};