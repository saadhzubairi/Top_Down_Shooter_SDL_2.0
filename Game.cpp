#include <vector>
#include <stdio.h>
#include "Game.h"
#include "GameObject.h"
#include "HelperClasses/Map.h"
#include "PlayerShip.h"
#include "Enemies/Ranger.h"
#include "Bullets/PlayerBullet.h"
#include "Bullets/EnemyBullet.h"
#include "Enemies/Nimble.h"
#include "Bullets/NimbleMissile.h"

SDL_Renderer *Game::renderer = nullptr;

std::vector<PlayerBullet *> Game::playerBullets;
std::vector<PlayerBullet *> Game::playerMissile;
std::vector<EnemyBullet *> Game::enemyBullets;
int Game::missileCount = 10;
int Game::cnt = 0;
PlayerShip *player;
Ranger *ranger;
Nimble *nimble;

int Game::height = 0;
int Game::width = 0;

Map *map;
SDL_Event Game::event;

Game::Game() {
    height = 0;
    width = 0;
    cnt = 0;
}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int heigh, bool fullscreen) {
    this->height = heigh;
    this->width = width;

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "[+] SDL initialized!" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, heigh, flags);
        if (window) {
            std::cout << "[+] Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "[+] Renderer Created!" << std::endl;
        }

        isRunning = true;
    } else { isRunning = false; }

    player = new PlayerShip("../Assets/SHIPS.png", width / 2 - 66, heigh - 154, 256, 3);
    ranger = new Ranger("../Assets/Ranger.png", 200, 50, 256, 3);
    nimble = new Nimble("../Assets/Nimble.png", 600, 50, 256, 3);
    map = new Map();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        isRunning = false;
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                player->Translate(7, 0);
                break;
            case SDLK_LEFT:
                player->Translate(-7, 0);
                break;
            case SDLK_UP:
                player->Translate(0, -5);
                break;
            case SDLK_DOWN:
                player->Translate(0, 5);
                break;
            case SDLK_SPACE:
                addPlayerBullet();
                break;
            case SDLK_b:
                addPlayerMissile();
                break;
            default:
                break;
        }
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();

    if (player->isAlive()) player->Render();
    if (ranger->isAlive()) ranger->Render();
    if (nimble->isAlive()) nimble->Render();

    for (PlayerBullet *playerBullet: Game::playerBullets) {
        playerBullet->Render();
    }
    for (PlayerBullet *playerBullet: Game::playerMissile) {
        playerBullet->Render();
    }
    for (EnemyBullet *enemyBullet: Game::enemyBullets) {
        enemyBullet->Render();
    }
    //Add stuff to render:
    SDL_RenderPresent(renderer);
    if (player->hit) {
        if (cnt == 120) {
            clean();
        }
    }
}

void Game::update() {
    if (player->isAlive()) {
        player->Update();
        player->Move();
    }

    if (ranger->isAlive()) {
        ranger->Update();
        ranger->Move();
    }

    if (nimble->isAlive()) {
        nimble->Update();
        nimble->Move();
    }

    for (PlayerBullet *playerBullet: Game::playerBullets) {
        playerBullet->Update();
        playerBullet->Move();
    }

    for (PlayerBullet *playerMissile: Game::playerMissile) {
        playerMissile->Update();
        playerMissile->Move();
    }

    for (EnemyBullet *enemyBullet: Game::enemyBullets) {
        enemyBullet->Update();
        enemyBullet->Move();
    }
    addEnemyBullet();
    addNimbleBullet();
    cnt++;
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "[+] Game Cleaned!" << std::endl;
}

bool Game::running() { return this->isRunning; }

void Game::deleteDeadStuff() {
    for (int i = 0; i < Game::playerBullets.size(); ++i) {
        if (!Game::playerBullets.at(i)->isAlive()) {
            Game::playerBullets.erase(Game::playerBullets.begin() + i);
        }
    }

    for (int i = 0; i < Game::playerMissile.size(); ++i) {
        if (!Game::playerMissile.at(i)->isAlive()) {
            Game::playerMissile.erase(Game::playerMissile.begin() + i);
        }
    }

    for (int i = 0; i < Game::enemyBullets.size(); ++i) {
        if (!Game::enemyBullets.at(i)->isAlive()) {
            Game::enemyBullets.erase(Game::enemyBullets.begin() + i);
        }
    }
}

