#include <iostream>
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
#include "src/components/components.h"

#include "src/systems/Movement.h"
#include "src/systems/Render.h"
#include "src/systems/AnimationSystem.h"

int display_w, display_h;

KeyInput::Keys KeyInput::key;

MyArray<EntityV2*> EntityManager::entity_list;

// TODO: Make state machine for both movement and animations

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

    // player->addComponent<MovementComponent>();

    EntityManager::addEntity(player);

    // EntityV2* player2 = new EntityV2();

    // player2->addComponent<MovementComponent>();

    // player2->getComponent<MovementComponent>()->speed.x = 50.0f;

    // EntityManager::addEntity(player2);

    MyArray<MovementComponent*> movementComponents = EntityManager::getComponentsByEntity<MovementComponent>(ComponentType::MOVEMENT);

    glm::mat4 projection;

    player->getComponent<RenderComponent>(ComponentType::RENDER)->projection = &projection;

    // std::cout << movementComponents[0]->speed.x << "\n";
    // std::cout << movementComponents[1]->speed.x << "\n";

    // std::cout << entity->components[0];

    // MovementComponent* test = EntityManager::getComponentByEntity<MovementComponent>();

    // MovementSystem movementSystem;

    RenderSystem renderSystem;
    AnimationSystem animationSystem;

    // if(test != nullptr) {
    //     std::cout << test->speed.x;
    // }


    // std::cout << entity->components[0];

    // EntityManager::entity_list.add_element()

    // Game game(&display_w, &display_h);

    // game.initEntities();

    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        KeyInput::processInput(window);

        projection = glm::ortho(0.0f, (float)display_w, 0.0f, (float)display_h, -10.0f, 10.0f);

        renderSystem.update();
        animationSystem.update();

        // movementSystem.update();

        // std::cout << entity->getComponent<MovementComponent>()->speed.x;

        // game.run();
        
        glfwSwapBuffers(window);
    }

    return 1;
}