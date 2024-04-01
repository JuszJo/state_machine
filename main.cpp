#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "libs/shader.h"

#include "src/player.h"

// struct Camera {
//     glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
//     glm::vec3 cameraFaceDirection = glm::vec3(0.0f, 0.0f, -1.0f);
//     glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//     float cameraSpeed = 2.0f;
// };

// Camera camera;

int display_w, display_h;

void processInput(GLFWwindow* window) {
}

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

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Player player("src\\assets\\player.png", 0.0f, 0.0f, 624.0f, 58.0f);

    glm::mat4 projection = glm::mat4(1.0f);
    // glm::mat4 view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFaceDirection, camera.cameraUp);

    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        player.keyInput.processInput(window);

        projection = glm::ortho(0.0f, (float)display_w, 0.0f, (float)display_h, -10.0f, 10.0f);
        // view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFaceDirection, camera.cameraUp);

        // player.render(&shader, projection, view);
        player.render(&shader, projection);
        // player.update();
        
        glfwSwapBuffers(window);
    }

    return 1;
}