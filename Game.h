#pragma once

#include<iostream>
#include <vector>
#include <cstdio>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "PlayerShip.h"
#include "GameObject.h"
#include "PlayerShip.h"

#include "HelperClasses/Map.h"

#include "Enemies/Ranger.h"
#include "Enemies/Nimble.h"

#include "Bullets/DefaultBullet.h"
#include "Bullets/PlayerBullet.h"
#include "Bullets/EnemyBullet.h"
#include "Bullets/NimbleBullet.h"
#include "Bullets/PlayerMissile.h"
#include "HelperClasses/Boom.h"
#include "UIElementsForGame/Counters.h"


class Game {

public:
    Game();
    ~Game();
    void init(const char *title, int xpos, int ypos, int w, int heigh, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void deleteDeadStuff();
    void clean();
    bool running();
    void checkCollisions();
    void respawnEnemies();

    void startGame();
    void startBoss();
    bool playStart{};
    bool bossStart{};
    bool quitGame();


    static void addPlayerBullet();
    static void addPlayerMissile();
    static void addEnemyBullet();
    static bool checkObjsCollide(GameObject* GO1, GameObject* GO2);

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<DefaultBullet* > playerBullets;
    static std::vector<DefaultBullet* > playerMissile;
    static std::vector< EnemyBullet*  > enemyBullets;
    static std::vector< Boom*  > booms;

    static PlayerShip *player;

    static int height;
    static int width;

private:
    static int cnt;
    bool isRunning{};
    SDL_Window *window{};
};