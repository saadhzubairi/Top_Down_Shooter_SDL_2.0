//
// Created by Saad Zubairi on 10/19/2022.
//

#include "TextureManager.h"
#include "../Game.h"

SDL_Texture *TextureManager::LoadTexture(const char *fn) {
    SDL_Surface *tmpSurf = IMG_Load(fn);
    SDL_Texture *text = SDL_CreateTextureFromSurface(Game::renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);
    return text;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect srcR, SDL_Rect destR) {
    SDL_RenderCopy(Game::renderer, tex, &srcR, &destR);
}

SDL_Texture * TextureManager::loadSprite(const char *fn, int sizeXY, int n, SDL_Rect gSpriteClips[3]) {

    SDL_Surface *tmpSurf = IMG_Load(fn);
    SDL_Texture *text = SDL_CreateTextureFromSurface(Game::renderer, tmpSurf);
    SDL_FreeSurface(tmpSurf);

    for (int i = 0; i < n; ++i) {
        gSpriteClips[i].x = i * sizeXY;
        gSpriteClips[i].y = 0;
        gSpriteClips[i].w = sizeXY;
        gSpriteClips[i].h = sizeXY;
    }
    return text;
}




