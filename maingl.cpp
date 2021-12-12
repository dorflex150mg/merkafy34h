#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <OpenGL/gl3.h>
#include "screen.h"
#include "building_pos.cpp"
#include "building.cpp"
#include "enemy.cpp"
#include "enemy_pos.cpp"
#include "ship.cpp"

#define MAX_PJTL	65536
#define MAX_BDNG	2048
#define MAX_ENMY	4096

const char *TITLE = "Space Epoch";

const char *SHIPPATH = "/Users/gabrielfernandez/dev/ship/assets/f35.png";

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;

Enemy *enemies[MAX_ENMY] = {nullptr};
Projectile *projectiles[MAX_PJTL] = {nullptr};
Building *buildings[MAX_BDNG] = {nullptr};
SDL_Rect projectile_rects[MAX_PJTL];
SDL_Rect building_rects[MAX_BDNG];
SDL_Rect enemy_rects[MAX_ENMY];
SDL_Surface *projectile_surfaces[MAX_PJTL];
SDL_Surface *building_surfaces[MAX_BDNG];
SDL_Surface *enemy_surfaces[MAX_BDNG];
int scroll_speed;
int scroll_val = 0;
int n_projectiles;
int n_buildings = 0;
int n_enemies = 0;
int scroll_slow;
int imgs_index;
int level;
long frame_cnt;


void spawn_enemy(int x, int y, int type, int move) {
   /* in case it n_enemies get greater than MAX_ENMY */
   enemies[n_enemies % MAX_ENMY] = new Enemy(x, y, type, move);
   enemy_rects[n_enemies % MAX_ENMY].h = enemies[n_enemies % MAX_ENMY]->getHeight();
   enemy_rects[n_enemies % MAX_ENMY].w = enemies[n_enemies % MAX_ENMY]->getWidth();
   n_enemies++;

}

void draw_projectile(SDL_Surface *p_surf, SDL_Rect *p_rect) {
   SDL_Surface *loadSurface = IMG_Load((char *) PROJECTILEPATH);
   p_surf = SDL_ConvertSurface(loadSurface, surface->format, 0);
   SDL_FreeSurface(loadSurface); 
   SDL_BlitSurface(p_surf, NULL, surface, p_rect);   
}

void draw_target(const char *icon_path, SDL_Surface *p_surf, SDL_Rect *p_rect) {
   SDL_Surface *loadSurface = IMG_Load((char *) icon_path);
   p_surf = SDL_ConvertSurface(loadSurface, surface->format, 0);
   SDL_FreeSurface(loadSurface); 
   SDL_BlitSurface(p_surf, NULL, surface, p_rect);   
}

void scroll() {
    if(frame_cnt % scroll_slow == 0){ 
       scroll_val += scroll_speed;
    }
    for(int i = 0; i < n_buildings; i++) {
        if(buildings[i] != nullptr) {
           if(buildings[i]->active) {
               if(frame_cnt % scroll_slow == 0) {
                  buildings[i]->posy += scroll_speed;
               }
           }
       }
   }
}

void setStartPosition(SDL_Rect *rect, int width, int height) {
   rect->x = SCREEN_WIDTH/2 - width/2;
   rect->y = SCREEN_HEIGHT - height;
}

inline void checkHitBuildings(Projectile *p, Building *targets[], int n_targets){
   for(int j = 0; j < n_targets; j++) {
      if(targets[j] != nullptr && targets[j]->active)  {
         if(p->getPosx() > targets[j]->getPosx() &&
           p->getPosx() < targets[j]->getPosx() + 
           targets[j]->getWidth() && 
           p->getPosy() > targets[j]->getPosy() && 
           p->getPosy() < targets[j]->getPosy() + 
           targets[j]->getHeight()){
              targets[j]->takeDamage(p->getDamage());
              printf("%s%d%s%d\n", "target ", j, " hp ",  targets[j]->health);
              p->active = false;
         }   
      }
   }
}


inline void checkHitEnemies(Projectile *p, Enemy *targets[], int n_targets){
   for(int j = 0; j < n_targets; j++) {
      if(targets[j] != nullptr && targets[j]->active)  {
         if(p->getPosx() > targets[j]->getPosx() &&
           p->getPosx() < targets[j]->getPosx() + 
           targets[j]->getWidth() && 
           p->getPosy() > targets[j]->getPosy() && 
           p->getPosy() < targets[j]->getPosy() + 
           targets[j]->getHeight()){
              targets[j]->takeDamage(p->getDamage());
              printf("%s%d%s%d\n", "target ", j, " hp ",  targets[j]->health);
              p->active = false;
         }   
      }
   }
}

