#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#define PROJECTILEPATH		"assets/projectile1.png"
#define PROJECTILEBALLPATH	"assets/ball.png"
#define PROJECTILE_HEIGHT	18
#define PROJECTILE_WIDTH	10

class Projectile {
   public:    
   int speed;
   int damage;
   int posx;
   int posy;
   int h;
   int w;
   int length;
   int height;
   int type;
   bool active;

   Projectile(int s_posx, int s_posy);
   int getPosx(void);
   int getPosy(void);
   int getWidth(void);
   int getHeight(void);
   void move(void);
   int getDamage(void);
};
#endif
