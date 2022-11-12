#include <vector>
#include <cstdio>
#include "Game.h"
#include "GameObject.h"
#include "HelperClasses/Map.h"
#include "PlayerShip.h"
#include "Enemies/Ranger.h"
#include "Bullets/DefaultBullet.h"
#include "Bullets/EnemyBullet.h"
#include "Enemies/Nimble.h"
#include "Bullets/NimbleBullet.h"
#include "Bullets/PlayerBullet.h"
#include "Bullets/PlayerMissile.h"
#include "UIElementsForGame/Counters.h"
#include "UIElementsForGame/UIButtons.h"


SDL_Renderer *Game::renderer = nullptr;

std::vector<DefaultBullet *>    Game::playerBullets;
std::vector<DefaultBullet *>    Game::playerMissile;
std::vector<EnemyBullet *>    Game::enemyBullets;
std::vector<UILabel *> labels;


int Game::missileCount = 10;
int Game::cnt = 0;
PlayerShip *player;
Ranger *ranger;
Nimble *nimble;

UIButtons *startGameButton;
UIButtons *quitGameButton;

int Game::height = 0;
int Game::width = 0;

Map *map;
SDL_Event Game::event;

Game::Game() {
    height = 0;
    width = 0;
    cnt = 0;
}

Game::~Game() = default;

void Game::init(const char *title, int xpos, int ypos, int w, int heigh, bool fullscreen) {
    Game::height = heigh;
    Game::width = w;
    this->playStart = false;
    this->isRunning = true;
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "[+] SDL initialized!" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, w, heigh, flags);
        if (window) {
            std::cout << "[+] Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "[+] Renderer Created!" << std::endl;
        }

        if (TTF_Init() == -1) {
        } else {
            std::cout << "[+] SDL_ttf initialized!" << std::endl;
        }

        isRunning = true;
    } else { isRunning = false; }

    startGameButton = new UIButtons("START", 500, 350, 105);
    quitGameButton = new UIButtons("QUIT", 500, 475, 55);

    map = new Map();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        isRunning = false;
    } else if (event.type == SDL_KEYDOWN && playStart) {
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
    } else if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(!playStart){
            bool startPressed = startGameButton->HandleButtonClickEventsFromMouse(x, y);
            if (startPressed) startGame();

            bool quitPressed = quitGameButton->HandleButtonClickEventsFromMouse(x, y);
            if (quitPressed) isRunning = false;
        }
    }
}

bool Game::quitGame(){
    return !isRunning;
}


void Game::startGame() {
    player = new PlayerShip(width / 2 - 66, height - 154);
    ranger = new Ranger(200, 50);
    nimble = new Nimble(600, 50);

    labels.push_back(new UILabel("Rangers Killed: ", 100, 30, 20));
    labels.push_back(new UILabel("Nimbles Killed: ", 300, 30, 20));
    labels.push_back(new UILabel("Rockets Left: ", 850, 30, 24));
    labels.push_back(new UILabel("0", 200, 30, 20));
    labels.push_back(new UILabel("0", 400, 30, 20));
    labels.push_back(new UILabel("0", 940, 30, 24));

    playStart = true;
}


void Game::render() {

    SDL_RenderClear(renderer);
    map->drawMap();

    if (playStart) {

        for (DefaultBullet *playerBullet: Game::playerBullets) {
            playerBullet->Render();
        }
        for (DefaultBullet *playerBullet: Game::playerMissile) {
            playerBullet->Render();
        }
        for (EnemyBullet *enemyBullet: Game::enemyBullets) {
            enemyBullet->Render();
        }

        if (player->isAlive()) player->Render();
        if (ranger->isAlive()) ranger->Render();
        if (nimble->isAlive()) nimble->Render();

        for (UILabel *label: labels) {
            label->Render();
        }
    }
    else{
        startGameButton->Render();
        quitGameButton->Render();
    }
    //Add stuff to render:
    SDL_RenderPresent(Game::renderer);
}

