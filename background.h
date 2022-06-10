#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#define BGPATH00		"assets/bg1.png"		
#define BGPATH01		"assets/bg1.png"
#define BGPATH10		"assets/bg1.png"

#define BG00			1
#define BG01			2
#define BG10			3

#define N_BG0			2

class Background {
   public:
      char *icon_path;
      int w;
      int h;
      int x;
      int y;
      Background(int type); 
      char *getPath();

};
#endif
