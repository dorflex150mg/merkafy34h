#include <stdio.h>
#include "target.h"
#include "enemy_missile.h"
#include "screen.h"
#include "maths.h"

EnemyMissile::EnemyMissile(int s_posx, int s_posy, int s_type){
   angle = 0;
   movement_counter = 0;
   track_interval = 0;
   posx = s_posx;
   posy = s_posy;
   last_movex = 0;
   last_movey = 0;
   health = 5;      
   target.health = 5;
   init_posx = s_posx;
   init_posy = s_posy;
   active = true;
   type = s_type;
   switch(type) {
      case TYPEMSSL1:
         icon_path = ICONMSSL1;
         h = HEIGHTMSSL1;
         w = WIDTHMSSL1;
         speed = SPEEDMSSL1;
         damage = DMGMSSL1;
	 track_interval = TRACKINTERVALMSSL1;
         break;
      default:
         icon_path = ICONMSSL1;
         h = HEIGHTMSSL1;
         w = WIDTHMSSL1;
         speed = SPEEDMSSL1;
         damage = DMGMSSL1;
         break;
   }
   /* Whole figure must leave screen to be off bounds, thus y < -h
   and x < -w */
   limit_top = -h;
   limit_left = -w;
}

Target *EnemyMissile::getTarget(void) {
   return &target;
}

int EnemyMissile::getHitBoxPosx(void){
   return posx - (w - (HITBOXWIDTH/2)); 
}

int EnemyMissile::getHitBoxWidth(void){
   return HITBOXWIDTH - (w - (HITBOXWIDTH/2));
}   

int EnemyMissile::getDamage(void){
    return damage;
}

void EnemyMissile::move(int ship_posx, int ship_posy){
   movement_counter++;
   if(movement_counter % track_interval == 0) { // every track interval, go towards the ship  
      /* MAX_SLOW is 10, which is the minimum speed (1 pixel every 10 move calls) */
      if(posx < ship_posx){
         posx++;
         last_movex = 1;	 
      } else {
         posx--;
	 last_movex = 0;
      }
      if(posy < ship_posy) {
          posy++;
          last_movey = 1;
      } else {
          posy--;
	  last_movey = 0;
      }
   } else { // if it is not track interval, keep moving in the same direction
      if(last_movex) {
         posx++;
      } else {
	 posx--;
      }
      if(last_movey) {
         posy++;
      } else {
	 posy--;
      } 
   }
} 

void EnemyMissile::calculateAngle(int ship_posx, int ship_posy) {
   int dist_x = ship_posx - posx; 
   int dist_y = ship_posy - posy;
   angle = get_angle_from_catets(dist_y, dist_x);
   if(ship_posx < posx) {
      angle -= 180;
      printf("!\n");
   } 
}

int EnemyMissile::calculateRectWidth(void) {
   /* the sum of the oposite catets from the triangles formed
    * by the width and height of the texture and the box
    * is the boxes width. */
   double oposite_large = get_oposite_catet(angle, h); 
   double oposite_small = get_oposite_catet(90 - angle, w); //complement angle
   return (int) oposite_large + oposite_small;
}


int EnemyMissile::calculateRectHeight(void) {
   /* the sum of the adjacent catets from the triangles formed
    * by the width and height of the texture and the box
    * is the boxes height. */
   double adjacent_large = get_adjacent_catet(angle, h); 
   double adjacent_small = get_adjacent_catet(90 - angle, w); //complement angle
   return (int) adjacent_large + adjacent_small;
}

int EnemyMissile::getCenterPosx(void) {
   return posx + h/2;
}

int EnemyMissile::getCenterPosy(void) {
   return posy + w/2;
}

int EnemyMissile::getAngle(void) {
   return (int) angle;
}

