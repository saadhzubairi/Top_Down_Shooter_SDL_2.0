#include "UILabel.h"


UILabel::UILabel(const char *text, int x, int y, int font_size) {
    roboto = TTF_OpenFont("../Assets/Roboto-Medium.ttf", font_size);
    textTexture = createText(text, x, y, &textRect);
    TTF_CloseFont(roboto);
    this->x = x;
    this->y = y;
    this->font_size = font_size;
    isVisible = true;
}

UILabel::~UILabel() {

}



void UILabel::Render() {
    if(isVisible)
    SDL_RenderCopy(Game::renderer, textTexture, NULL, &textRect);
}

SDL_Texture *UILabel::createText(const char *text, int x, int y, SDL_Rect *textRect) {
    SDL_Surface *surface = TTF_RenderText_Solid(roboto, text, {255, 255, 255});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);

    textRect->x = x - (surface->w/2);
    textRect->y = y - (surface->h/2);
    textRect->h = surface->h;
    textRect->w = surface->w;

    this->width = textRect->w;
    this->height = textRect->h;




    SDL_FreeSurface(surface);
    return textTexture;
}

void UILabel::SetText(std::string text) {
    roboto = TTF_OpenFont("../Assets/Roboto-Medium.ttf", this->font_size);
    textTexture = createText(text.c_str(), this->x, this->y, &textRect);
    TTF_CloseFont(roboto);
}

