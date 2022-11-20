#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../Game.h"
#include <string>
#include "../HelperClasses/TextureManager.h"
#include "UILabel.h"

class UIButtons : public UILabel {
public:
    UIButtons(const char *text, int x, int y,
              int font_size);
    ~UIButtons();
    SDL_Texture *buttonText;
    SDL_Rect srcR, destR;
    bool HandleButtonClickEventsFromMouse(int x, int y);
    void HandleHoverEffects(int x, int y);
    void Render();

};
