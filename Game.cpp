
#include "Game.h"
#include "UIElementsForGame/UILabel.h"
#include "UIElementsForGame/UIButtons.h"
#include "Enemies/Turret.h"
#include "Enemies/Boss.h"
#include "HelperClasses/Boom.h"
#include "HelperClasses/BoomHit.h"
#include "Bullets/BossBullet.h"


SDL_Renderer *Game::renderer = nullptr;


std::vector<DefaultBullet *>    Game::playerBullets;
std::vector<DefaultBullet *>    Game::playerMissile;
std::vector<EnemyBullet *>    Game::enemyBullets;
std::vector<GameObject *>    Game::booms;

std::vector<UILabel *> labels;

PlayerShip *Game::player;

int Game::cnt = 0;

Ranger *ranger;
Nimble *nimble;
Boss *boss;

UIButtons *startGameButton;
UIButtons *quitGameButton;

int Game::height = 0;
int Game::width = 0;

Map *map;
SDL_Event Game::event;

Game::Game() {
    height = 0;
    width = 0;
    cnt = 0;
}

Game::~Game() = default;

void Game::init(const char *title, int xpos, int ypos, int w, int heigh, bool fullscreen) {
    Game::height = heigh;
    Game::width = w;
    this->playStart = false;
    this->bossStart = false;
    this->isRunning = true;
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "[+] SDL initialized!" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, w, heigh, flags);
        if (window) {
            std::cout << "[+] Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "[+] Renderer Created!" << std::endl;
        }

        if (TTF_Init() == -1) {
        } else {
            std::cout << "[+] SDL_ttf Initialized!" << std::endl;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        else printf("[+] SDL_Mixer Initialized\n");

        isRunning = true;
    } else { isRunning = false; }
    musicController = new MusicController();
    musicController->playMenuMusic();
    startGameButton = new UIButtons("START", 500, 350, 105);
    quitGameButton = new UIButtons("QUIT", 500, 475, 55);

    map = new Map();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        isRunning = false;
    } else if (event.type == SDL_KEYDOWN && playStart) {
        switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                player->Translate(8, 0);
                break;
            case SDLK_LEFT:
                player->Translate(-8, 0);
                //SDL_PushEvent(&event);
                break;
            case SDLK_UP:
                player->Translate(0, -8);
                //SDL_PushEvent(&event);
                break;
            case SDLK_DOWN:
                player->Translate(0, 8);
                //SDL_PushEvent(&event);
                break;
            case SDLK_SPACE:
                addPlayerBullet();
                musicController->playShot();
                break;
            case SDLK_b:
                musicController->playRocket();
                addPlayerMissile();
                break;
            default:
                break;
        }
    } else if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (!playStart) {
            bool startPressed = startGameButton->HandleButtonClickEventsFromMouse(x, y);
            if (startPressed) { startGame(); musicController->playGameMusic();}

            bool quitPressed = quitGameButton->HandleButtonClickEventsFromMouse(x, y);
            if (quitPressed) isRunning = false;
        }
    }
}

bool Game::quitGame() {
    return !isRunning;
}

void Game::startGame() {
    Counters::rockets_left = 10;
    Counters::nimble_kills = 0;
    Counters::ranger_kills = 0;

    player = new PlayerShip(width / 2 - 66, height - 154);
    ranger = new Ranger(200, 10);
    nimble = new Nimble(600, 10);
    labels.push_back(new UILabel("Rangers Killed: ", 100, 30, 20));
    labels.push_back(new UILabel("Nimbles Killed: ", 300, 30, 20));
    labels.push_back(new UILabel("Rockets Left: ", 850, 30, 24));
    labels.push_back(new UILabel("0", 200, 30, 20));
    labels.push_back(new UILabel("0", 400, 30, 20));
    labels.push_back(new UILabel("0", 940, 30, 24));
    labels.push_back(new UILabel("Boss in: ", 60, 60, 15));
    labels.push_back(new UILabel("0", 100, 60, 15));
    playStart = true;
}

void Game::startBoss() {

    musicController->playBossLevelStart();
    ranger->Translate(-1000, 0);
    nimble->Translate(-1000, 0);
    delete ranger;
    delete nimble;
    labels.clear();
    enemyBullets.clear();
    bossStart = true;
    Counters::rockets_left = 10;
    boss = new Boss(500, -128);

    labels.push_back(new UILabel("Boss Life Left: ", 100, 30, 20));
    labels.push_back(new UILabel("10", 200, 30, 20));
    labels.push_back(new UILabel("Rockets Left: ", 850, 30, 24));
    labels.push_back(new UILabel("0", 940, 30, 24));
}