void Game::update() {
    if (playStart) {
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

        for (DefaultBullet *playerBullet: Game::playerBullets) {
            playerBullet->Update();
            playerBullet->Move();
        }

        for (DefaultBullet *playerMissile: Game::playerMissile) {
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
        if (player->hit) {
            if (cnt == 120) {
                playStart = false;
                startGameButton->SetText("TRY AGAIN");
            }
        }

        if (missileCount == 0) {
            if (cnt > 120)
                Counters::rockets_left = 1;
        }

        std::string m = std::to_string(Counters::ranger_kills);
        labels[3]->SetText(m);
        m = std::to_string(Counters::nimble_kills);
        labels[4]->SetText(m);
        m = std::to_string(Counters::rockets_left);
        labels[5]->SetText(m);
    }
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

    //IF BULLET HITS RANGER OR NIMBLE:
    for (DefaultBullet *playerBullet: Game::playerBullets) {
        //RANGER
        if (playerBullet->yPos >= (ranger->yPos) && playerBullet->yPos <= (ranger->yPos + 50)) {
            if (playerBullet->xPos >= (ranger->xPos - 64) && playerBullet->xPos <= (ranger->xPos + 64)) {
                ranger->TakeHit();
                playerBullet->Destroy();
            }
        }

        //NIMBLE
        if (playerBullet->yPos >= (nimble->yPos) && playerBullet->yPos <= (nimble->yPos + 50)) {
            if (playerBullet->xPos >= (nimble->xPos - 32) && playerBullet->xPos <= (nimble->xPos + 32)) {
                nimble->TakeHit();
                playerBullet->Destroy();
            }
        }

        //NIMBLE DODGE
        if (playerBullet->yPos >= (nimble->yPos) && playerBullet->yPos <= (nimble->yPos + 150)) {
            if (playerBullet->xPos >= (nimble->xPos - 64) && playerBullet->xPos <= (nimble->xPos)) {
                nimble->Translate(10, 0);
            } else if (playerBullet->xPos >= (nimble->xPos) && playerBullet->xPos <= (nimble->xPos + 64)) {
                nimble->Translate(-10, 0);
            }
        }
    }

    //IF MISSILE HITS RANGER OR NIMBLE:
    for (DefaultBullet *playerMissile: Game::playerMissile) {
        if (playerMissile->yPos >= (ranger->yPos) && playerMissile->yPos <= (ranger->yPos + 50)) {
            if (playerMissile->xPos >= (ranger->xPos - 64) && playerMissile->xPos <= (ranger->xPos + 64)) {
                ranger->TakeHit();
                playerMissile->Destroy();
            }
        }

        if (playerMissile->yPos >= (nimble->yPos) && playerMissile->yPos <= (nimble->yPos + 50)) {
            if (playerMissile->xPos >= (nimble->xPos - 64) && playerMissile->xPos <= (nimble->xPos + 64)) {
                nimble->TakeHit();
                playerMissile->Destroy();
            }
        }

        //NIMBLE DODGE
        if (playerMissile->yPos >= (nimble->yPos) && playerMissile->yPos <= (nimble->yPos + 256)) {
            if (playerMissile->xPos >= (nimble->xPos - 128) && playerMissile->xPos <= (nimble->xPos)) {
                nimble->Translate(1, -3);
            } else if (playerMissile->xPos >= (nimble->xPos) && playerMissile->xPos <= (nimble->xPos + 128)) {
                nimble->Translate(-1, -3);
            }
        }
    }

    //IF BULLET HITS PLAYER
    for (EnemyBullet *enemyBullet: Game::enemyBullets) {
        if (enemyBullet->yPos >= player->yPos - 64 && enemyBullet->yPos <= player->yPos) {
            if (enemyBullet->xPos >= player->xPos - 64 && enemyBullet->xPos <= player->xPos + 64) {
                if (!player->hit) {
                    enemyBullet->Destroy();
                    player->setObjTexture("../Assets/Explosion.png", 256, 3);
                    player->TakeHit();
                    cnt = 0;
                }
            }
        }
    }

}

void Game::respawnEnemies() {
    if (playStart) {
        if (!ranger->isAlive()) {
            if (ranger->life == 0)
                Counters::ranger_kills++;
            int x = rand() % 9;
            ranger = new Ranger(x * 100, -128);
        }
        if (!nimble->isAlive()) {
            if (nimble->life == 0)

                Counters::nimble_kills++;
            int x = rand() % 9;
            nimble = new Nimble(x * 100, -128);
        }
    }
}

void Game::addEnemyBullet() {
    int x = rand() % 200;
    if (x > 195) {
        if (ranger->xPos >= player->xPos - 64 && ranger->xPos <= player->xPos + 64) {
            EnemyBullet *enemyBullet = new EnemyBullet(
                    ranger->xPos, ranger->yPos);
            Game::enemyBullets.push_back(enemyBullet);
        }
    }
}

void Game::addNimbleBullet() {
    int x = rand() % 200;
    if (x > 195) {
        NimbleBullet *enemyBullet = new NimbleBullet(player->xPos, player->yPos, nimble->xPos, nimble->yPos);
        Game::enemyBullets.push_back(reinterpret_cast<EnemyBullet *const>(enemyBullet));
    }
}

void Game::addPlayerMissile() {
    if (player->hit == false) {
        if (missileCount > 0) {
            auto *missile = new PlayerMissile(player->xPos, player->yPos);
            Game::playerMissile.push_back(missile);
            missileCount--;
            Counters::rockets_left--;
            if (missileCount == 0) {
                cnt = 0;
            }
        } else if (cnt > 120) {
            Counters::rockets_left--;
            printf("%d\n", cnt);
            auto *missile = new PlayerMissile(player->xPos, player->yPos);
            Game::playerMissile.push_back(missile);
            cnt = 0;
        }
    }
}

void Game::addPlayerBullet() {
    if (player->hit == false) {
        DefaultBullet *playerBullet = new PlayerBullet(player->xPos, player->yPos);
        Game::playerBullets.push_back(playerBullet);
    }
}