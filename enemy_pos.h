#pragma once
#ifndef ENEMY_POS_H_
#define ENEMY_POS_H_

#define NENMY0	30
#define NENMY2	50
#define NENMY4	70
#define NENMY6	90
#define NENMY8	110

struct enemy_pos_t{ 
   int x; 
   int scroll;
   int type;
   int move;
   bool active;
};

//static struct enemy_pos_t **enemies_pos;
//static struct enemy_pos_t *enemies_lvl0;
//static struct enemy_pos_t *enemies_lvl2;
//static struct enemy_pos_t *enemies_lvl4;
//static struct enemy_pos_t *enemies_lvl6;
//static struct enemy_pos_t *enemies_lvl8;

void init_enemies(int level);
struct enemy_pos_t *get_enemies_pos(int level);

#endif
