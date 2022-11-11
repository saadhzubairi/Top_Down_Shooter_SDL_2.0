#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Label {
public:
    Label(const char *text, int x, int y);
    ~Label();
    TTF_Font *roboto;
    SDL_Texture *textTexture;
    SDL_Rect textRect;
    void Render();

};
