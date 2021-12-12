#include "building_pos.h"
#include "level.h"
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>


struct buildings_pos_t** buildings_pos; 
struct buildings_pos_t* buildings_lvl0; 
struct buildings_pos_t* buildings_lvl2; 
struct buildings_pos_t* buildings_lvl4; 
struct buildings_pos_t* buildings_lvl6; 
struct buildings_pos_t* buildings_lvl8; 

void init_buildings(int level) {
   if(level == 0) {
      /* initializing list of buildings for all levels */
      buildings_pos = (struct buildings_pos_t**) malloc(sizeof(struct buildings_pos_t*) * NLEVELS);
      buildings_lvl0 = (struct buildings_pos_t*) malloc(sizeof(struct buildings_pos_t) * NBDNG0); 
      buildings_lvl2 = (struct buildings_pos_t*) malloc(sizeof(struct buildings_pos_t) * NBDNG2); 
      buildings_lvl4 = (struct buildings_pos_t*) malloc(sizeof(struct buildings_pos_t) * NBDNG4); 
      buildings_lvl6 = (struct buildings_pos_t*) malloc(sizeof(struct buildings_pos_t) * NBDNG6); 
      buildings_lvl8 = (struct buildings_pos_t*) malloc(sizeof(struct buildings_pos_t) * NBDNG8); 

      buildings_pos[0] = buildings_lvl0;
      buildings_pos[2] = buildings_lvl2;
      buildings_pos[4] = buildings_lvl4;
      buildings_pos[6] = buildings_lvl6;
      buildings_pos[8] = buildings_lvl8;

      for(int i = 0; i < NBDNG0; i++) {
         buildings_pos[0][i].active = true;
         buildings_pos[0][i].type = 1;
      }
      buildings_pos[0][0].x = 100;
      buildings_pos[0][1].x = 800;
      buildings_pos[0][2].x = 400;
      buildings_pos[0][3].x = 100;
      buildings_pos[0][4].x = 100;
      buildings_pos[0][5].x = 500;
      buildings_pos[0][6].x = 800;
      buildings_pos[0][7].x = 400;
      buildings_pos[0][8].x = 100;
      buildings_pos[0][9].x = 100;
      buildings_pos[0][0].scroll = -300;
      buildings_pos[0][1].scroll = -500;
      buildings_pos[0][2].scroll = -800;
      buildings_pos[0][3].scroll = -1000;
      buildings_pos[0][4].scroll = -1200;
      buildings_pos[0][5].scroll = -1500;
      buildings_pos[0][6].scroll = -1700;
      buildings_pos[0][7].scroll = -1800;
      buildings_pos[0][8].scroll = -2000;
      buildings_pos[0][9].scroll = -2200;
   } else if(level == 2) {
      for(int i = 0; i < NBDNG2; i++) {
         buildings_pos[2][i].active = true;
         buildings_pos[2][i].type = 1;
      }
      buildings_pos[2][0].x = 100;
      buildings_pos[2][1].x = 800;
      buildings_pos[2][2].x = 400;
      buildings_pos[2][3].x = 100;
      buildings_pos[2][4].x = 100;
      buildings_pos[2][5].x = 500;
      buildings_pos[2][6].x = 800;
      buildings_pos[2][7].x = 400;
      buildings_pos[2][8].x = 100;
      buildings_pos[2][9].x = 100;
      buildings_pos[2][10].x = 100;
      buildings_pos[2][11].x = 800;
      buildings_pos[2][12].x = 400;
      buildings_pos[2][13].x = 100;
      buildings_pos[2][14].x = 100;
      buildings_pos[2][0].scroll = -300;
      buildings_pos[2][1].scroll = -500;
      buildings_pos[2][2].scroll = -800;
      buildings_pos[2][3].scroll = -1000;
      buildings_pos[2][4].scroll = -1200;
      buildings_pos[2][5].scroll = -1500;
      buildings_pos[2][6].scroll = -1700;
      buildings_pos[2][7].scroll = -1800;
      buildings_pos[2][8].scroll = -2000;
      buildings_pos[2][9].scroll = -2200;
      buildings_pos[2][10].scroll = -2300;
      buildings_pos[2][11].scroll = -2400;
      buildings_pos[2][12].scroll = -2500;
      buildings_pos[2][13].scroll = -2750;
      buildings_pos[2][14].scroll = -2900;
   } else if(level == 4) {
      for(int i = 0; i < NBDNG4; i++) {
         buildings_pos[4][i].active = true;
         buildings_pos[4][i].type = 1;
      }
      buildings_pos[4][0].x = 100;           
      buildings_pos[4][1].x = 800;
      buildings_pos[4][2].x = 400;
      buildings_pos[4][3].x = 100;
      buildings_pos[4][4].x = 100;
      buildings_pos[4][5].x = 500;
      buildings_pos[4][6].x = 800;
      buildings_pos[4][7].x = 400;
      buildings_pos[4][8].x = 100;
      buildings_pos[4][9].x = 100;
      buildings_pos[4][10].x = 100;
      buildings_pos[4][11].x = 800;
      buildings_pos[4][12].x = 400;
      buildings_pos[4][13].x = 100;
      buildings_pos[4][14].x = 100;
      buildings_pos[4][15].x = 500;
      buildings_pos[4][16].x = 800;
      buildings_pos[4][17].x = 400;
      buildings_pos[4][18].x = 100;
      buildings_pos[4][19].x = 100;
      buildings_pos[4][20].x = 100;
      buildings_pos[4][21].x = 800;
      buildings_pos[4][22].x = 400;
      buildings_pos[4][23].x = 100;
      buildings_pos[4][24].x = 100;
      buildings_pos[4][0].scroll = -300;
      buildings_pos[4][0].scroll = -300;
      buildings_pos[4][1].scroll = -500;
      buildings_pos[4][2].scroll = -800;
      buildings_pos[4][3].scroll = -1000;
      buildings_pos[4][4].scroll = -1200;
      buildings_pos[4][5].scroll = -1500;
      buildings_pos[4][6].scroll = -1700;
      buildings_pos[4][7].scroll = -1700;
      buildings_pos[4][8].scroll = -1700;
      buildings_pos[4][9].scroll = -2200;
      buildings_pos[4][10].scroll = -2300;
      buildings_pos[4][11].scroll = -2400;
      buildings_pos[4][12].scroll = -2500;
      buildings_pos[4][13].scroll = -2750;
      buildings_pos[4][14].scroll = -2900;
      buildings_pos[4][15].scroll = -3000;
      buildings_pos[4][16].scroll = -3200;
      buildings_pos[4][17].scroll = -3400;
      buildings_pos[4][18].scroll = -3400;
      buildings_pos[4][19].scroll = -3600;
      buildings_pos[4][20].scroll = -3800;
      buildings_pos[4][21].scroll = -3800;
      buildings_pos[4][22].scroll = -4000;
      buildings_pos[4][23].scroll = -4500;
      buildings_pos[4][24].scroll = -5000;
   } else if(level == 6) {
      for(int i = 0; i < NBDNG6; i++) {
         buildings_pos[6][i].active = true;
         buildings_pos[6][i].type = 1;
      }
      buildings_pos[6][0].x = 100;           
      buildings_pos[6][1].x = 800;
      buildings_pos[6][2].x = 400;
      buildings_pos[6][3].x = 100;
      buildings_pos[6][4].x = 100;
      buildings_pos[6][5].x = 500;
      buildings_pos[6][6].x = 800;
      buildings_pos[6][7].x = 400;
      buildings_pos[6][8].x = 100;
      buildings_pos[6][9].x = 100;
      buildings_pos[6][10].x = 100;
      buildings_pos[6][11].x = 800;
      buildings_pos[6][12].x = 400;
      buildings_pos[6][13].x = 100;
      buildings_pos[6][14].x = 100;
      buildings_pos[6][15].x = 500;
      buildings_pos[6][16].x = 800;
      buildings_pos[6][17].x = 400;
      buildings_pos[6][18].x = 100;
      buildings_pos[6][19].x = 100;
      buildings_pos[6][20].x = 100;
      buildings_pos[6][21].x = 800;
      buildings_pos[6][22].x = 400;
      buildings_pos[6][23].x = 100;
      buildings_pos[6][24].x = 100;
      buildings_pos[6][25].x = 500;
      buildings_pos[6][26].x = 800;
      buildings_pos[6][27].x = 400;
      buildings_pos[6][28].x = 100;
      buildings_pos[6][29].x = 100;
      buildings_pos[6][30].x = 100;
      buildings_pos[6][31].x = 800;
      buildings_pos[6][32].x = 400;
      buildings_pos[6][33].x = 100;
      buildings_pos[6][34].x = 100;
      buildings_pos[6][0].scroll = -300;
      buildings_pos[6][1].scroll = -500;
      buildings_pos[6][2].scroll = -800;
      buildings_pos[6][3].scroll = -1000;
      buildings_pos[6][4].scroll = -1200;
      buildings_pos[6][5].scroll = -1500;
      buildings_pos[6][6].scroll = -1700;
      buildings_pos[6][7].scroll = -1700;
      buildings_pos[6][8].scroll = -1700;
      buildings_pos[6][9].scroll = -2200;
      buildings_pos[6][10].scroll = -2700;
      buildings_pos[6][11].scroll = -2800;
      buildings_pos[6][12].scroll = -2900;
      buildings_pos[6][13].scroll = -3000;
      buildings_pos[6][14].scroll = -3000;
      buildings_pos[6][15].scroll = -3500;
      buildings_pos[6][16].scroll = -3700;
      buildings_pos[6][17].scroll = -3800;
      buildings_pos[6][18].scroll = -3800;
      buildings_pos[6][19].scroll = -4000;
      buildings_pos[6][20].scroll = -4200;
      buildings_pos[6][21].scroll = -4200;
      buildings_pos[6][22].scroll = -4200;
      buildings_pos[6][23].scroll = -4200;     
      buildings_pos[6][24].scroll = -4250;
      buildings_pos[6][25].scroll = -4300;
      buildings_pos[6][26].scroll = -4500;
      buildings_pos[6][27].scroll = -4850;
      buildings_pos[6][28].scroll = -4850;
      buildings_pos[6][29].scroll = -4850;
      buildings_pos[6][30].scroll = -5200;
      buildings_pos[6][31].scroll = -5350;
      buildings_pos[6][32].scroll = -5600;
      buildings_pos[6][33].scroll = -5800;     
      buildings_pos[6][34].scroll = -6200;
   } else if(level == 8) {
      for(int i = 0; i < NBDNG8; i++) {
         buildings_pos[8][i].active = true;
         buildings_pos[8][i].type = 1;
      }
      buildings_pos[8][0].x = 100;           
      buildings_pos[8][1].x = 800;
      buildings_pos[8][2].x = 400;
      buildings_pos[8][3].x = 100;
      buildings_pos[8][4].x = 100;
      buildings_pos[8][5].x = 500;
      buildings_pos[8][6].x = 800;
      buildings_pos[8][7].x = 400;
      buildings_pos[8][8].x = 100;
      buildings_pos[8][9].x = 100;
      buildings_pos[8][10].x = 100;
      buildings_pos[8][11].x = 800;
      buildings_pos[8][12].x = 400;
      buildings_pos[8][13].x = 100;
      buildings_pos[8][14].x = 100;
      buildings_pos[8][15].x = 500;
      buildings_pos[8][16].x = 800;
      buildings_pos[8][17].x = 400;
      buildings_pos[8][18].x = 100;
      buildings_pos[8][19].x = 100;
      buildings_pos[8][20].x = 100;
      buildings_pos[8][21].x = 800;
      buildings_pos[8][22].x = 400;
      buildings_pos[8][23].x = 100;
      buildings_pos[8][24].x = 100;
      buildings_pos[8][25].x = 500;
      buildings_pos[8][26].x = 800;
      buildings_pos[8][27].x = 400;
      buildings_pos[8][28].x = 100;
      buildings_pos[8][29].x = 100;
      buildings_pos[8][30].x = 100;
      buildings_pos[8][31].x = 800;
      buildings_pos[8][32].x = 400;
      buildings_pos[8][33].x = 100;
      buildings_pos[8][34].x = 100;
      buildings_pos[8][35].x = 500;
      buildings_pos[8][36].x = 800;
      buildings_pos[8][37].x = 400;
      buildings_pos[8][38].x = 100;
      buildings_pos[8][39].x = 100;
      buildings_pos[8][40].x = 100;
      buildings_pos[8][41].x = 800;
      buildings_pos[8][42].x = 400;
      buildings_pos[8][43].x = 100;
      buildings_pos[8][44].x = 100;
      buildings_pos[8][0].scroll = -300;
      buildings_pos[8][1].scroll = -500;
      buildings_pos[8][2].scroll = -800;
      buildings_pos[8][3].scroll = -1000;
      buildings_pos[8][4].scroll = -1200;
      buildings_pos[8][5].scroll = -1500;
      buildings_pos[8][6].scroll = -1700;
      buildings_pos[8][7].scroll = -1700;
      buildings_pos[8][8].scroll = -1700;
      buildings_pos[8][9].scroll = -2200;
      buildings_pos[8][10].scroll = -2700;
      buildings_pos[8][11].scroll = -2800;
      buildings_pos[8][12].scroll = -2900;
      buildings_pos[8][13].scroll = -3000;
      buildings_pos[8][14].scroll = -3000;
      buildings_pos[8][15].scroll = -3500;
      buildings_pos[8][16].scroll = -3700;
      buildings_pos[8][17].scroll = -3800;
      buildings_pos[8][18].scroll = -3800;
      buildings_pos[8][19].scroll = -4000;
      buildings_pos[8][20].scroll = -4200;
      buildings_pos[8][21].scroll = -4200;
      buildings_pos[8][22].scroll = -4200;
      buildings_pos[8][23].scroll = -4200;     
      buildings_pos[8][24].scroll = -4250;
      buildings_pos[8][25].scroll = -4300;
      buildings_pos[8][26].scroll = -4500;
      buildings_pos[8][27].scroll = -4850;
      buildings_pos[8][28].scroll = -4850;
      buildings_pos[8][29].scroll = -4850;
      buildings_pos[8][30].scroll = -5000;
      buildings_pos[8][31].scroll = -5050;
      buildings_pos[8][32].scroll = -5400;
      buildings_pos[8][33].scroll = -5400;     
      buildings_pos[8][34].scroll = -5500;
      buildings_pos[8][35].scroll = -5900;
      buildings_pos[8][36].scroll = -5900;
      buildings_pos[8][37].scroll = -6500;
      buildings_pos[8][38].scroll = -6500;
      buildings_pos[8][39].scroll = -6500;
      buildings_pos[8][40].scroll = -7000;
      buildings_pos[8][41].scroll = -7000;
      buildings_pos[8][42].scroll = -7000;
      buildings_pos[8][43].scroll = -8500;     
      buildings_pos[8][44].scroll = -8550;
  }

}


struct buildings_pos_t *get_buildings_pos(int level) {
    return buildings_pos[level];    
}


