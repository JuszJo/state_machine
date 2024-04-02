#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "game.h"

int display_w, display_h;

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

    Game game(&display_w, &display_h);

    game.initEntities();

    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.keyInput.processInput(window);

        game.run();
        
        glfwSwapBuffers(window);
    }

    return 1;
}