#ifndef ENEMY_H_
#define ENEMY_H_

#include "target.h"
#include "enemy_missile.h"
#include "enemy_projectile.h"
#include "screen.h"

#define ICONM1		"assets/m1.png"		
#define ICONM2		"assets/m2.png"

#define MAX_SLOW	10

#define WALLMOVE2	100

#define TYPEM1		1
#define HEALTHM1	20
#define SPEEDM1		7
#define WIDTHM1		48
#define HEIGHTM1	60
#define COLDMGM1	30
#define FIREINTVM1	50

#define TYPEM2		2
#define HEALTHM2	20
#define SPEEDM2		7
#define WIDTHM2		48
#define HEIGHTM2	60
#define COLDMGM2	30
#define FIREINTVM2	100

#define FIRETYPEPJTL	1
#define FIRETYPEMSSL	2

class Enemy : public Target {
   public:
      static const int limit_bottom = SCREEN_HEIGHT;
      static const int limit_right = SCREEN_WIDTH;
      const char* icon_path; 
      int type;
      int fire_interval;
      int fire_counter;
      int fire_type;
      int movement_counter;
      int speed;
      int init_posx;
      int init_posy;
      int limit_top;
      int limit_left;
      int movement;
      int collision_damage;
      bool back;

      Enemy(int s_posx, int s_posy, int s_type, int t_movement);
      void move(void);
      EnemyProjectile *fire_projectile(void); 
      EnemyMissile *fire_missile(void);
};
#endif
