#ifndef BUILDING_POS_H_
#define BUILDING_POS_H_

#define NBDNG0	10
#define NBDNG2	15
#define NBDNG4	25
#define NBDNG6	35
#define NBDNG8	45

struct buildings_pos_t{ 
   int x; 
   int scroll;
   int type;
   bool active;
};

//struct buildings_pos_t **buildings_pos;  
//struct buildings_pos_t *buildings_lvl0;
//struct buildings_pos_t *buildings_lvl2;
//struct buildings_pos_t *buildings_lvl4;
//struct buildings_pos_t *buildings_lvl6;
//struct buildings_pos_t *buildings_lvl8;

void init_buildings(int level);
struct buildings_pos_t *get_buildings_pos(int level);
#endif
