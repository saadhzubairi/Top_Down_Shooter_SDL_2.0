#include "Boss.h"

Boss::Boss(int x, int y) : GameObject("../Assets/Bossy.png", x, y, 512,512, 4,1, 1.5) {

    turretll = new Turret(x - 185, y +20);
    turretl = new Turret(x - 60, y+20);
    turretr = new Turret(x + 60, y+20);
    turretrr = new Turret(x + 185, y+20);
}

Boss::~Boss() {

}

void Boss::Render() {
    GameObject::Render();

    turretll->Render();
    turretl->Render();
    turretr->Render();
    turretrr->Render();
}

void Boss::Move() {

    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;

    if (yPos > 170) {
        GameObject::Translate(0, sin(Counters::frame / 50) * 2);

    } else {
        GameObject::Translate(0, 2);
    }
    turretll->yPos = turretl->yPos = turretr->yPos = turretrr->yPos = this->yPos+20;
}

void Boss::Update() {
    GameObject::Update();
    turretll->Update();
    turretl->Update();
    turretr->Update();
    turretrr->Update();
}
