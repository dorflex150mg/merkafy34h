#include <stdio.h>
#include <stdlib.h>

#include "enemy.h"
#include "target.h"
#include "enemy_missile.h"
#include "enemy_projectile.h"

Enemy::Enemy(int s_posx, int s_posy, int s_type, int t_movement) {
   movement_counter = 0;
   fire_counter = 0;
   back = false;
   posx = s_posx;
   target.posx = s_posx;
   posy = s_posy;
   target.posy = s_posy;
   init_posx = s_posx;
   init_posy = s_posy;
   movement = t_movement;
   active = true;
   type = s_type;
   switch(type) {
      case TYPEM1:
         icon_path = ICONM1;
         h = HEIGHTM1;
         w = WIDTHM1;
	 target.w = WIDTHM1;
         health = HEALTHM1;
         target.health = HEALTHM1;
         speed = SPEEDM1;
         fire_interval = FIREINTVM1;
         collision_damage = COLDMGM1;
         fire_type = FIRETYPEPJTL;
         break;
      case TYPEM2:
         icon_path = ICONM2;
         h = HEIGHTM2;
         w = WIDTHM2;
	 target.w = WIDTHM2;
         health = HEALTHM2;
         target.health = HEALTHM2;
         speed = SPEEDM2;
         fire_interval = FIREINTVM2;
         collision_damage = COLDMGM2;
         fire_type = FIRETYPEMSSL;
         break;
      case TYPEM3:
         icon_path = ICONM3;
         h = HEIGHTM3;
         w = WIDTHM3;
	 target.w = WIDTHM3;
         health = HEALTHM3;
         target.health = HEALTHM3;
         speed = SPEEDM3;
         fire_interval = FIREINTVM3;
         collision_damage = COLDMGM3;
         fire_type = FIRETYPEPJTL;
         break;
      default:
         icon_path = ICONM1;
         h = HEIGHTM1;
         w = WIDTHM1;
         break;
   }
   /* Whole figure must leave screen to be off bounds, thus y < -h
   and x < -w */
   limit_top = -h;
   limit_left = -w;
}

Target *Enemy::getTarget(void) {
   return &target;
}
 
void Enemy::move(void){
   movement_counter++;
   /* MAX_SLOW is 10, which is the minimum speed (1 pixel every 10 move calls) */
   /* speed must not exceed max slow */
   int slow = MAX_SLOW - speed;
   if(movement_counter % slow == 0) {
      if(movement == 1) {
         if(init_posx < SCREEN_WIDTH/2){
            posx++;
	    target.posx++;
         } else {
            posx--;
            target.posx--;
         }
         posy++;
	 target.posy++;
      } else if(movement == 2) {
         if(posx < init_posx + WALLMOVE2 && !back) {
            posx++;
            target.posx++;
         } else if (posx > init_posx) {
            posx--;
	    target.posx--;
            back = true;
         } else {
            back = false;
         }
         posy++;
	 target.posy++;
      } else if(movement == 3) {
         if(posy < (SCREEN_HEIGHT/2) && !back) {
            posy++;
	    target.posy++;
         } else {
            back = true;
            posy--;
	    target.posy--;
         }
      }
   }
   //if(posx > limit_right || posx < limit_left || posy > limit_bottom) {
   if(posx > limit_right || posx < limit_left) {
       printf("deactivated\n");
       active = false;
   }
} 


EnemyProjectile *Enemy::fire_projectile(void) { 
    if(fire_type == FIRETYPEPJTL) {
       if(movement_counter % fire_interval == 0){ 
          int proj_direction;
          if(type == TYPEM1) {
             proj_direction = fire_counter % 3;
          }
	  if(type == TYPEM3) {
             if(posx > SCREEN_WIDTH) {
                proj_direction = 0; // shoots to the left side of screen
	     } else {
	        proj_direction = 2; // shoot to the right side of screen
	     }
          }	
          fire_counter++; 
          return new EnemyProjectile(posx + getWidth()/2, 
                                     posy + getHeight(),  
                                     TYPEM1, proj_direction);
       } else {
          return nullptr;
       }
   } else {
      return nullptr;
   }
}

EnemyMissile *Enemy::fire_missile(void){
   if(fire_type == FIRETYPEMSSL) {
      if(movement_counter % fire_interval == 0) {
         return new EnemyMissile(posx, posy, TYPEMSSL1);  
      }
      return nullptr;
   } else {
      return nullptr;
   }
}
