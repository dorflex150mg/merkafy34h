#ifndef BOSS_H_
#define BOSS_H_

#include "enemy.h"
#include "projectile.h"
#include "movement_strategy.h"
//#include "enemy_missile.h"
//#include "enemy_projectile.h"

#define HEALTHBOSS1	2000

#define TYPEBOSS1		1

#define SPEEDBOSS1		10
#define WIDTHBOSS1		90
#define HEIGHTBOSS1		68
#define COLDMGBOSS1		30
#define FIREINTVPROJBOSS1	50
#define FIREINTVMSSLBOSS1	125
#define NMOVESTRATSBOSS1	2

#define CANNON1RELATIVEX	10
#define CANNON2RELATIVEX	20

#define BOSS1PATH		"assets/boss1.png"	

class EnemyProjectile;
class EnemyMissile;

class Boss : public Target {
   public:
      MovementStrategy *movement_strategies[2];
      int *fire_counters;
      const char *icon_path;
      int speed;
      int collision_dmg;
      int type;
      int n_move_strategies;
      int cur_stage;
      int proj_fire_interval;
      int mssl_fire_interval;
      int movement_counter;
      bool inc_x;
      bool inc_y;
  
      Boss(int type);
      void move(void);
      //Projectile fire_projectile(void) {
      //   return new Projectile();
      //}
      EnemyProjectile *fireProjectile(void);
      EnemyMissile *fireMissile(void);
      bool isDead(void);
};
#endif
