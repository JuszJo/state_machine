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

int main() {
    if (!glfwInit()) return 1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "State Machine", NULL, NULL);

    if (!window) {
        glfwTerminate();

        return 1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Player player("src\\assets\\player.png", 0.0f, 0.0f, 30.0f, 30.0f);

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