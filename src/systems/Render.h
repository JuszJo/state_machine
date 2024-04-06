#ifndef Render_H
#define Render_H

#include "../../utils/my_array.h"

#include "../EntityManager.h"
#include "../components/components.h"

class RenderSystem {
    public:
        RenderSystem() {}
        
        void update() {
            // RenderComponent* renderComponent = EntityManager::getComponentsByEntity<RenderComponent>();
            MyArray<RenderComponent*> renderComponents = EntityManager::getComponentsByEntity<RenderComponent>(ComponentType::RENDER);

            for(int i = 0; i < renderComponents.size(); ++i) {
                RenderComponent* currentComponent = renderComponents[i];
                currentComponent->shader->use();
                glUniformMatrix4fv(glGetUniformLocation(currentComponent->shader->shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(*currentComponent->projection));
                // glUniformMatrix4fv(glGetUniformLocation(currentComponent->shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(currentComponent->shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(currentComponent->model));
                glBindTexture(GL_TEXTURE_2D, currentComponent->TBO);
                glBindVertexArray(currentComponent->VAO);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }
};

#endif