void Game::checkCollisions() {

    for (PlayerBullet *playerBullet: Game::playerBullets) {
        if (playerBullet->yPos >= (ranger->yPos) && playerBullet->yPos <= (ranger->yPos + 50)) {
            if (playerBullet->xPos >= (ranger->xPos - 64) && playerBullet->xPos <= (ranger->xPos + 64)) {
                ranger->TakeHit();
                playerBullet->Destroy();
            }
        }

        if (playerBullet->yPos >= (nimble->yPos) && playerBullet->yPos <= (nimble->yPos + 50)) {
            if (playerBullet->xPos >= (nimble->xPos - 64) && playerBullet->xPos <= (nimble->xPos + 64)) {
                nimble->TakeHit();
                playerBullet->Destroy();
            }
        }

        if (playerBullet->yPos >= (nimble->yPos) && playerBullet->yPos <= (nimble->yPos + 150)) {
            if (playerBullet->xPos >= (nimble->xPos - 64) && playerBullet->xPos <= (nimble->xPos)) {
                nimble->Translate(3, 0);
            } else if (playerBullet->xPos >= (nimble->xPos) && playerBullet->xPos <= (nimble->xPos + 64)) {
                nimble->Translate(-3, 0);
            }
        }
    }

    for (PlayerBullet *playerMissile: Game::playerMissile) {
        if (playerMissile->yPos >= (ranger->yPos) && playerMissile->yPos <= (ranger->yPos + 50)) {
            if (playerMissile->xPos >= (ranger->xPos - 64) && playerMissile->xPos <= (ranger->xPos + 64)) {
                ranger->TakeHit();
                playerMissile->Destroy();
            }
        }

        if (playerMissile->yPos >= (nimble->yPos) && playerMissile->yPos <= (nimble->yPos + 50)) {
            if (playerMissile->xPos >= (nimble->xPos - 32) && playerMissile->xPos <= (nimble->xPos + 32)) {
                nimble->TakeHit();
                playerMissile->Destroy();
            }
        }

        //NIMBLE DODGE
        if (playerMissile->yPos >= (nimble->yPos) && playerMissile->yPos <= (nimble->yPos + 150)) {
            if (playerMissile->xPos >= (nimble->xPos - 64) && playerMissile->xPos <= (nimble->xPos)) {
                nimble->Translate(200, 0);
            } else if (playerMissile->xPos >= (nimble->xPos) && playerMissile->xPos <= (nimble->xPos + 64)) {
                nimble->Translate(-200, 0);
            }
        }
    }

    for (EnemyBullet *enemyBullet: Game::enemyBullets) {
        if (enemyBullet->yPos >= player->yPos - 64 && enemyBullet->yPos <= player->yPos) {
            if (enemyBullet->xPos >= player->xPos - 64 && enemyBullet->xPos <= player->xPos + 64) {
                if (!player->hit) {
                    enemyBullet->Destroy();
                    player = new PlayerShip("../Assets/Explosion.png", player->xPos, player->yPos, 256, 3);
                    player->TakeHit();
                    cnt = 0;
                }
            }
        }
    }

}

void Game::respawnEnemies() {
    if (!ranger->isAlive()) {
        int x = rand() % 9;
        ranger = new Ranger("../Assets/Ranger.png", x * 100, 50, 256, 3);
    }
    if (!nimble->isAlive()) {
        int x = rand() % 9;
        nimble = new Nimble("../Assets/Nimble.png", x * 100, 50, 256, 3);
    }
}

void Game::addEnemyBullet() {
    int x = rand() % 200;
    if (x > 188) {
        if (ranger->xPos >= player->xPos - 64 && ranger->xPos <= player->xPos + 64) {
            EnemyBullet *enemyBullet = new EnemyBullet("../Assets/Bullets_enemy.png",
                                                       ranger->xPos,ranger->yPos,
                                                       256,3);
            Game::enemyBullets.push_back(enemyBullet);
        }
    }
}

void Game::addNimbleBullet() {
    int x = rand() % 200;
    if (x > 188) {
        NimbleMissile *enemyBullet = new NimbleMissile(player->xPos, player->yPos,
                                                     "../Assets/Bullets_enemy.png",
                                                     nimble->xPos, nimble->yPos, 256,
                                                     3);
        Game::enemyBullets.push_back(reinterpret_cast<EnemyBullet *const>(enemyBullet));

    }
}

void Game::addPlayerMissile() {
    if (player->hit == false) {

        if (missileCount > 0) {
            PlayerBullet *missile = new PlayerBullet("../Assets/Missiles_ship.png", player->xPos, player->yPos, 256, 3);
            Game::playerMissile.push_back(missile);
            missileCount--;
            if (missileCount == 0) {
                cnt = 0;
            }
        } else if (cnt > 120) {
            printf("%d\n", cnt);
            PlayerBullet *missile = new PlayerBullet("../Assets/Missiles_ship.png", player->xPos, player->yPos, 256, 3);
            Game::playerMissile.push_back(missile);
            cnt = 0;
        }
    }
}

void Game::addPlayerBullet() {
    if (player->hit == false) {
        PlayerBullet *playerBullet = new PlayerBullet("../Assets/Bullets_ship.png", player->xPos, player->yPos, 256, 3);
        Game::playerBullets.push_back(playerBullet);
    }
}