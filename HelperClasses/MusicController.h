#pragma once

#include "SDL_mixer.h"

class MusicController {
public:
    MusicController();
    ~MusicController();


    Mix_Music *menuMusic = NULL;
    Mix_Music *gameMusic = NULL;
    Mix_Music *gameOverMusic = NULL;

    Mix_Chunk* shot = NULL;
    Mix_Chunk* Rocket = NULL;
    Mix_Chunk* Hit = NULL;
    Mix_Chunk* Boom = NULL;
    Mix_Chunk* BossLevelStart = NULL;

    void playMenuMusic();
    void playGameMusic();
    void playShot();
    void playRocket();
    void playHit();
    void playBoom();
    void playGameOver();
    void playBossLevelStart();

};
