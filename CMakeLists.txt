cmake_minimum_required(VERSION 3.23)
project(SDL_test)

set(CMAKE_CXX_STANDARD 14)
set(SDL2_INCLUDE_DIR C:\\src\\SDL\\include)
set(SDL2_INCLUDE_DIR2 C:\\src\\SDL2_image-2.6.2\\include)
set(SDL2_INCLUDE_DIR3 C:\\src\\SDL2_ttf-2.20.1\\include)

set(SDL2_LIB_DIR C:\\src\\SDL\\lib\\x86)
set(SDL2_LIB_DIR2 C:\\src\\SDL2_image-2.6.2\\lib\\x86)
set(SDL2_LIB_DIR3 C:\\src\\SDL2_ttf-2.20.1\\lib\\x86)


include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR2})
include_directories(${SDL2_INCLUDE_DIR3})

link_directories(${SDL2_LIB_DIR})
link_directories(${SDL2_LIB_DIR2})
link_directories(${SDL2_LIB_DIR3})


add_executable(SDL_test main.cpp Game.cpp Game.h HelperClasses/TextureManager.h HelperClasses/TextureManager.cpp GameObject.h GameObject.cpp HelperClasses/Map.cpp HelperClasses/Map.h PlayerShip.cpp PlayerShip.h Enemies/Ranger.cpp Enemies/Ranger.h Enemies/Nimble.cpp Enemies/Nimble.h Bullets/DefaultBullet.cpp Bullets/DefaultBullet.h Bullets/EnemyBullet.cpp Bullets/EnemyBullet.h Bullets/NimbleBullet.cpp Bullets/NimbleBullet.h Bullets/PlayerBullet.cpp Bullets/PlayerBullet.h Bullets/PlayerMissile.cpp Bullets/PlayerMissile.h UIElementsForGame/UILabel.cpp UIElementsForGame/UILabel.h UIElementsForGame/Counters.cpp UIElementsForGame/Counters.h UIElementsForGame/UIButtons.cpp UIElementsForGame/UIButtons.h Bullets/RotatingBullet.cpp Bullets/RotatingBullet.h Enemies/Turret.cpp Enemies/Turret.h Enemies/Boss.cpp Enemies/Boss.h HelperClasses/Boom.cpp HelperClasses/Boom.h Bullets/BossBullet.cpp Bullets/BossBullet.h HelperClasses/BoomHit.cpp HelperClasses/BoomHit.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)



