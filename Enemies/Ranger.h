#include "../GameObject.h"

class Ranger : public GameObject{
public:
    Ranger(int x, int y);
    ~Ranger();
    void Move() override;
    void TakeHit();
    int life;
};