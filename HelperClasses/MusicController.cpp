//
// Created by Saad Zubairi on 11/21/2022.
//

#include <cstdio>
#include "MusicController.h"

MusicController::MusicController() {
    this->menuMusic = Mix_LoadMUS("../Assets/Music/Menu_Music.wav");
    this->gameMusic = Mix_LoadMUS("../Assets/Music/Game_Music.wav");
    this->gameOverMusic = Mix_LoadMUS("../Assets/Music/GameOver.wav");

    this->shot = Mix_LoadWAV("../Assets/Music/Shot.wav");
    this->Rocket = Mix_LoadWAV("../Assets/Music/Rocket.wav");
    this->Hit = Mix_LoadWAV("../Assets/Music/Hit.wav");
    this->Boom = Mix_LoadWAV("../Assets/Music/Boom.wav");
    this->BossLevelStart = Mix_LoadWAV("../Assets/Music/BossLevelStart.wav");
}

void MusicController::playMenuMusic() {
    if (menuMusic == NULL) { printf("nope...\n"); }
    else
        Mix_PlayMusic(menuMusic, -1);
}

void MusicController::playGameMusic() {
    Mix_PlayMusic(gameMusic, -1);
}
void MusicController::playGameOver() {
    Mix_PlayMusic(gameOverMusic, -1);
}

void MusicController::playShot() {
    Mix_PlayChannel(-1, shot, 0);
}

void MusicController::playRocket(){
    Mix_PlayChannel(-1,Rocket,0);
};
void MusicController::playHit(){
    Mix_PlayChannel(-1,Hit,0);
};
void MusicController::playBoom(){
    Mix_PlayChannel(-1,Boom,0);
};
void MusicController::playBossLevelStart(){
    Mix_PlayChannel(-1,BossLevelStart,0);
};

