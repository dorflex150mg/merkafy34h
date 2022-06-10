#ifndef LEVEL_H_
#define LEVEL_H_

#include "themes.h"
#include "boss.h"
#include "level_data.h"
#include "background.h"

class Level {
   public:
      char *theme_path;
      char **bg_paths;
      int n_level;
      int length;
      int finished;
      int n_buildings;
      int n_enemies;
      bool is_boss;
      Background **bgs;
      Background *cur_bg;
      Background *next_bg;
      Boss *boss;

   Level(int s_n_level);
   char *getThemePath(void);
   char **getBgPaths(void);
   int getLength(void);
   int getLevel(void);
   int getnBuildings(void);
   int getnEnemies(void);
   bool isBossLevel(void);
   void finish(void);
   Background *getCurBg();
   Background *getNextBg();
   Boss *getBoss(void);
};
#endif
