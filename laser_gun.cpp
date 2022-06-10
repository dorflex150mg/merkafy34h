#include "laser_gun.h"

LaserGun::LaserGun(){
   damage = 1;
   level = 0;
   charge = 100;
   w = LASER_WIDTH;
}

int LaserGun::fireable(void) {
   if(charge <= 0) {
      return 0;
   }
   return 1;
} 

int LaserGun::getWidth(){
   return w;
}

int LaserGun::getDamage() {
   return damage;
}

int LaserGun::getCharge(void) {
   return charge;
}

void LaserGun::decreaseCharge(void) {
   charge -= 1;
}

void LaserGun::increaseCharge(void) {
   if(charge < 100) {
      charge += 1;
   }
}
