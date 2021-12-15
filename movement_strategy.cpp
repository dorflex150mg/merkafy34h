#include "movement_strategy.h"
#include "screen.h"

MovementStrategy::MovementStrategy(int s_move_id){}

void MovementStrategy::move(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){
   if(*inc_y) {
      (*posy)--;
   } else {
      (*posy)++;
   }
   if(*inc_x) {
      (*posx)--;
   } else {
      (*posx)++;
   }
   if(*posy > SCREEN_HEIGHT) {
      *inc_y = true;  
   }
   if(*posx > SCREEN_WIDTH) {
      *inc_x = true;
   }
   if(*posy < 0) {
      *inc_y = false;
   }
   if(*posx < 0) {
      *inc_x = false;
   }
}
void MovementStrategy::move_v(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){}
void MovementStrategy::move_hit_walls(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){}
void MovementStrategy::move_straight(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){}
