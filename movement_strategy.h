#ifndef MOVEMENT_STRATEGY_H_
#define MOVEMENT_STRATEGY_H_

#include "screen.h"

#define MOVEHITWALLS	1	
#define MOVEV		2	


class MovementStrategy {
   public:

      int move_id;    
      
      MovementStrategy(int s_move_id);
      void move(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed);
      void move_v(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed);
      void move_hit_walls(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed);
      void move_straight(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed);
};
#endif
