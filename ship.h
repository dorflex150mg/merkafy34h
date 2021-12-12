#ifndef SHIP_H_
#define SHIP_H_
#include "screen.h"
#include "projectile.h"
#include "enemy.h"
#include "enemy_missile.h"

#define SHIP_WIDTH	48
#define SHIP_HEIGHT	80
#define MAX_HEALTH	100

#define SHIPPATH 	"assets/f35.png"

class Ship {

   public:
      int posx;
      int posy;
      int w;
      int h;
      int speed;
      int max_health;
      int cur_health;
      bool god_mode;

      Ship(void);
      int getPosx(void);
      int getPosy(void);
      int getWidth(void);
      int getHeight(void);
      void setStartPosition(void);
      void goLeft(void);
      void goRight(void);
      void goUp(void);
      void goDown(void);
      char *getIconPath(void);
      int getCenterPosx(void);
      int getCenterPosy(void);
      void takeDamage(int damage);
      int getHealth(void);
      bool checkCollision(Enemy *enemy);
      bool checkCollisionMissile(EnemyMissile *enemy);
      Projectile *fire(void);
};
#endif
