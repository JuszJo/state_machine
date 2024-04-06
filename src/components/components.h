#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../../libs/shader.h"

#include "../animation/Animation.h"

enum ComponentType {
    POSITION,
    RENDER,
    MOVEMENT,
    ANIMATION,
    PLAYER,
    NONE
};

// BaseComponent struct
struct BaseComponent {
    int entityId;  // ID of the entity this component belongs to
    ComponentType type;
};

struct PlayerComponent {
    struct BaseComponent base;
};

struct PositionComponent {
    struct BaseComponent base;

    glm::vec3 position;
};

struct MovementComponent {
    struct BaseComponent base;

    glm::vec3 speed;

    float acceleration;
};

struct RenderComponent {
    struct BaseComponent base;

    Shader* shader;

    GLuint VAO;
    GLuint VBO;
    unsigned int* TBO;

    glm::mat4 model;

    glm::mat4* projection;
};

struct AnimationComponent {
    struct BaseComponent base;

    Animation* animation;
};

#endif