#include<iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Bullets/DefaultBullet.h"
#include "Bullets/EnemyBullet.h"
#include "SDL_ttf.h"

class Game {

public:
    Game();
    ~Game();
    void init(const char *title, int xpos, int ypos, int width, int heigh, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void deleteDeadStuff();
    void clean();
    bool running();
    void checkCollisions();
    void respawnEnemies();

    static void addPlayerBullet();
    static void addPlayerMissile();
    static void addEnemyBullet();
    static void addNimbleBullet();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<DefaultBullet*> playerBullets;
    static std::vector<DefaultBullet*> playerMissile;
    static std::vector<EnemyBullet*> enemyBullets;
    static int height;
    static int width;

private:
    static int cnt;
    static int missileCount;
    bool isRunning;
    SDL_Window *window;
};