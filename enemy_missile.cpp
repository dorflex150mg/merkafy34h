#include "target.h"
#include "enemy_missile.h"
#include "screen.h"

EnemyMissile::EnemyMissile(int s_posx, int s_posy, int s_type){
   movement_counter = 0;
   posx = s_posx;
   posy = s_posy;
   health = 5;      
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
    /* MAX_SLOW is 10, which is the minimum speed (1 pixel every 10 move calls) */
     if(posx < ship_posx){
        posx++;
     } else {
        posx--;
     }
     if(posy < ship_posy) {
         posy++;
     } else {
         posy--;
     }
} 
