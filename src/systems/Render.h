#ifndef RENDER_H
#define RENDER_H

#include "../../utils/my_array.h"

#include "../EntityManager.h"
#include "../components/components.h"

class RenderSystem {
    public:
        RenderSystem() {}
        
        void update() {
            // RenderComponent* renderComponent = EntityManager::getComponentsByEntity<RenderComponent>();
            // MyArray<RenderComponent*> renderComponents = EntityManager::getComponentsByEntity<RenderComponent>(ComponentType::RENDER);
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<RenderComponent>(ComponentType::RENDER);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];
                RenderComponent* currentComponent = currentEntity->getComponent<RenderComponent>(ComponentType::RENDER);

                // RenderComponent* currentComponent = entities[i];
                currentComponent->shader->use();
                glUniformMatrix4fv(glGetUniformLocation(currentComponent->shader->shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(*currentComponent->projection));
                // glUniformMatrix4fv(glGetUniformLocation(currentComponent->shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(currentComponent->shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(currentComponent->model));
                if(currentEntity->hasComponent<AnimationComponent>(ComponentType::ANIMATION)) {
                    AnimationComponent* animationComponent = currentEntity->getComponent<AnimationComponent>(ComponentType::ANIMATION);
                    currentEntity->setUniform1i(currentComponent->shader, "totalFrames", animationComponent->animation->currentState->totalFrames);
                    currentEntity->setUniform1i(currentComponent->shader, "currentFrame", animationComponent->animation->currentState->currentFrame);
                }
                glBindTexture(GL_TEXTURE_2D, *currentComponent->TBO);
                glBindVertexArray(currentComponent->VAO);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }
};

#endif