void Game::render() {

    SDL_RenderClear(renderer);
    map->drawMap();

    if (playStart) {
        //both level objects


        for (UILabel *label: labels) { label->Render(); }

        if (bossStart) { boss->Render(); }

        for (EnemyBullet *enemyBullet: Game::enemyBullets) { enemyBullet->Render(); }

        if (bossStart) { boss->RenderTurrets(); }

        for (DefaultBullet *playerBullet: Game::playerBullets) { playerBullet->Render(); }

        if (!bossStart) {
            if (ranger->isAlive()) ranger->Render();
            if (nimble->isAlive()) nimble->Render();
        }
        for (GameObject *boom: Game::booms) { boom->Render(); }
        for (DefaultBullet *playerBullet: Game::playerMissile) { playerBullet->Render(); }
        if (player->isAlive()) player->Render();
    } else {
        startGameButton->Render();
        quitGameButton->Render();
    }
    SDL_RenderPresent(Game::renderer);
}

void Game::update() {
    if (playStart) {
        if (player->isAlive()) {
            player->Update();
            player->Move();
        }
        for (GameObject *boom: Game::booms) {
            boom->Update();
            boom->Move();
        }
        for (DefaultBullet *playerBullet: Game::playerBullets) {
            playerBullet->Update();
            playerBullet->Move();
        }
        for (DefaultBullet *playerMissile: Game::playerMissile) {
            playerMissile->Update();
            playerMissile->Move();
        }

        for (EnemyBullet *enemyBullet: Game::enemyBullets) {
            enemyBullet->Update();
            enemyBullet->Move();
        }

        if (bossStart) {
            boss->Update();
            boss->Move();
            addBossBullet();

            if (!boss->turretl->isAlive() && !boss->turretll->isAlive() && !boss->turretr->isAlive() &&
                !boss->turretrr->isAlive() && !Counters::bossDead
                    ) {
                Counters::bossDead = true;
                musicController->playBoom();
                booms.push_back(new Boom(boss->xPos, boss->yPos));
                musicController->playBoom();
                booms.push_back(new Boom(boss->xPos - 200, boss->yPos));
                musicController->playBoom();
                booms.push_back(new Boom(boss->xPos + 200, boss->yPos));
            }


        } else {
            if (ranger->isAlive()) {
                ranger->Update();
                ranger->Move();
            }
            if (nimble->isAlive()) {
                nimble->Update();
                nimble->Move();
            }

            addEnemyBullet();
        }

        //WHERE PLAYER DIES
        cnt++;
        if (player->hit) {
            if (cnt == 120) {
                playStart = false;
                bossStart = false;
                Counters::frame = 0;
                musicController->playMenuMusic();
                startGameButton->SetText("TRY AGAIN");
                labels.clear();
                enemyBullets.clear();
                playerBullets.clear();
            }
        }

        //WHEN BOSS DIES:
        if (Counters::bossDead) {
            Counters::bossDeathCounter--;
            if (Counters::bossDeathCounter <= 0) {
                Counters::bossDeathCounter = 60;
                Counters::bossDead = false;
                enemyBullets.clear();
                playerBullets.clear();
                labels.clear();
                playStart = false;
                bossStart = false;
                startGameButton->SetText("Play Again, Winner!");
                Counters::frame = 0;
                musicController->playMenuMusic();
            }
        }

        //TO START BOSS LEVEL
        if (Counters::frame >= 1800 && !bossStart) {
            startBoss();
        }

        //REFULE 1 MISSILE
        if (Counters::rockets_left == 0) {
            if (cnt > 120) Counters::rockets_left = 1;
        }

        if (playStart) {
            if (bossStart) {
                std::string m = std::to_string(Counters::enemy_health);
                labels[1]->SetText(m);
                m = std::to_string(Counters::rockets_left);
                labels[3]->SetText(m);
            } else {
                std::string m = std::to_string(Counters::ranger_kills);
                labels[3]->SetText(m);
                m = std::to_string(Counters::nimble_kills);
                labels[4]->SetText(m);
                m = std::to_string(Counters::rockets_left);
                labels[5]->SetText(m);
                m = std::to_string(30 - Counters::frame / 60);
                labels[7]->SetText(m);
            }
        }
        for (DefaultBullet *missile: playerMissile) {
            if (Counters::frame%2==0){
                booms.push_back(new Smoke(missile->xPos,missile->yPos));
            }
        }
    }
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "[+] Game Cleaned!" << std::endl;
}

bool Game::running() { return this->isRunning; }

