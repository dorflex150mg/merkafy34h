#include "laser_gun.h"

LaserGun::LaserGun(){
   damage = 1;
   level = 0;
   w = LASER_WIDTH;
}

int LaserGun::fire(int posy) {
   return posy;
} 

int LaserGun::getWidth(){
   return w;
}

int LaserGun::getDamage() {
   return damage;
}
