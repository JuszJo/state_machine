#include <iostream>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../libs/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

#include "utils/image_loader.h"

#include "src/keyinput.h"

// #include "game.h"

#include "src/EntityManager.h"
#include "src/entityV2.h"
#include "src/player.h"
#include "src/box.h"
#include "src/components/components.h"

#include "src/systems/Update.h"
#include "src/systems/Render.h"
#include "src/systems/AnimationSystem.h"
#include "src/systems/Gravity.h"
#include "src/systems/Collision.h"

int display_w, display_h;

KeyInput::Keys KeyInput::key;

MyArray<EntityV2*> EntityManager::entity_list;

// TODO: Make Event Manager for events
// TODO: Add way to sub to events

GLFWwindow* initGLFW(int width, int height, const char* name) {
    if (!glfwInit()) return 0;

    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);

    if (!window) {
        glfwTerminate();

        return 0;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    return window;
}

int main() {
    GLFWwindow* window = initGLFW(800, 600, "State Machine");

    EntityV2* player = new Player("src/assets/playeridle.png");

    EntityManager::addEntity(player);

    Box* box = new Box();

    EntityManager::addEntity(box);

    // EntityV2* player2 = new EntityV2();

    // player2->addComponent<MovementComponent>();

    // player2->getComponent<MovementComponent>()->speed.x = 50.0f;

    // EntityManager::addEntity(player2);

    glm::mat4 projection;

    player->getComponent<RenderComponent>(ComponentType::RENDER)->projection = &projection;

    box->getComponent<RenderComponent>(ComponentType::RENDER)->projection = &projection;

    player->getComponent<PositionComponent>(ComponentType::POSITION)->position = glm::vec3(0.0f, 500.0f, 0.0f);

    UpdateSystem updateSystem;
    RenderSystem renderSystem;
    AnimationSystem animationSystem;
    GravitySystem gravitySystem;
    CollisionSystem collisionSystem;

    // EntityManager::entity_list.add_element()

    // Game game(&display_w, &display_h);

    // game.initEntities();

    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // // Set target FPS
    // constexpr int targetFPS = 60;
    // // Calculate frame duration
    // constexpr double frameDuration = 1.0 / targetFPS;

    while (!glfwWindowShouldClose(window)) {
        // // Get start time
        // double startTime = glfwGetTime();

        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        KeyInput::processInput(window);

        projection = glm::ortho(0.0f, (float)display_w, 0.0f, (float)display_h, -10.0f, 10.0f);

        animationSystem.update();
        updateSystem.update();
        gravitySystem.update();
        collisionSystem.checkWallCollision();
        collisionSystem.update();
        renderSystem.update();

        // // Get elapsed time
        // double endTime = glfwGetTime();
        // double elapsedTime = endTime - startTime;

        // // If frame was rendered faster than desired frame duration, sleep to limit FPS
        // if (elapsedTime < frameDuration) {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((frameDuration - elapsedTime) * 1000)));
        // }

        // game.run();
        
        glfwSwapBuffers(window);
    }

    return 1;
}