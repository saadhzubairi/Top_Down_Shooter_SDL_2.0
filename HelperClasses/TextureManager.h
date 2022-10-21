#pragma once

#include "SDL.h"
#include "SDL_image.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fn);
    static void Draw(SDL_Texture* tex, SDL_Rect srcR,SDL_Rect destR);
    static SDL_Texture * loadSprite(const char *fn, int sizeXY, int n, SDL_Rect gSpriteClips[3]);
};
