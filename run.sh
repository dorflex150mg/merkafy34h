#!/bin/bash
#g++ ship.cpp -o ship -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -lSDL2_image

g++ animation.cpp boss.cpp enemy.cpp enemy_pos.cpp enemy_projectile.cpp enemy_missile.cpp level.cpp building.cpp movement_strategy.cpp projectile.cpp ship.cpp target.cpp building_pos.cpp main.cpp -o ship  -lSDL2 -lSDL2_image -lSDL2_mixer
./ship
