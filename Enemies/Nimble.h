
#include "../GameObject.h"

class Nimble : public GameObject{
public:
    Nimble(int x, int y);
    ~Nimble();
    void Move() override;
    void TakeHit();
    int life;
};
