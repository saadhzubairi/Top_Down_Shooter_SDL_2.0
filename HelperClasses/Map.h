//
// Created by Saad Zubairi on 10/20/2022.
//

#ifndef SDL_TEST_MAP_H
#define SDL_TEST_MAP_H

#include "SDL.h"

class Map {
public:
    Map();
    ~Map();

    void loadMap(int arr[25][35]);
    void drawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture* grass;
    SDL_Texture* water;
    SDL_Texture* dirt;

    int map [25][35];

};


#endif //SDL_TEST_MAP_H