void Game::deleteDeadStuff() {
    for (int i = 0; i < Game::playerBullets.size(); ++i) {
        if (!Game::playerBullets.at(i)->isAlive()) {
            Game::playerBullets.erase(Game::playerBullets.begin() + i);
        }
    }
    for (int i = 0; i < Game::playerMissile.size(); ++i) {
        if (!Game::playerMissile.at(i)->isAlive()) {
            Game::playerMissile.erase(Game::playerMissile.begin() + i);
        }
    }
    for (int i = 0; i < Game::enemyBullets.size(); ++i) {
        if (!Game::enemyBullets.at(i)->isAlive()) {
            Game::enemyBullets.erase(Game::enemyBullets.begin() + i);
        }
    }
    for (int i = 0; i < Game::booms.size(); ++i) {
        if (!Game::booms.at(i)->isAlive()) {
            Game::booms.erase(Game::booms.begin() + i);
        }
    }

}

void Game::checkCollisions() {

    //IF BULLET HITS RANGER OR NIMBLE:
    for (DefaultBullet *playerBullet: Game::playerBullets) {

        //RANGER & NIMBLE
        if (checkObjsCollide(playerBullet, ranger)) {
            ranger->TakeHit();
            booms.push_back(new BoomHit(ranger->xPos, ranger->yPos));
            musicController->playHit();
            playerBullet->Destroy();
        }

        if (bossStart) {
            if (checkObjsCollide(playerBullet, boss->turretl) && boss->turretl->isAlive()) {
                boss->turretl->TakeHit();
                playerBullet->Destroy();
                booms.push_back(new BoomHit(boss->turretl->xPos, boss->turretl->yPos));
                musicController->playHit();
                Counters::enemy_health--;

                if(!boss->turretl->isAlive()){
                    musicController->playBoom();
                }

            }
            if (checkObjsCollide(playerBullet, boss->turretll) && boss->turretll->isAlive()) {
                boss->turretll->TakeHit();
                playerBullet->Destroy();
                musicController->playHit();
                booms.push_back(new BoomHit(boss->turretll->xPos, boss->turretll->yPos));
                Counters::enemy_health--;
                if(!boss->turretll->isAlive()){
                    musicController->playBoom();
                }
            }
            if (checkObjsCollide(playerBullet, boss->turretr) && boss->turretr->isAlive()) {
                boss->turretr->TakeHit();
                playerBullet->Destroy();
                musicController->playHit();
                booms.push_back(new BoomHit(boss->turretr->xPos, boss->turretr->yPos));
                Counters::enemy_health--;
                if(!boss->turretr->isAlive()){
                    musicController->playBoom();
                }
            }
            if (checkObjsCollide(playerBullet, boss->turretrr) && boss->turretrr->isAlive()) {
                boss->turretrr->TakeHit();
                playerBullet->Destroy();
                musicController->playHit();
                booms.push_back(new BoomHit(boss->turretrr->xPos, boss->turretrr->yPos));
                Counters::enemy_health--;
                if(!boss->turretrr->isAlive()){
                    musicController->playBoom();
                }
            }
        }

        //NIMBLE DODGE
        if (playerBullet->yPos >= (nimble->yPos) && playerBullet->yPos <= (nimble->yPos + 150)) {
            if (playerBullet->xPos >= (nimble->xPos - 64) && playerBullet->xPos <= (nimble->xPos)) {
                nimble->Translate(20, 0);
            } else if (playerBullet->xPos >= (nimble->xPos) && playerBullet->xPos <= (nimble->xPos + 64)) {
                nimble->Translate(-20, 0);
            }
        }
    }

    //IF MISSILE HITS RANGER OR NIMBLE:
    for (DefaultBullet *playerMissile: Game::playerMissile) {

        if (checkObjsCollide(playerMissile, ranger)) {
            ranger->TakeHit();
            ranger->TakeHit();
            ranger->TakeHit();
            booms.push_back(new Boom(ranger->xPos, ranger->yPos));
            musicController->playBoom();
            playerMissile->Destroy();
        }

        if (checkObjsCollide(playerMissile, nimble)) {
            nimble->TakeHit();
            playerMissile->Destroy();
        }

        //NIMBLE DODGE
        if (playerMissile->yPos >= (nimble->yPos) && playerMissile->yPos <= (nimble->yPos + 256)) {
            if (playerMissile->xPos >= (nimble->xPos - 128) && playerMissile->xPos <= (nimble->xPos)) {
                nimble->Translate(1, -3);
            } else if (playerMissile->xPos >= (nimble->xPos) && playerMissile->xPos <= (nimble->xPos + 128)) {
                nimble->Translate(-1, -3);
            }
        }
    }

    //IF BULLET HITS PLAYER
    for (EnemyBullet *enemyBullet: Game::enemyBullets) {
        if (checkObjsCollide(enemyBullet, player)) {
            if (!player->hit) {
                /*enemyBullet->Destroy();
                player->setObjTexture("../Assets/Explosion.png", 768,256,1,3, 0.5);
                musicController->playGameOver();
                musicController->playBoom();
                player->TakeHit();
                cnt = 0;*/
            }
        }
    }
}

