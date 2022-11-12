
#include "UIButtons.h"

UIButtons::UIButtons(const char *text, int x, int y, int font_size) : UILabel(text, x, y, font_size) {
    buttonText = TextureManager::LoadTexture("../Assets/button.png");
    srcR.x = 256;
    srcR.y = 0;
    srcR.w = 256;
    srcR.h = 256;

    destR.x = this->x - 10;
    destR.y = this->y - 10;
    destR.w = this->width + 20;
    destR.h = this->height + 20;

    isVisible = true;

}

UIButtons::~UIButtons() {

}

void UIButtons::Render() {
    SDL_RenderCopy(Game::renderer, buttonText, &srcR, &destR);
    UILabel::Render();
}

bool UIButtons::HandleButtonClickEventsFromMouse(int x, int y) {

    if (x > destR.x && x < (destR.x + destR.w)) {
        if (y > destR.y && y < (destR.y + destR.h))
            return true;
    }
    return false;
}
