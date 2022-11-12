#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "string"
#include "../Game.h"
#include <string>

class UILabel {
public:
    UILabel(const char *text, int x, int y, int font_size);
    ~UILabel();
    TTF_Font *roboto;
    SDL_Texture *textTexture;
    SDL_Rect textRect;
    void Render();
    void SetText(std::string text);
    SDL_Texture* createText(const char* text, int x, int y, SDL_Rect *textRect);
    int x;
    int y;
    int width;
    int height;
    int font_size;
    bool isVisible;
};
