#include <stdlib.h>
#include "boss.h"
#include "enemy.h"
#include "projectile.h"
#include "movement_strategy.h"

Boss::Boss(int type) {
   cur_stage = 0;
   movement_counter = 0;
   inc_x = false;
   inc_y = false;
   switch(type) {
      case TYPEBOSS1:
	 fire_counters = (int *) malloc(sizeof(int) * 2);
         health = HEALTHBOSS1;
         speed = SPEEDBOSS1;
         width = WIDTHBOSS1;
         height = HEIGHTBOSS1;
         collision_dmg = COLDMGBOSS1;
	 proj_fire_interval = FIREINTVPROJBOSS1;
	 mssl_fire_interval = FIREINTVMSSLBOSS1;
         movement_strategies[0] = new MovementStrategy(MOVEV);
         movement_strategies[1] = new MovementStrategy(MOVEHITWALLS);
         break;
      default: 
         health = HEALTHBOSS1;
         speed = SPEEDBOSS1;
         width = WIDTHBOSS1;
         height = HEIGHTBOSS1;
         collision_dmg = COLDMGBOSS1;
         break;
   }

}
 
void Boss::move(void) {
   movement_counter++;
   switch(type) {
      case TYPEBOSS1:
         if(health < HEALTHBOSS1/2) {
            cur_stage = 1;
         }
         break;
      default:
         break; 
   }
   movement_strategies[cur_stage]->move(&posx, &posy, &inc_x, &inc_y, speed); 
}

//Projectile fire_projectile(void) {
//   return new Projectile();
//}

EnemyProjectile *Boss::fireProjectile(void) {
   int proj_posy;
   int proj_posx;
   int proj_direction;
   if(movement_counter % proj_fire_interval == 0) {
      /* choosing cannon - half of the times, the movement counter
       * is divisible by half of the fire intervals (2n/2 vs (2n + 1)/2)*/
      if(movement_counter % (proj_fire_interval/2) == 0) {
         proj_posx = posx + CANNON1RELATIVEX;
         proj_direction = fire_counters[0] % 3;
	 fire_counters[0]++;
      } else {
         proj_posx = posx + CANNON2RELATIVEX;
         proj_direction = fire_counters[1] % 3;
	 fire_counters[1]++;
      }
      proj_posy = posy + HEIGHTBOSS1;
      return new EnemyProjectile(proj_posx, proj_posy, TYPEM1, proj_direction);
   }
   return nullptr;
}


EnemyMissile *Boss::fireMissile(void){
   if(movement_counter % mssl_fire_interval == 0) {
      return new EnemyMissile(posx, posy, TYPEMSSL1);
   }
   return nullptr;
}

bool Boss::isDead(void) {
   if(health <= 0) {
      return true; 
   }
   return false;
}
