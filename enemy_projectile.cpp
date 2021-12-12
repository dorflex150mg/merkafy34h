#include "enemy_projectile.h"

EnemyProjectile::EnemyProjectile(int s_posx, int s_posy, int s_type, int s_direction){
   type = s_type;
   switch(type) {
      case 1:
         icon_path = (char*) ENEMYPROJECTILEPATH1;
         speed = TYPE_1_SPEED;
         damage = TYPE_1_DMG;
         w = TYPE_1_WIDTH;
         h = TYPE_1_HEIGHT;
         break;
      default:
         icon_path = (char*) ENEMYPROJECTILEPATH1;
         speed = TYPE_1_SPEED;
         damage = TYPE_1_DMG;
         break;
   }
   /* perhaps used later */
   counter = 0;
   direction = s_direction;
   posx = s_posx;
   posy = s_posy;
   active = true;
 }

int EnemyProjectile::getPosx(){
   return posx;
}

int EnemyProjectile::getPosy(){
   return posy;
}

int EnemyProjectile::getWidth(){
   return w;
}

int EnemyProjectile::getHeight(){
   return h;
}

void EnemyProjectile::move(void) {
   switch(type) {
      case TYPE_1:
         if(posy > 0) {
            posy += speed;
            /* if direction == 1, the projectile goes straight */
            if(direction == 0) {
               posx++;
            } else if(direction == 2) {
               posx--;
            }                
         } else {
            /* projectile gets inactive when it goes offscreen */
            active = false;
         }
      case TYPE_2:
        switch(direction) {
           /* quadrant 1: 0 to 2. 0 to 90 degrees */
           case 0:
              posx+=2;
              posy++;
              break;
           case 1:
              posx++;
              posy++;
              break;
           case 2:
              posx++;
              posy+=2;
              break;
           /* quadrant 2: 3 to 5. 90 to 180 degrees */
           case 3:
              posx--;
              posy+=2; 
              break;
           case 4:
              posx--;
              posy++;
              break;
           case 5:
              posx-=2;
              posy++;
              break;
           /* quadrant 3: 6 to 8. 180 to 270 degrees */
           case 6:
              posx-=2;
              posy--;
              break;
           case 7:
              posx--;
              posy--;
              break;
           case 8:
              posx--;
              posy-=2;
              break;
           /* quadrant 4: 9 to 11. 270 to 360 degrees */
           case 9:
              posx++;
              posy-=2;
              break;
           case 10:
              posx++;
              posy--;
              break;
           case 11:
              posx+=2;
              posy--;
              break;
      }
   }
}

int EnemyProjectile::getDamage() {
   return damage;
}
