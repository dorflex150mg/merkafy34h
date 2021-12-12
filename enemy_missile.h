#ifndef ENEMY_MISSILE_H_
#define ENEMY_MISSILE_H_
#include <stdlib.h>
#include "target.h"
#include "screen.h"

#define ICONMSSL1	"assets/missile1.png";		

#define TYPEMSSL1		1
#define HEALTHMSSL1		10
#define SPEEDMSSL1		7
#define WIDTHMSSL1		15
#define HEIGHTMSSL1	        30
#define DMGMSSL1		30
#define HITBOXWIDTH		25


class EnemyMissile : public Target {
   public:
      static const int limit_bottom = SCREEN_HEIGHT;
      static const int limit_right = SCREEN_WIDTH;
      const char* icon_path; 
      int type;
      int movement_counter;
      int speed;
      int init_posx;
      int init_posy;
      int limit_top;
      int limit_left;
      int health;
      int damage;

      EnemyMissile(int posx, int posy, int stype); 

      int getHitBoxPosx(void);
      int getHitBoxWidth();
      int getDamage();
      void move(int ship_posx, int ship_posy);
};
#endif
