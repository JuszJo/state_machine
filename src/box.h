#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../libs/shader.h"

#include "entityV2.h"

#include "components/components.h"

class Box: public EntityV2 {
    private:
        int stride = 3;

    public:
        Box(): EntityV2() {
            SizeComponent* sizeComponent = this->addComponent<SizeComponent>(ComponentType::SIZE);
            sizeComponent->width = 100.0f;
            sizeComponent->height = 100.0f;

            PositionComponent* positionComponent = this->addComponent<PositionComponent>(ComponentType::POSITION);
            positionComponent->position = glm::vec3(0.0f, 0.0f, 0.0f);

            RenderComponent* renderComponent = this->addComponent<RenderComponent>(ComponentType::RENDER);
            renderComponent->shader = new Shader("shaders\\hitbox\\hitboxvertexShader.glsl", "shaders\\hitbox\\hitboxfragmentShader.glsl");
            renderComponent->model = glm::mat4(1.0f);

            float x = positionComponent->position.x;
            float y = positionComponent->position.y;
            float width = sizeComponent->width;
            float height = sizeComponent->height;

            float vertices[20] = {
                x, y, 0.0f,
                x + width, y, 0.0f,
                x, y + height, 0.0f,
                x + width, y + height, 0.0f
            };
            
            int stride = 3;
            int offset = 0;

            glGenVertexArrays(1, &renderComponent->VAO);
            glGenBuffers(1, &renderComponent->VBO);

            glBindVertexArray(renderComponent->VAO);

            int verticeSize = sizeof(vertices);
            glBindBuffer(GL_ARRAY_BUFFER, renderComponent->VBO);
            glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), offset == 0 ? nullptr : (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void render() {
            RenderComponent* renderComponent = this->getComponent<RenderComponent>(ComponentType::RENDER);

            if(this->hasComponent<PositionComponent>(ComponentType::POSITION)) {
                PositionComponent* positionComponent = this->getComponent<PositionComponent>(ComponentType::POSITION);
                renderComponent->model = glm::mat4(1.0f);
                renderComponent->model = glm::translate(renderComponent->model, glm::vec3(positionComponent->position.x, positionComponent->position.y, 0.0f));
            }

            renderComponent->shader->use();

            int projectionLocation = glGetUniformLocation(renderComponent->shader->shaderProgram, "projection");
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(*renderComponent->projection));

            glBindVertexArray(renderComponent->VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
};