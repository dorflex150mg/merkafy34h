#include <stdio.h>
#include <stdlib.h>
#include "animation.h"

Animation::Animation(int s_posx, int s_posy, int s_type){
   posx = s_posx;
   posy = s_posy;
   type = s_type;
   cur_frame = 0; 
   call_cnt = 0;
   active = true;
   switch(type) {
      case TYPEEXPLOSION:
         n_frames = NFRAMESEXPLOSION;
         frames_x = (int*) malloc(sizeof(int) * n_frames);
         frames_y = (int*) malloc(sizeof(int) * n_frames);
         frames_w = (int*) malloc(sizeof(int) * n_frames);
         frames_h = (int*) malloc(sizeof(int) * n_frames);

         frames_w[0] = EXPLOSIONW0;
         frames_h[0] = EXPLOSIONH0;
            
         frames_w[1] = EXPLOSIONW1;
         frames_h[1] = EXPLOSIONH1;
            
         frames_w[2] = EXPLOSIONW2;
         frames_h[2] = EXPLOSIONH2;
            
         frames_w[3] = EXPLOSIONW3;
         frames_h[3] = EXPLOSIONH3;
         break;
      case TYPEHIT:
         n_frames = NFRAMESHIT;
         frames_x = (int*) malloc(sizeof(int) * n_frames);
         frames_y = (int*) malloc(sizeof(int) * n_frames);
         frames_w = (int*) malloc(sizeof(int) * n_frames);
         frames_h = (int*) malloc(sizeof(int) * n_frames);

         frames_w[0] = HITW0;
         frames_h[0] = HITH0;
            
         frames_w[1] = HITW1;
         frames_h[1] = HITH1;
            
         frames_w[2] = HITW2;
         frames_h[2] = HITH2;
         printf("hit created\n");
         break;
      default:
         n_frames = NFRAMESEXPLOSION;
         frames_x = (int*) malloc(sizeof(int) * n_frames);
         frames_y = (int*) malloc(sizeof(int) * n_frames);
         frames_w = (int*) malloc(sizeof(int) * n_frames);
         frames_h = (int*) malloc(sizeof(int) * n_frames);
         break;
   }
}

int Animation::getnFrames(void){
   return n_frames;
}

int Animation::getCurrentFrame(void){
   return cur_frame;
}

void Animation::updateFrame(void){
   call_cnt++;
   if(type == TYPEEXPLOSION) {
      if(call_cnt % CALLSPERFRAMEEXPLOSION == 0) { 
         cur_frame++;
      }
   }
   if(type == TYPEHIT) {
      if(call_cnt % CALLSPERFRAMEHIT == 0) { 
         printf("hit frame updated\n");
         cur_frame++;
      }
   }
   
   if(cur_frame >= n_frames) {
      cur_frame = 0;
      active = false;
   }
}

int Animation::getFramePosx(int i) {
   return posx;
}

int Animation::getFramePosy(int i) {
   return frames_y[i];
}

int Animation::getFrameWidth(int i) {
   return frames_w[i];
}

int Animation::getFrameHeight(int i) {
   return frames_h[i];
}

int Animation::getCurFramePosx(void){
   return posx - (frames_w[cur_frame]/2); 
}

int Animation::getCurFramePosy(void){
   return posy - (frames_h[cur_frame]/2); 
}
