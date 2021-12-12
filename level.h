#ifndef LEVEL_H_
#define LEVEL_H_

#include "themes.h"
#include "boss.h"
#include "level_data.h"

class Level {
   public:
      char *theme_path;
      int n_level;
      int length;
      int finished;
      int n_buildings;
      int n_enemies;
      bool is_boss;
      Boss *boss;

   Level(int s_n_level);
   char *getThemePath(void);
   int getLength(void);
   int getLevel(void);
   int finish(void);
   int getnBuildings(void);
   int getnEnemies(void);
   bool isBossLevel(void);
   Boss *getBoss(void);
};
#endif
