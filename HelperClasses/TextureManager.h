#pragma once

#include "SDL.h"
#include "SDL_image.h"

class TextureManager {
public:
    static SDL_Texture *LoadTexture(const char *fn);

    static void Draw(SDL_Texture *tex, SDL_Rect srcR, SDL_Rect destR);

    static SDL_Texture *LoadSprite(const char *fn, int sheetSizeX, int sheetSizeY, int rows, int cols, SDL_Rect* spriteSourceRects);
};
