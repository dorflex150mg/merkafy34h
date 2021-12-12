#include "projectile.h"

//Projectile::Projectile(){}

Projectile::Projectile(int s_posx, int s_posy){
   speed = 30;
   damage = 5;
   posx = s_posx;
   posy = s_posy;
   length = 1;
   height = 1;
   type = 1;
   w = PROJECTILE_WIDTH;
   h = PROJECTILE_HEIGHT;
   active = true;
 }

int Projectile::getPosx(){
   return posx;
}

int Projectile::getPosy(){
   return posy;
}

int Projectile::getWidth(){
   return w;
}

int Projectile::getHeight(){
   return h;
}

void Projectile::move() {
   if(posy > 0) {
      posy -= speed;
   } else {
      active = false;
  }
}

int Projectile::getDamage() {
   return damage;
}
