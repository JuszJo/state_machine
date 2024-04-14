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
                RenderComponent* renderComponent = currentEntity->getComponent<RenderComponent>(ComponentType::RENDER);

                if(currentEntity->hasComponent<PositionComponent>(ComponentType::POSITION)) {
                    PositionComponent* positionComponent = currentEntity->getComponent<PositionComponent>(ComponentType::POSITION);
                    renderComponent->model = glm::mat4(1.0f);
                    renderComponent->model = glm::translate(renderComponent->model, glm::vec3(positionComponent->position.x, positionComponent->position.y, 0.0f));
                }

                renderComponent->shader->use();

                currentEntity->setUniformMatrix4fv(renderComponent->shader, "projection", *renderComponent->projection);
                // currentEntity->setUniformMatrix4fv(renderComponent->shader, "view", *renderComponent->view);
                currentEntity->setUniformMatrix4fv(renderComponent->shader, "model", renderComponent->model);

                if(currentEntity->hasComponent<AnimationComponent>(ComponentType::ANIMATION)) {
                    AnimationComponent* animationComponent = currentEntity->getComponent<AnimationComponent>(ComponentType::ANIMATION);
                    currentEntity->setUniform1i(renderComponent->shader, "totalFrames", animationComponent->animation->currentState->totalFrames);
                    currentEntity->setUniform1i(renderComponent->shader, "currentFrame", animationComponent->animation->currentState->currentFrame);
                    glBindTexture(GL_TEXTURE_2D, animationComponent->animation->currentState->TBO);
                }
                else {
                    glBindTexture(GL_TEXTURE_2D, *renderComponent->TBO);
                }

                glBindVertexArray(renderComponent->VAO);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }
        }
};

#endif
