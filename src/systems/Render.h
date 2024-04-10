#ifndef RENDER_H
#define RENDER_H

#include "../../utils/my_array.h"

#include "../EntityManager.h"
#include "../components/components.h"

class RenderSystem {
    public:
        RenderSystem() {}
        
        void update() {
            MyArray<EntityV2*> entities = EntityManager::getEntitiesByComponent<RenderComponent>(ComponentType::RENDER);

            for(int i = 0; i < entities.size(); ++i) {
                EntityV2* currentEntity = entities[i];
                RenderComponent* currentComponent = currentEntity->getComponent<RenderComponent>(ComponentType::RENDER);

                currentComponent->shader->use();

                currentEntity->setUniformMatrix4fv(currentComponent->shader, "projection", *currentComponent->projection);
                // currentEntity->setUniformMatrix4fv(currentComponent->shader, "view", *currentComponent->view);
                currentEntity->setUniformMatrix4fv(currentComponent->shader, "model", currentComponent->model);

                if(currentEntity->hasComponent<AnimationComponent>(ComponentType::ANIMATION)) {
                    AnimationComponent* animationComponent = currentEntity->getComponent<AnimationComponent>(ComponentType::ANIMATION);
                    currentEntity->setUniform1i(currentComponent->shader, "totalFrames", animationComponent->animation->currentState->totalFrames);
                    currentEntity->setUniform1i(currentComponent->shader, "currentFrame", animationComponent->animation->currentState->currentFrame);
                    glBindTexture(GL_TEXTURE_2D, animationComponent->animation->currentState->TBO);
                }
                else {
                    glBindTexture(GL_TEXTURE_2D, *currentComponent->TBO);
                }

                glBindVertexArray(currentComponent->VAO);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }
};

#endif
