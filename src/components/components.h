#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../../libs/shader.h"

#include "../animation/Animation.h"

enum ComponentType {
    POSITION,
    SIZE,
    UPDATE,
    RENDER,
    MOVEMENT,
    JUMP,
    ANIMATION,
    PLAYER,
    GRAVITY,
    COLLISION,
    HITBOX,
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

struct SizeComponent {
    struct BaseComponent base;

    float width, height;
};

struct HitboxComponent {
    struct BaseComponent base;
    struct SizeComponent size;

    struct PositionComponent* positionComponent;

    float offsetX;
    float offsetY;
};

struct MovementComponent {
    struct BaseComponent base;

    glm::vec3 speed;

    float acceleration;
};

struct JumpComponent {
    struct BaseComponent base;

    float jumpForce;
    bool canJump;
};

struct UpdateComponent {
    struct BaseComponent base;
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

struct GravityComponent {
    struct BaseComponent base;

    glm::vec3 gForce;
};

struct CollisionComponent {
    struct BaseComponent base;
};

#endif