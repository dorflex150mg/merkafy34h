#ifndef LASER_H_ 
#define LASER_H_

#define LASER_WIDTH	4

class LaserGun{
   public:    
   int damage;
   int posx;
   int posy;
   int w;
   int level;

   LaserGun(void);
   int getWidth(void);
   int getDamage(void);
   int fire(int posx);
   bool isFiring(void);
   void setLevel(int level);
   int getLevel(void);
};
#endif
