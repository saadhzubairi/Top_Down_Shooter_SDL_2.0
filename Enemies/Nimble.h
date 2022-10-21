
#include "../GameObject.h"

class Nimble : public GameObject{
public:
    Nimble(const char *textureSheet, int x, int y, int spriteSizeXY, int numSprites);
    ~Nimble();
    void Move() override;
    void TakeHit();
private:
    int life;
};
