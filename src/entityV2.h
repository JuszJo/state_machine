#ifndef ENTITYV2_H
#define ENTITYV2_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include "../libs/stb_image.h"

#include "../libs/shader.h"

// #include "../utils/my_array.h"

#include "components/components.h"

class EntityV2 {
    public:
        static const int MAX_SIZE = 100;
        BaseComponent* components[MAX_SIZE];

        glm::mat4 model = glm::mat4(1.0f);

        unsigned int VAO, VBO, EBO, TBO;

        bool active = false;

        // virtual void listen(KeyInput::Keys* keys) {};
        Shader* shader;

        EntityV2() {
            for(int i = 0; i < MAX_SIZE; ++i) {
                components[i] = (BaseComponent*)malloc(sizeof(BaseComponent));

                components[i]->type = ComponentType::NONE;
            }
        }

        template<typename T>
        T* addComponent(enum ComponentType type) {
            T* component = new T;

            component->base.type = type;
            
            components[type] = (BaseComponent*)component;

            return component;
        }

        template<typename T>
        T* getComponent(enum ComponentType type) {
            T* currentComponent = (T*)components[type];

            if(currentComponent) {
                return currentComponent;
            }

            return nullptr;
        }

        // // Remove a component from the entity
        // template<typename T>
        // void removeComponent() {
        //     components.remove_element_if([&](const auto& component) {
        //         return dynamic_cast<T*>(component.get()) != nullptr;
        //     });
        // }

        template<typename T>
        bool hasComponent(enum ComponentType type) {
            T* currentComponent = (T*)components[type];

            if(currentComponent->base.type == type) {
                return true;
            }

            return false;
        }

        virtual void update() {};

        virtual void render(glm::mat4 projection) {};

        void addShader(Shader* newShader) {
            shader = newShader;
        }

        virtual void resetModel() {
            model = glm::mat4(1.0f);
        }

        void setUniformVec3f(Shader* shader, const char* name, float val1, float val2, float val3) {
            int location = glGetUniformLocation(shader -> shaderProgram, name);
            glUniform3f(location, val1, val2, val3);
        }

        void setUniform1f(Shader* shader, const char* name, float value) {
            int location = glGetUniformLocation(shader -> shaderProgram, name);
            glUniform1f(location, value);
        }

        void setUniform1i(Shader* shader, const char* name, int value) {
            int location = glGetUniformLocation(shader -> shaderProgram, name);
            glUniform1f(location, value);
        }

        void setUniformMatrix4fv(Shader* shader, const char* name, glm::mat4 value) {
            int location = glGetUniformLocation(shader -> shaderProgram, name);
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        }

    protected:
        int stride;

        void genVertexandBuffers(unsigned int* VAO, unsigned int* VBO) {
            glGenVertexArrays(1, VAO);
            GLenum error;
            while ((error = glGetError()) != GL_NO_ERROR) {
                std::cerr << "OpenGL error: " << error << std::endl;
            }
            glGenBuffers(1, VBO);
        }

        void genElementBuffers(unsigned int* EBO) {
            glGenBuffers(1, EBO);
        }

        void bindVAO(unsigned int VAO) {
            glBindVertexArray(VAO);
        }

        void handleVertexBufferObject(unsigned int VBO, float* vertices, float size) {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }

        void handleElementBuffer(unsigned int EBO, unsigned int* indices, float size) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
        }

        void handleVertexArrayObject(int location, int nComponents, int stride, int offset) {
            glVertexAttribPointer(location, nComponents, GL_FLOAT, GL_FALSE, stride * sizeof(float), offset == 0 ? nullptr : (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(location);
        }

        void cleanupBuffers() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
};

#endif