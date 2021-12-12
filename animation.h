#include <stdlib.h>

#ifndef ANIMATION_H_
#define ANIMATION_H_

#define TYPEEXPLOSION		1
#define TYPEHIT			2

#define NFRAMESEXPLOSION	4
#define NFRAMESHIT		3

#define SMALLEXPLOSIONPATH      "assets/small_explosion.png"
#define MEDIUMEXPLOSIONPATH     "assets/medium_explosion.png"
#define BIGEXPLOSIONPATH        "assets/big_explosion.png"
#define GREATEXPLOSIONPATH      "assets/great_explosion.png"


#define SMALLHITPATH      	"assets/small_hit.png"
#define MEDIUMHITPATH     	"assets/medium_hit.png"
#define BIGHITPATH        	"assets/big_hit.png"


#define EXPLOSIONW0 		12
#define EXPLOSIONH0 		12

#define EXPLOSIONW1 		32
#define EXPLOSIONH1 		32

#define EXPLOSIONW2 		62
#define EXPLOSIONH2 		62

#define EXPLOSIONW3 		102
#define EXPLOSIONH3 		102

#define HITW0 			8	
#define HITH0 			8	

#define HITW1 			16	
#define HITH1 			20

#define HITW2 			16
#define HITH2 			20

#define CALLSPERFRAMEEXPLOSION	8	
#define CALLSPERFRAMEHIT	8	

class Animation {

   public:
      int posx;
      int posy;
      int type;
      int call_cnt;
      int n_frames;
      int cur_frame;
      int *frames_x;
      int *frames_y;
      int *frames_w;
      int *frames_h;
      bool active;
   
      int explosions_x[4];
      int explosions_y[4];

      
      Animation(int s_posx, int s_posy, int s_type);
      int getnFrames(void);
      int getCurrentFrame(void);
      void updateFrame(void);
      int getFramePosx(int i);
      int getFramePosy(int i);
      int getFrameWidth(int i);
      int getFrameHeight(int i);
      int getCurFramePosx(void);
      int getCurFramePosy(void);
};
#endif
