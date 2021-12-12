#include <stdlib.h>
#include "building.h"
#include "boss.h" 

Building::Building(int s_posx, int s_posy, int s_type) {
   posx = s_posx;
   posy = s_posy;
   active = true;
   type = s_type;
   switch(type) {
      case TYPESAM:
         icon_path = SAMPATH;
         w = SAMW;
         h = SAMH;
         health = SAMHEALTH;
         fire_interval = SAMFIREINTV;
         break;
      case TYPEAAGUN:
         icon_path = AAGUNPATH;
         w = AAGUNW;
         h = AAGUNH;
         health = AAGUNHEALTH;
         fire_interval = AAGFIREINTV;
      default:
         icon_path = SAMPATH;
         w = SAMW;
         h = SAMH;
         health = SAMHEALTH;
         fire_interval = SAMFIREINTV;
         break;
   }
}

int Building::getFireType(void) {
   if(type == TYPESAM) {
      return 2;
   } else if(type == TYPEAAGUN) {
      return FIRETYPEPTJL;
   }
}

EnemyMissile *Building::fireMissile(void){ 
   fire_counter++;
   switch(type) {
      case TYPESAM: 
         if(fire_counter % fire_interval == 0) {
            return new EnemyMissile(posx, posy, TYPEMSSL1);  
         }
         break;
      default:
         return nullptr;
   }
}

EnemyProjectile *Building::fireProjectile(int ship_posx, int ship_posy){ 
   fire_counter++;
   switch(type) {
      case TYPEAAGUN:
         /* this counter is used to change the gun's direction
         and provide spread */
         fire_direction_counter++;
         if(fire_counter % fire_interval == 0) {
            /* movements are 1 to 12. The AAgun locks onto the right quadrant
            and shoots in each fire_direction WITHIN the quadrant (3 each quadrant).
            That is called the "spread" */
            int spread_fire_direction = fire_direction_counter % AAGSPREADDIRECTIONS;
            /* quadrant 1 */
            if(ship_posx >= posx && ship_posy >= posy) {
               fire_direction += 0;
            /* quadrant 2 */
            } else if(ship_posx <= posx && ship_posy >= posy) {
               fire_direction += 3;
            } else if(ship_posx <= posx && ship_posy <= posy) {
               fire_direction += 6;
            } else {
               fire_direction += 9;
            }
            return new EnemyProjectile(posx, posy, 1, fire_direction);  
         }
         break;
      default:
         return nullptr;
   }
}
