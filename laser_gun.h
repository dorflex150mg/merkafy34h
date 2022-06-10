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
   int charge;

   LaserGun(void);
   int fireable(void);
   int getWidth(void);
   int getDamage(void);
   int fire(int posx);
   bool isFiring(void);
   void setLevel(int level);
   int getLevel(void);
   int getCharge(void);
   void decreaseCharge(void);
   void increaseCharge(void);
};
#endif
