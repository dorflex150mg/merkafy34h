#include "movement_strategy.h"
#include "screen.h"

MovementStrategy::MovementStrategy(int s_move_id){}

void MovementStrategy::move(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){}
void MovementStrategy::move_v(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){}
void MovementStrategy::move_hit_walls(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){}
void MovementStrategy::move_straight(int *posx, int *posy, bool *inc_x, bool *inc_y, int speed){}
