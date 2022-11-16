#include "Boss.h"

Boss::Boss(int x, int y) : GameObject("../Assets/BOSS.png", x, y, 128, 1, 2) {
    turretm = new Turret(x, y + 25);
    turretl = new Turret(x - 170, y + 25);
    turretr = new Turret(x + 170, y + 25);
}

Boss::~Boss() {

}

void Boss::Render() {
    GameObject::Render();
    turretm->Render();
    turretl->Render();
    turretr->Render();
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

    /*turretm->xPos = turretl->xPos = turretr->xPos = this->xPos;*/
    turretm->yPos = turretl->yPos = turretr->yPos = this->yPos + 25;


}

void Boss::Update() {
    GameObject::Update();
    turretm->Update();
    turretl->Update();
    turretr->Update();
}
