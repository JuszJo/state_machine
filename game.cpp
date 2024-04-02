#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game.h"

#include "libs/shader.h"

#include "src/player.h"

Game::Game(int* display_w, int* display_h) {
    this->display_w = display_w;
    this->display_h = display_h;
}

void Game::initEntities() {
    Shader* shader = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Player* player = new Player("src\\assets\\player.png", 0.0f, 0.0f, 624.0f, 58.0f);

    player->addShader(shader);

    this->entities.add_element(player);

    glm::mat4 projection = glm::mat4(1.0f);
}

void Game::run() {
    this->projection = glm::ortho(0.0f, (float)*this->display_w, 0.0f, (float)*this->display_h, -10.0f, 10.0f);

    for(int i = 0; i < this->entities.size(); ++i) {
        EntityV2* currentEntity = this->entities[i];

        currentEntity->render(projection);
        currentEntity->update();
    }
}