void update(Ship ship, SDL_Rect *rect){
   /* updating incoming buildings */
   for(int i = 0; i < sizeof(buildings_pos)/sizeof(struct buildings_pos_t); i++) {
      if(buildings_pos[i].active) {
         int diff = scroll_val + buildings_pos[i].scroll;
         if(diff > 0) {
            buildings[i] = new Building(buildings_pos[i].x, diff, buildings_pos[i].type);
            building_rects[i].w = buildings[i]->getWidth(); 
            building_rects[i].h = buildings[i]->getHeight(); 
            n_buildings++;
            buildings_pos[i].active = false;
         }
      } 
   }
   /* updating buildings in screen */
   for(int i = 0; i < n_buildings; i++) {
      if(buildings[i] != nullptr) {
         if(buildings[i]->active){
            building_rects[i].x = buildings[i]->getPosx();       
            building_rects[i].y = buildings[i]->getPosy();
            if(buildings[i]->getPosy() > SCREEN_HEIGHT) {
               buildings[i]->active = false;
            }
         }
      }      
   }
   scroll();
   /* updating incoming enemies */
   for(int i = 0; i < sizeof(enemies_pos)/sizeof(struct enemy_pos_t); i++) {
      if(enemies_pos[i].active) {
         int diff = scroll_val + enemies_pos[i].scroll;
         if(diff > 0) {
            spawn_enemy(enemies_pos[i].x, diff, enemies_pos[i].type, enemies_pos[i].move);
            enemies_pos[i].active = false;
         }
      } 
   }
   /* updating enemies on screen */
   for(int i = 0; i < n_enemies; i++) {
       if(enemies[i]->active) {
           enemies[i]->move();
           enemy_rects[i].x = enemies[i]->getPosx();
           enemy_rects[i].y = enemies[i]->getPosy();
           if(enemies[i]->getPosy() > SCREEN_HEIGHT) {
               printf("deactivated on update\n");
               enemies[i]->active = false;
           }
       } 
   }
   /* updating projectiles */
   for(int i = 0; i < n_projectiles; i++){
      if(projectiles[i]->active){
         projectiles[i]->move();
         projectile_rects[i].x = projectiles[i]->getPosx();
         projectile_rects[i].y = projectiles[i]->getPosy();
         /* checking for projectile hits on buildings */
         
         checkHitBuildings(projectiles[i], buildings, n_buildings);
         checkHitEnemies(projectiles[i], enemies, n_enemies); 
      }
      if(projectiles[n_projectiles - 1] == NULL) {
         n_projectiles--;
      }
   }
   /* updating ship */
   rect->x = ship.getPosx();
   rect->y = ship.getPosy();
}

void draw(SDL_Surface *surface, SDL_Surface *optSurface, SDL_Rect *texr, SDL_Window *window){
   SDL_FillRect(surface, NULL, 0x00);
   for(int i = 0; i < n_projectiles; i++) {
      if(projectiles[i]->active) {
         draw_projectile(projectile_surfaces[i], &projectile_rects[i]);
      }
   }
   for(int i = 0; i < n_buildings; i++) {
      if(buildings[i] != nullptr) {
         if(buildings[i]->active) {
            draw_target(buildings[i]->icon_path, building_surfaces[i], &building_rects[i]);
         }
      }
   }
   for(int i = 0; i < n_enemies; i++) {
      if(enemies[i] != nullptr) {
         if(enemies[i]->active) {
            draw_target(enemies[i]->icon_path, enemy_surfaces[i], &enemy_rects[i]);
         }
      }
   }
   SDL_BlitSurface(optSurface, NULL, surface, texr);
   SDL_BlitSurface(optSurface, NULL, surface, texr);
   //glClearColor(1.0f, 0.0, 0.0, 1.0);
   //glClear(GL_COLOR_BUFFER_BIT);
   SDL_UpdateWindowSurface(window);
}


int main(int argc, char* args[]) {
   SDL_Surface *optSurface = NULL;
   SDL_Surface *image = NULL;
   SDL_Texture *img = NULL;
   SDL_Texture *projectile = NULL;
   SDL_Rect texr;
   Ship ship;
   frame_cnt = 0l;
   scroll_speed = 1;
   scroll_slow = 8;
   
   if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("%s\n", "Unable to initialize SDL");
      exit(1);
   }
   window = SDL_CreateWindow(TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
   if(window == NULL) {
      printf("%s\n", "Unable to create window");
      exit(1);
   }
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GLContext glContext = SDL_GL_CreateContext(window);
   
   int imgFlags = IMG_INIT_PNG;
   if(!(IMG_Init(imgFlags) & imgFlags)) {
      printf("Unable to load image");
      exit(1);
   }
   //surface = SDL_GetWindowSurface(window);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   image = IMG_Load((char *) SHIPPATH);
   glEnable(GL_TEXTURE_2D);
   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, 
                  GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, 
                  GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, 
                image->format->BytesPerPixel, 
                image->w, image->h, 
                0, GL_RGB, GL_RGB, 
                GL_UNSIGNED_BYTE, image->pixels);
  
   glOrtho(0, 640, 480, 0, -1, 1);
   glClearColor(1, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1, 1, 1);
   glBindTexture(GL_TEXTURE_2D, texture);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0);
   glVertex3f(0, 0, 0);
   glTexCoord2f(1, 0);
   glVertex3f(30, 0, 0);
   glTexCoord2f(1, 1);
   glVertex3f(30, 50, 0);
   glTexCoord2f(0, 1);
   glVertex3f(0, 50, 0);
   glEnd();
    
   //SDL_GL_SwapWindow(window);
   //SDL_Delay(5000);
   optSurface = SDL_ConvertSurface(loadSurface, surface->format, 0);
   //SDL_FreeSurface(loadSurface); 
   bool quit = false;
   ship.setStartPosition();
   init_buildings();
   init_enemies();
   while(!quit) {
      frame_cnt++;
      SDL_Event e;
      const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
      while(SDL_PollEvent(&e)) {
         if (keyboard_state_array[SDL_SCANCODE_UP]) {
            ship.goUp();
         }
         else if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
            ship.goDown();
         }
     
         if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
            ship.goRight();
         }
         else if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
            ship.goLeft();
         }
         else if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
            quit = true;
         }
         if(keyboard_state_array[SDL_SCANCODE_SPACE]) {
            /* case it overflows (unlikely though) */
            projectiles[n_projectiles % MAX_PJTL] = ship.fire();
            n_projectiles++;
         }
      }
      //update(ship, &texr);
      //draw(surface, optSurface, &texr, window);
   }
   SDL_DestroyWindow(window);
   SDL_Quit();
   return 0; 
}
