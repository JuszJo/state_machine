#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>

// #include "../animation/Animation.h"
// #include "../animation/ConcreteAnimationStates.h"

// BaseComponent struct
struct BaseComponent {
    int entityId;  // ID of the entity this component belongs to
};


struct MovementComponent: public BaseComponent {
    glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f);

    float acceleration = 0.0f;
};

struct RenderComponent: public BaseComponent {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
};

// struct AnimationComponent: public BaseComponent {
//     Animation animation;
// };

#endif