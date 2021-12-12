#ifndef TARGET_H_
#define TARGET_H_

class Target {
   public:
      int health;
      int posx;
      int posy;
      int w;
      int h;
      bool active;   

      int getPosx(void);
      int getPosy(void);
      int getWidth(void);
      int getHeight(void);
      bool takeDamage(int damage);
};
#endif
