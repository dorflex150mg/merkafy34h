#include <stdio.h>
#include <stdlib.h>

#include "background.h"

Background::Background(int type) {
   switch(type) {
      case BG00:
         icon_path = (char *) BGPATH00;
         break;
      case BG01:
         icon_path = (char *) BGPATH00;
         break;
      case BG10:
         icon_path = (char *) BGPATH00;
         break;
      default:
         icon_path = (char *) BGPATH00;
         break;
   }
}

char *Background::getPath(void){
   return icon_path;
}
