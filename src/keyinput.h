#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class KeyInput {
    public:
        struct Keys {
            bool w = false;
            bool a = false;
            bool s = false;
            bool d = false;
            bool f = false;
            bool i = false;
            bool j = false;
            bool k = false;
            bool l = false;
            bool m = false;
            bool n = false;
            bool o = false;
            bool p = false;
            bool t = false;
            bool space = false;
        };

        Keys key;

        KeyInput() {}

        void processInput(GLFWwindow* window) {
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) key.w = true;
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) key.w = false;

            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) key.s = true;
            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) key.s = false;

            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) key.a = true;
            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) key.a = false;

            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) key.d = true;
            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) key.d = false;

            if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) key.f = true;
            if(glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) key.f = false;

            if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) key.i = true;
            if(glfwGetKey(window, GLFW_KEY_I) == GLFW_RELEASE) key.i = false;

            if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) key.j = true;
            if(glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) key.j = false;

            if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) key.k = true;
            if(glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE) key.k = false;
            
            if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) key.l = true;
            if(glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) key.l = false;

            if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) key.m = true;
            if(glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) key.m = false;

            if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) key.n = true;
            if(glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE) key.n = false;

            if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) key.o = true;
            if(glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE) key.o = false;

            if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) key.p = true;
            if(glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) key.p = false;
            
            if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) key.t = true;
            if(glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) key.t = false;

            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) key.space = true;
            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) key.space = false;   
        }

};

#endif