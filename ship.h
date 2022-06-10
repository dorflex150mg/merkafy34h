#ifndef SHIP_H_
#define SHIP_H_
#include "screen.h"
#include "projectile.h"
#include "enemy.h"
#include "enemy_missile.h"
#include "laser_gun.h"

#define SHIP_WIDTH	48
#define SHIP_HEIGHT	80
#define MAX_HEALTH	100

#define SHIPPATH 	"assets/f35.png"
#define SHIPPATHL 	"assets/f35l.png"
#define SHIPPATHR 	"assets/f35r.png"

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
      LaserGun *laser_gun;

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
      char *getIconPathRight(void);
      char *getIconPathLeft(void);
      int getCenterPosx(void);
      int getCenterPosy(void);
      void takeDamage(int damage);
      int getHealth(void);
      bool checkCollision(Enemy *enemy);
      bool checkCollisionMissile(EnemyMissile *enemy);
      bool hasLaserGun(void);
      LaserGun *getLaserGun(void);
      Projectile *fire(void);
};
#endif
