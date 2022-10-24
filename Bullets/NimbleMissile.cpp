#include "NimbleMissile.h"
#include <stdio.h>

NimbleMissile::NimbleMissile(int TarX, int TarY, const char *textureSheet, int x, int y, int sheetSizeXy,
                             int numSprites) :
        PlayerBullet(textureSheet, x, y, sheetSizeXy, numSprites) {
    this->TarX = TarX;
    this->TarY = TarY;

    xFactor = 0;
    dX = TarX - xPos;
    dY = TarY - yPos;
    slope = dY / dX;
    xFactor = dY / slope;
    xFactor = xFactor / 50;
}

NimbleMissile::~NimbleMissile() {

}

void NimbleMissile::Move() {
    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(xFactor, 9);

    if (yPos > 1000) {
        this->alive = false;
    }
}
