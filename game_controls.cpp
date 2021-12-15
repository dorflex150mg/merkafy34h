#include <SDL2/SDL_mixer.h>

#define ALLSOUNDCHANNELS	-1

bool sound_on = true;
int counter = 0;

void switch_sound(void) {
   counter++;
   if(counter % 2 == 0) {
       sound_on = !sound_on; 
       printf("%s%d\n", "Toggling sound ", counter);
   }
   if(sound_on) {
       Mix_VolumeMusic(MIX_MAX_VOLUME);
   } else {
       printf("turning off sound\n");
       Mix_VolumeMusic(0);
   }
}
