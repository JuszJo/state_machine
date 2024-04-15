#ifndef RENDER_H
#define RENDER_H

#include "../../utils/my_array.h"

#include "../EntityManager.h"
#include "../components/components.h"

class RenderSystem {
    public:
        Shader* hitboxShader = new Shader("shaders\\hitbox\\hitboxvertexShader.glsl", "shaders\\hitbox\\hitboxfragmentShader.glsl");

        RenderSystem() {}

        void legacyRenderHitbox(EntityV2* currentEntity) {
            HitboxComponent* hitboxComponent = currentEntity->getComponent<HitboxComponent>(ComponentType::HITBOX);

            float x = hitboxComponent->positionComponent->position.x + hitboxComponent->offsetX;
            float y = hitboxComponent->positionComponent->position.y + hitboxComponent->offsetY;
            float width = hitboxComponent->size.width;
            float height = hitboxComponent->size.height;

            float vertices[20] = {
                x, y, 0.0f,
                x + width, y, 0.0f,
                x, y + height, 0.0f,
                x + width, y + height, 0.0f
            };

            GLuint VAO, VBO;
            int stride = 3;
            int offset = 0;

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            int verticeSize = sizeof(vertices);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), offset == 0 ? nullptr : (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            RenderComponent* renderComponent = currentEntity->getComponent<RenderComponent>(ComponentType::RENDER);

            hitboxShader->use();

            int projectionLocation = glGetUniformLocation(hitboxShader->shaderProgram, "projection");
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(*renderComponent->projection));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
        
        void update() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<RenderComponent>(ComponentType::RENDER);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];

                if(currentEntity->hasComponent<HitboxComponent>(ComponentType::HITBOX)) {
                    legacyRenderHitbox(currentEntity);
                }

                currentEntity->render();
            }
        }
};

#endif
