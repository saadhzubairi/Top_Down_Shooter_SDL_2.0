#include <SDL.h>
#include <string>
#include "Game.h"
#include "GameObject.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {

    game = new Game();

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game->init("BirchEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, false);

    bool check_end = false;

    while (game->running() == true) {
        Counters::frame++;
        if(Counters::frame%5==0) Counters::spriteFrame++;
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        game->deleteDeadStuff();
        game->checkCollisions();
        game->respawnEnemies();
        game->quitGame();
        check_end = game->quitGame();

        if(check_end) break;
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}