#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>

#include "../../libs/shader.h"

#include "../animation/Animation.h"
#include "../animation/ConcreteAnimationStates.h"

enum ComponentType {
    RENDER,
    MOVEMENT,
    ANIMATION,
    NONE
};

// BaseComponent struct
struct BaseComponent {
    int entityId;  // ID of the entity this component belongs to
    ComponentType type = NONE;
};

struct MovementComponent {
    struct BaseComponent base;

    glm::vec3 speed;

    float acceleration;
};

struct RenderComponent {
    struct BaseComponent base;

    Shader* shader;

    unsigned int VAO, VBO, TBO;

    glm::mat4 model;

    glm::mat4* projection;

    glm::vec3 position;
};

struct AnimationComponent {
    struct BaseComponent base;
    
    Animation* animation;
};

#endif