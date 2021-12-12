#include "target.h"
#include <stdio.h>

int Target::getPosx(){
   return posx;
}

int Target::getPosy(){
   return posy;
}

int Target::getWidth(){
   return w;
}

int Target::getHeight(){
   return h;
}

bool Target::takeDamage(int damage) {
   bool is_dead = false;
   health -= damage;
   printf("Health: %d\n", health);
   if(health <= 0) {
      active = false;
      is_dead = true;
   }
   return is_dead;
}
