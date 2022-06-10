#include "ship.h"
#include "screen.h"
#include "projectile.h"
#include "enemy.h"
#include <stdio.h>

Ship::Ship(void) {
   posx = 0;
   posy = 0;
   w = SHIP_WIDTH;
   h = SHIP_HEIGHT;
   speed = 20;
   max_health = MAX_HEALTH;
   cur_health = max_health; 
   god_mode = true;
   laser_gun = new LaserGun();
   printf("%s\n", "ship created");
}

int Ship::getPosx(void){
    return posx;
}

int Ship::getPosy(void){
    return posy;
}

int Ship::getWidth(void){
   return w;
}

int Ship::getHeight(void){
   return h;
}

void Ship::setStartPosition(void) {
   posx = SCREEN_WIDTH/2 - SHIP_WIDTH/2;
   posy = SCREEN_HEIGHT - SHIP_HEIGHT;
}


void Ship::goLeft(void){
    if(posx > 0) {
        posx -= speed;
    }
    if(posx <= 0) {
        posx = 0;
    }
}


void Ship::goRight(void){
    int limit = SCREEN_WIDTH - SHIP_WIDTH;
    if(posx < limit) {
        posx += speed;
    }
    if(posx >= limit) {
        posx = limit;
    }
}


void Ship::goUp(void){
    if(posy > 0) {
        posy -= speed;
    }
    if(posy <= 0) {
        posy = 0;
    }
}


void Ship::goDown(void){
    int limit = SCREEN_HEIGHT - SHIP_HEIGHT;
    if(posy < limit) {
        posy += speed;
    }
    if(posy >= limit) {
        posy = limit;
    }
}

char *Ship::getIconPath(void) {
   return (char*) SHIPPATH;
}


char *Ship::getIconPathLeft(void) {
   return (char*) SHIPPATHL;
}

char *Ship::getIconPathRight(void) {
   return (char*) SHIPPATHR;
}

int Ship::getCenterPosx(void){
   return posx + SHIP_WIDTH/2;
}

int Ship::getCenterPosy(void){
   return posy + SHIP_HEIGHT/2;
}

void Ship::takeDamage(int damage){
   if(!god_mode) {
      cur_health -= damage;
   }
   if(cur_health == 0) {
      printf("%s\n", "dead");
   }
}

int Ship::getHealth(void){
   return cur_health;
}

bool Ship::checkCollision(Enemy *enemy) {
   /* check if the x and width coincide
   if not, return false already */
   if(!((posx < enemy->getPosx() && posx + w > enemy->getPosx()) ||
     (posx > enemy->getPosx() && posx < enemy->getPosx() + enemy->getWidth()))) {
      return false;
   }
   /* the same here for y and height*/
   if(!((posy < enemy->getPosy() &&
     posy + h > enemy->getPosy()) ||
     (posy > enemy->getPosy() &&
     posy < enemy->getPosy() + enemy->getHeight()))) {
      return false;
   }
   /* if both x and y coincide, then there's a collision */
   return true; 
}

bool Ship::checkCollisionMissile(EnemyMissile *enemy) {
   /* check if the x and width coincide
   if not, return false already */
   if(!((posx < enemy->getPosx() && posx + w > enemy->getPosx()) ||
     (posx > enemy->getPosx() && posx < enemy->getPosx() + enemy->getWidth()))) {
      return false;
   }
   /* the same here for y and height*/
   if(!((posy < enemy->getPosy() &&
     posy + h > enemy->getPosy()) ||
     (posy > enemy->getPosy() &&
     posy < enemy->getPosy() + enemy->getHeight()))) {
      return false;
   }
   /* if both x and y coincide, then there's a collision */
   return true; 
}

bool Ship::hasLaserGun(void) {
   //TODO: false until the correct pick up gets picked
   return true;
}

LaserGun *Ship::getLaserGun(void) {
   return laser_gun;
}

Projectile *Ship::fire(void){
   int x_start = posx;
   return new Projectile(x_start, posy);
}       