bool Game::checkObjsCollide(GameObject *GO1, GameObject *GO2) {
    if ((GO1->xMin >= GO2->xMin && GO1->xMin <= GO2->xMax) || (GO2->xMin >= GO1->xMin && GO2->xMin <= GO1->xMax)) {
        if ((GO1->yMin >= GO2->yMin && GO1->yMin <= GO2->yMax) || (GO2->yMin >= GO1->yMin && GO2->yMin <= GO1->yMax)) {
            return true;
        }
    }
    return false;
}

void Game::respawnEnemies() {
    if (playStart) {
        if (!bossStart) {
            if (!ranger->isAlive()) {
                if (ranger->life == 0) {
                    Counters::ranger_kills++;
                    auto newBoom = new Boom(ranger->xPos, ranger->yPos);
                    booms.push_back(newBoom);
                    musicController->playBoom();
                }

                int x = rand() % 9;
                ranger = new Ranger(x * 100 + 64, -128);
            }
            if (!nimble->isAlive()) {
                if (nimble->life == 0) {
                    Counters::nimble_kills++;
                    auto newBoom = new Boom(nimble->xPos, nimble->yPos);
                    booms.push_back(newBoom);
                    musicController->playBoom();
                }
                int x = rand() % 9;
                nimble = new Nimble(x * 100 + 64, -128);
            }
        }
    }
}

void Game::addEnemyBullet() {
    int x = rand() % 200;
    int l = 198;
    if (x > l) {
        if (ranger->xPos >= player->xPos - 64 && ranger->xPos <= player->xPos + 64) {
            EnemyBullet *enemyBullet = new EnemyBullet(
                    ranger->xPos, ranger->yPos);
            Game::enemyBullets.push_back(enemyBullet);
        }
    }
    if (x > l) {
        NimbleBullet *enemyBullet = new NimbleBullet(nimble->xPos, nimble->yPos);
        Game::enemyBullets.push_back(reinterpret_cast<EnemyBullet *const>(enemyBullet));
    }
}

void Game::addBossBullet() {
    int x = rand() % 300;
    int l = 290;
    if (x > l && boss->turretl->isAlive()) {
        BossBullet *bossBullet = new BossBullet(boss->turretl->xPos, boss->turretl->yPos);
        Game::enemyBullets.push_back(reinterpret_cast<EnemyBullet *const>(bossBullet));
    }
    x = rand() % 300;
    if (x > l && boss->turretll->isAlive()) {
        BossBullet *bossBullet = new BossBullet(boss->turretll->xPos, boss->turretll->yPos);
        Game::enemyBullets.push_back(reinterpret_cast<EnemyBullet *const>(bossBullet));
    }
    x = rand() % 300;
    if (x > l && boss->turretr->isAlive()) {
        BossBullet *bossBullet = new BossBullet(boss->turretr->xPos, boss->turretr->yPos);
        Game::enemyBullets.push_back(reinterpret_cast<EnemyBullet *const>(bossBullet));
    }
    x = rand() % 300;
    if (x > l && boss->turretrr->isAlive()) {
        BossBullet *bossBullet = new BossBullet(boss->turretrr->xPos, boss->turretrr->yPos);
        Game::enemyBullets.push_back(reinterpret_cast<EnemyBullet *const>(bossBullet));
    }
}

void Game::addPlayerMissile() {

    if (!player->hit) {
        GameObject *eInput;
        int x = rand() % 2;

        if (Counters::rockets_left > 0) {
            if (x == 0) eInput = ranger;
            else eInput = nimble;
            auto *missile = new PlayerMissile(player->xPos, player->yPos, eInput);
            Game::playerMissile.push_back(missile);
            Counters::rockets_left--;
            if (Counters::rockets_left == 0) {
                cnt = 0;
            }
        } else if (cnt > 120) {
            Counters::rockets_left--;
            if (x == 0) eInput = ranger;
            else eInput = nimble;
            auto *missile = new PlayerMissile(player->xPos, player->yPos, eInput);
            Game::playerMissile.push_back(missile);
            cnt = 0;
        }
    }
}

void Game::addPlayerBullet() {
    if (!player->hit) {
        DefaultBullet *playerBullet = new PlayerBullet(player->xPos, player->yPos);
        Game::playerBullets.push_back(playerBullet);
    }
}


