#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "libs/stb_image.h"

#define STB_IMAGE_IMPLEMENTATION

#include "src/keyinput.h"

// #include "game.h"

#include "src/EntityManager.h"
#include "src/entityV2.h"
#include "src/components/components.h"

int display_w, display_h;

KeyInput::Keys KeyInput::key;

MyArray<EntityV2*> EntityManager::entity_list;

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

    EntityV2* entity = new EntityV2();

    entity->addComponent<MovementComponent>();

    // std::cout << entity->components[0];

    EntityV2* test = EntityManager::getEntityByComponent<MovementComponent>();

    std::cout << entity->components[0];

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

        // game.run();
        
        glfwSwapBuffers(window);
    }

    return 1;
}