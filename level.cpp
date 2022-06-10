#include <stdio.h>
#include "themes.h"
#include "level.h"
#include "level_data.h"
#include "enemy_pos_dat.h"
#include "building_pos_data.h"
#include "background.h"

Level::Level(int s_n_level){
   n_level = s_n_level;
   finished = false;
   switch(n_level) {
      case 0:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL0;
         is_boss = false;
         length = LENGTHLVL0;
         n_buildings = NBDNG0;
         n_enemies = NENMY0;
         break;
      case 1:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL1;
         is_boss = true;
	 printf("creating getting boss type 1\n");
         boss = new Boss(TYPEBOSS1);
	 n_buildings = 0;
	 n_enemies = 0;
         break;
      case 2:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL2;
         is_boss = false;
         length = LENGTHLVL2;
         n_buildings = NBDNG2;
         n_enemies = NENMY2;
	 n_buildings = 0;
	 n_enemies = 0;
         break;
      case 3:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL3;
         is_boss = true;
	 n_buildings = 0;
	 n_enemies = 0;
         break;
      case 4:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL4;
         is_boss = false;
         length = LENGTHLVL4;
         n_buildings = NBDNG4;
         n_enemies = NENMY4;
         break;
      case 5:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL5;
         is_boss = true;
	 n_buildings = 0;
	 n_enemies = 0;
         break;
      case 6:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL6;
         is_boss = false;
         length = LENGTHLVL6;
         n_buildings = NBDNG6;
         n_enemies = NENMY6;
         break;
      case 7:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL7;
         is_boss = true;
	 n_buildings = 0;
	 n_enemies = 0;
         break;
      case 8:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL8;
         is_boss = false;
         length = LENGTHLVL8;
         n_buildings = NBDNG8;
         n_enemies = NENMY8;
         break;
      case 9:
         bgs = (Background **) malloc(sizeof(Background*) * N_BG0);
	 bgs[0] = new Background(BG00);
	 bgs[1] = new Background(BG01);
	 cur_bg = bgs[0];
	 next_bg = bgs[1];
         theme_path = (char*) THEMELVL8;
         is_boss = true;
	 n_buildings = 0;
	 n_enemies = 0;
         break;
      default:
         theme_path = (char*) THEMELVL0;
         length = LENGTHLVL0; 
         n_buildings = NBDNG0;
         n_enemies = NENMY0;
    }
}

char *Level::getThemePath(){
   return theme_path;
} 

int Level::getLength(){
   return length;
}

int Level::getLevel() {
   return n_level;
}

void Level::finish(){
   finished = true;
}

int Level::getnBuildings(){
   return n_buildings;
}

int Level::getnEnemies(){
   return n_enemies;
}

bool Level::isBossLevel() {
   return is_boss;
}

Background *Level::getCurBg(){
   return cur_bg;
}

Background *Level::getNextBg(){
   return next_bg;
}

Boss *Level::getBoss() {
   return boss;
}
