#pragma once

#ifndef BUILDING_H_
#define BUILDING_H_

#include "boss.h" 
#include "enemy_projectile.h"
#include "enemy_missile.h"

#define SAMPATH			"assets/sam.png"
#define SAMW			50
#define	SAMH			40
#define SAMHEALTH		40
#define TYPESAM			1
#define SAMFIREINTV		300

#define AAGUNPATH		"assets/aagun1.png"
#define AAGUNW			40
#define	AAGUNH			40
#define AAGUNHEALTH		40
#define TYPEAAGUN		2
#define AAGFIREINTV		40
#define AAGSPREADDIRECTIONS 	3


#define FIRETYPEPTJL		1
#define FIRETYPEMSSL		2


class Building : public Target {
   public:
      int type;
      int fire_counter;
      int fire_interval;
      int fire_direction_counter;
      int fire_direction;
      const char *icon_path;

      Building(int s_posx, int s_posy, int s_type);
      int getFireType(void);
      EnemyMissile *fireMissile(void);
      EnemyProjectile *fireProjectile(int ship_posx, int ship_posy); 
};      
#endif
