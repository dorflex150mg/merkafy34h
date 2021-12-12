#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "screen.h"
#include "info_components.h"
#include "building.h"
#include "level.h"
#include "level_data.h"

#include "ship.h"
#include "animation.h"
#include "boss.h"
#include "enemy_pos.h"
#include "building_pos.h"
#include "building_pos_data.h"

#define MAXPJTL			65536
#define MAXBDNG			1024
#define MAXENMY			1024
#define MAXMSSL			256
#define MAXANMN			1024
#define G_O_BLIT_MS		200
#define MAXLVL			10

#define FRAMERULE	21

#define FIREPJTLTYPE	1
#define FIREMSSLTYPE	2
#define FIREBEAMTYPE	3

const char *TITLE = "Space Epoch";


/* SDL data structures */
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *img_ship = NULL;

/*SDL_mixer data structures */
Mix_Music *themes[NLEVELS] = {nullptr};
Mix_Chunk *shipFireProj = NULL;
Mix_Chunk *shipFireMssl = NULL;
Mix_Chunk *enemyFireProj = NULL;
Mix_Chunk *enemyFireMssl = NULL;

/* entity object pointers */
Enemy *enemies[MAXENMY] = {nullptr};
Building *buildings[MAXBDNG] = {nullptr};
Projectile *projectiles[MAXPJTL] = {nullptr};
EnemyProjectile *enemyProjectiles[MAXPJTL] = {nullptr};
EnemyMissile *enemyMissiles[MAXMSSL] = {nullptr};
Animation *explosions[MAXANMN] = {nullptr};
Animation *hits[MAXANMN] = {nullptr};
MovementStrategy *test[10] = {nullptr};

/* Placeholder boss. I wish there was a better way */
Boss *boss = new Boss(TYPEBOSS1); 

/* rectangles to orient drawing for each entity */
SDL_Rect enemy_rects[MAXENMY];
SDL_Rect building_rects[MAXBDNG];
SDL_Rect projectile_rects[MAXPJTL];
SDL_Rect enemy_projectile_rects[MAXPJTL];
SDL_Rect enemy_missile_rects[MAXMSSL];
SDL_Rect boss_rect;

/* drawable surfaces for each entity */
SDL_Texture *enemy_imgs[MAXENMY];
SDL_Texture *building_imgs[MAXBDNG];
SDL_Texture *projectile_imgs[MAXPJTL];
SDL_Texture *enemy_projectile_imgs[MAXPJTL];
SDL_Texture *enemy_missile_imgs[MAXMSSL];
SDL_Texture *boss_img;


/*drawable surfaces for each boss */

/* animation sprites texture and rectangles */
SDL_Rect explosionsFrames[MAXANMN][NFRAMESEXPLOSION];
SDL_Texture *small_explosion;
SDL_Texture *medium_explosion;
SDL_Texture *big_explosion;
SDL_Texture *great_explosion;

SDL_Rect hitFrames[MAXANMN][NFRAMESHIT];
SDL_Texture *small_hit;
SDL_Texture *medium_hit;
SDL_Texture *big_hit;

SDL_Texture *explosionTextures[NFRAMESEXPLOSION];
SDL_Texture *hitTextures[NFRAMESEXPLOSION];

/* info rectangles */
SDL_Rect margin_health_bar;
SDL_Rect inner_health_bar;

Level *levels[MAXLVL];
Level *cur_level;

int scroll_speed;
int scroll_val = 0;
int n_projectiles = 0;
int n_enemy_projectiles = 0;
int n_enemy_missiles = 0;
int n_buildings = 0;
int n_enemies = 0;
int n_explosions = 0;
int n_hits = 0;
int scroll_slow;
int imgs_index;
long frame_cnt;

void init_animations() {
   small_explosion = IMG_LoadTexture(renderer, SMALLEXPLOSIONPATH);
   explosionTextures[0] = small_explosion;
   medium_explosion = IMG_LoadTexture(renderer, MEDIUMEXPLOSIONPATH);
   explosionTextures[1] = medium_explosion;
   big_explosion = IMG_LoadTexture(renderer, BIGEXPLOSIONPATH);
   explosionTextures[2] = big_explosion;
   great_explosion = IMG_LoadTexture(renderer, GREATEXPLOSIONPATH);
   explosionTextures[3] = great_explosion;
   
   small_hit = IMG_LoadTexture(renderer, SMALLHITPATH);
   hitTextures[0] = small_hit;
   medium_hit = IMG_LoadTexture(renderer, MEDIUMHITPATH);
   hitTextures[1] = medium_hit;
   big_hit = IMG_LoadTexture(renderer, BIGHITPATH);
   hitTextures[2] = big_hit;
}

void create_explosion(int posx, int posy, int width, int height, int type){
   int center_x = posx + (width/2);
   int center_y = posy + (height/2);
   explosions[n_explosions] = new Animation(center_x, center_y, type);
   /* setting animation frames positions according to the frame size and position */
   for(int i = 0; i < explosions[n_explosions]->getnFrames(); i++) {
      explosionsFrames[n_explosions][i].x = center_x - ((explosions[n_explosions]->frames_w[i])/2);
      explosionsFrames[n_explosions][i].y = center_y - ((explosions[n_explosions]->frames_h[i])/2);
      explosionsFrames[n_explosions][i].w = explosions[n_explosions]->frames_w[i];
      explosionsFrames[n_explosions][i].h = explosions[n_explosions]->frames_h[i];
   }
   n_explosions++;
}

void create_boss_explosions(Boss *boss) {
    create_explosion(boss->getPosx(), boss->getPosy(), boss->getWidth(), boss->getHeight(), TYPEEXPLOSION);
    create_explosion(boss->getPosx() + 50, boss->getPosy() + 20, boss->getWidth(), boss->getHeight(), TYPEEXPLOSION);
    create_explosion(boss->getPosx() - 50, boss->getPosy() - 20, boss->getWidth(), boss->getHeight(), TYPEEXPLOSION);
    create_explosion(boss->getPosx() - 10, boss->getPosy() + 50, boss->getWidth(), boss->getHeight(), TYPEEXPLOSION);
    create_explosion(boss->getPosx() + 80, boss->getPosy() - 10, boss->getWidth(), boss->getHeight(), TYPEEXPLOSION);
}


void create_hit(int posx, int posy){
   hits[n_hits] = new Animation(posx, posy, TYPEHIT);
   /* setting animation frames positions according to the frame size and position */
   for(int i = 0; i < hits[n_hits]->getnFrames(); i++) {
      hitFrames[n_hits][i].x = posx - ((hits[n_hits]->frames_w[i])/2);
      hitFrames[n_hits][i].y = posy - ((hits[n_hits]->frames_h[i])/2);
      hitFrames[n_hits][i].w = hits[n_hits]->frames_w[i];
      hitFrames[n_hits][i].h = hits[n_hits]->frames_h[i];
   }
   printf("projectile location on hit %d %d\n", posx, posy); 
   printf("hit location %d %d\n", hits[n_hits]->frames_x[n_hits], hits[n_hits]->frames_y[n_hits]);
   n_hits++;
}


void spawn_boss() {
   if(cur_level->isBossLevel()) {
      boss = cur_level->getBoss();
      boss_img = IMG_LoadTexture(renderer, boss->icon_path);  
      boss_rect.x = SCREEN_HEIGHT/4;
      boss_rect.y = SCREEN_WIDTH/2 - (boss->getWidth())/2;
      boss_rect.w = boss->getWidth();
      boss_rect.h = boss->getHeight();
   }
}
   
void goToNextLevel(Ship *ship) {
   /* stop and free the theme from the level before updating it */
   Mix_HaltMusic();
   Mix_FreeMusic(themes[cur_level->getLevel()]);

   int next_n_level = cur_level->getLevel() + 1;
   cur_level = levels[next_n_level];

   /* loading and playing theme for the updated level */
   themes[cur_level->getLevel()] = Mix_LoadMUS(cur_level->getThemePath());
   printf("current level %d, current theme %s\n", cur_level->getLevel(),  cur_level->getThemePath());
   scroll_val = 0;
   n_projectiles = 0;
   n_enemy_projectiles = 0;
   n_enemy_missiles = 0;
   n_buildings = 0;
   n_enemies = 0;
   n_explosions = 0;
   n_hits = 0;
   /* building and enemy initialization do nothing 
    * when the coming level is a boss level */
   init_buildings(cur_level->getLevel());
   init_enemies(cur_level->getLevel());
   /* boss spawning does nothing when the coming
    * level is not a boss level */
   spawn_boss();
   init_animations();
   ship->setStartPosition();
}

void fire(Ship *ship){
   /* case it overflows (unlikely though) */
   projectiles[n_projectiles % MAXPJTL] = ship->fire();
   projectile_imgs[n_projectiles % MAXPJTL] = IMG_LoadTexture(renderer, PROJECTILEPATH);
   projectile_rects[n_projectiles % MAXPJTL].w = projectiles[n_projectiles % MAXPJTL]->getWidth();
   projectile_rects[n_projectiles % MAXPJTL].h = projectiles[n_projectiles % MAXPJTL]->getHeight();
   n_projectiles++;
}

void building_fire(Building *building, int ship_posx, int ship_posy) {
   if(building->getFireType() == FIREPJTLTYPE) {
      EnemyProjectile *projectile = building->fireProjectile(ship_posx, ship_posy);
      if(projectile != nullptr) {
         enemyProjectiles[n_enemy_projectiles % MAXPJTL] = projectile;
         enemy_projectile_imgs[n_enemy_projectiles % MAXPJTL] = IMG_LoadTexture(renderer, PROJECTILEPATH);
         enemy_projectile_rects[n_enemy_projectiles % MAXPJTL].w = projectile->getWidth();
         enemy_projectile_rects[n_enemy_projectiles % MAXPJTL].h = projectile->getHeight();
         n_enemy_projectiles++;
       } 
   } else if(building->getFireType() == FIREMSSLTYPE) {
      EnemyMissile *missile = building->fireMissile();
      if(missile != nullptr) {
         enemyMissiles[n_enemy_missiles % MAXMSSL] = missile;
         enemy_missile_imgs[n_enemy_missiles % MAXMSSL] = IMG_LoadTexture(renderer, missile->icon_path);
         enemy_missile_rects[n_enemy_missiles % MAXMSSL].w = missile->getWidth();
         enemy_missile_rects[n_enemy_missiles % MAXMSSL].h = missile->getHeight();
         n_enemy_missiles++;
      }
   } 
}
      
void spawn_enemy(int x, int y, int type, int move) {
   /* in case n_enemies get greater than MAXENMY */
   enemies[n_enemies % MAXENMY] = new Enemy(x, y, type, move);
   enemy_imgs[n_enemies % MAXENMY] = IMG_LoadTexture(renderer, enemies[n_enemies % MAXENMY]->icon_path);
   enemy_rects[n_enemies % MAXENMY].h = enemies[n_enemies % MAXENMY]->getHeight();
   enemy_rects[n_enemies % MAXENMY].w = enemies[n_enemies % MAXENMY]->getWidth();
   n_enemies++;
}



void draw_animation(SDL_Texture *animation_frame, SDL_Rect *current_clip){
   SDL_RenderCopy(renderer, animation_frame, NULL, current_clip);
}



void draw_target(const char *icon_path, SDL_Texture *img_target, SDL_Rect *p_rect) {
   SDL_RenderCopy(renderer, img_target, NULL, p_rect);
}

void draw_projectile(SDL_Texture *img_projectile, SDL_Rect *p_rect) {
   SDL_RenderCopy(renderer, img_projectile, NULL, p_rect);
}

void draw_info_components(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &margin_health_bar);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &inner_health_bar);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void init_info_components(){
   margin_health_bar.x = MARGINHEALTHBARX;
   margin_health_bar.y = MARGINHEALTHBARY;
   margin_health_bar.w = MARGINHEALTHBARW;
   margin_health_bar.h = MARGINHEALTHBARH;
   
   inner_health_bar.x = INNERHEALTHBARX;
   inner_health_bar.y = INNERHEALTHBARY;
   inner_health_bar.w = INNERHEALTHBARW;
   inner_health_bar.h = INNERHEALTHBARH;
}
    
void init_levels() {
   for(int i = 0; i < MAXLVL; i++) {
      levels[i] = new Level(i);
   }
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

void checkHitShip(EnemyProjectile *p, Ship *ship){
   if(p->getPosx() > ship->getPosx() &&                                  
     p->getPosx() < ship->getPosx() + 
     ship->getWidth() && 
     p->getPosy() > ship->getPosy() && 
     p->getPosy() < ship->getPosy() + 
     ship->getHeight()){
        ship->takeDamage(p->getDamage());
        p->active = false;
   } 
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
              create_hit(p->getPosx(), p->getPosy());
              bool dead = targets[j]->takeDamage(p->getDamage());
              p->active = false;
              if(dead) {
                create_explosion(targets[j]->getPosx(), targets[j]->getPosy(), targets[j]->getWidth(), targets[j]->getHeight(), TYPEEXPLOSION);
              }
         }   
      }
   }
}

/* TODO: Boss, enemy, missile and pick up HAVE a target -> 
 * there is only one hit algorithm */
inline void checkHitEnemies(Projectile *p, Enemy *targets[], int n_targets){
   for(int j = 0; j < n_targets; j++) {
      if(targets[j] != nullptr && targets[j]->active)  {
         if(p->getPosx() > targets[j]->getPosx() &&
           p->getPosx() < targets[j]->getPosx() + 
           targets[j]->getWidth() && 
           p->getPosy() > targets[j]->getPosy() && 
           p->getPosy() < targets[j]->getPosy() + 
           targets[j]->getHeight()){
              create_hit(p->getPosx(), p->getPosy());
              bool is_dead = targets[j]->takeDamage(p->getDamage());
              p->active = false;
              if(is_dead) {
                 create_explosion(targets[j]->getPosx(), targets[j]->getPosy(), targets[j]->getWidth(), targets[j]->getHeight(), TYPEEXPLOSION);
              }
         }   
      }
   }
}

inline void checkHitEnemyMissiles(Projectile *p, EnemyMissile *targets[], int n_targets){
   for(int j = 0; j < n_targets; j++) {
      if(targets[j] != nullptr && targets[j]->active)  {
         if(p->getPosx() > targets[j]->getHitBoxPosx() && 
          p->getPosx() < targets[j]->getPosx() + 
          targets[j]->getHitBoxWidth() && 
          p->getPosy() < targets[j]->getPosy() + 
          targets[j]->getHeight() && 
          p->getPosy() > targets[j]->getPosy()) {
            bool is_dead = targets[j]->takeDamage(p->getDamage());
            p->active = false;
              if(is_dead) {
                 create_explosion(targets[j]->getPosx(), targets[j]->getPosy(), targets[j]->getWidth(), targets[j]->getHeight(), TYPEEXPLOSION);
              }
          }
      }
   }
}

inline void checkHitBoss(Projectile *p, Boss *boss) {
   if(p->getPosx() > boss->getPosx() &&
     p->getPosx() < boss->getPosx() + 
     boss->getWidth() && 
     p->getPosy() > boss->getPosy() && 
     p->getPosy() < boss->getPosy() + 
     boss->getHeight()){
        create_hit(p->getPosx(), p->getPosy());
        bool is_dead = boss->takeDamage(p->getDamage());
        p->active = false;
        if(is_dead) {
           create_boss_explosions(boss);
        }
    }
}

void update(Ship *ship, SDL_Rect *ship_rect){
   /* updating incoming buildings */
   for(int i = 0; i < cur_level->getnBuildings(); i++) {
      struct buildings_pos_t *cur_buildings_pos = get_buildings_pos(cur_level->getLevel()); 
      if((cur_buildings_pos[i]).active) {
         int diff = scroll_val + get_buildings_pos(cur_level->getLevel())[i].scroll;
         if(diff > 0) {
            printf("%s\n", "creating building");
            buildings[i] = new Building(get_buildings_pos(cur_level->getLevel())[i].x, diff, get_buildings_pos(cur_level->getLevel())[i].type);
            printf("%s\n", "loading image");
            building_imgs[i] = IMG_LoadTexture(renderer, buildings[i]->icon_path);
            printf("%s\n", "setting rect positions");
            building_rects[i].w = buildings[i]->getWidth(); 
            building_rects[i].h = buildings[i]->getHeight(); 
            n_buildings++;
            get_buildings_pos(cur_level->getLevel())[i].active = false;
         }
      } 
   }
   /* updating buildings in screen */
   for(int i = 0; i < n_buildings; i++) {
      if(buildings[i] != nullptr) {
         if(buildings[i]->active){
            printf("%s\n", "active building - setting rects");
            building_rects[i].x = buildings[i]->getPosx();       
            building_rects[i].y = buildings[i]->getPosy();
            /* checking whether any buildings have fired.
            if so, gets what kind of weapon and treats it
            appropriately */
            printf("%s\n", "active building - firing");
            building_fire(buildings[i], ship->getPosx(), ship->getPosy()); 
            if(buildings[i]->getPosy() > SCREEN_HEIGHT) {
               buildings[i]->active = false;
            }
         }
      }      
   }
   scroll();
   /* updating incoming enemies */
   for(int i = 0; i < cur_level->getnEnemies(); i++) {
      if(get_enemies_pos(cur_level->getLevel())[i].active) {
         int diff = scroll_val + get_enemies_pos(cur_level->getLevel())[i].scroll;
         if(diff > 0) {
            spawn_enemy(get_enemies_pos(cur_level->getLevel())[i].x, diff, get_enemies_pos(cur_level->getLevel())[i].type, get_enemies_pos(cur_level->getLevel())[i].move);
            get_enemies_pos(cur_level->getLevel())[i].active = false;
         }
      } 
   }
   /* updating enemies on screen */
   for(int i = 0; i < n_enemies; i++) {
       if(enemies[i]->active) {
           /* check whether each enemy moved or fired -
           it's up to the enemy to decide either */
           enemies[i]->move();
           EnemyProjectile *fired_projectile = enemies[i]->fire_projectile(); 
           EnemyMissile *fired_missile = enemies[i]->fire_missile(); 
           /* if the enemy actually fired, store the projectiled and
           set the rects width and height to the projectiles */
           if(fired_projectile != nullptr){
              enemyProjectiles[n_enemy_projectiles % MAXPJTL] = fired_projectile;
              enemy_projectile_imgs[n_enemy_projectiles % MAXPJTL] = IMG_LoadTexture(renderer, fired_projectile->icon_path);
              enemy_projectile_rects[n_enemy_projectiles % MAXPJTL].w = fired_projectile->getWidth(); 
              enemy_projectile_rects[n_enemy_projectiles % MAXPJTL].h = fired_projectile->getHeight();
              n_enemy_projectiles++;
           } else if(fired_missile != nullptr){
              enemyMissiles[n_enemy_missiles % MAXPJTL] = fired_missile;
              enemy_missile_imgs[n_enemy_missiles % MAXPJTL] = IMG_LoadTexture(renderer, fired_missile->icon_path);
              enemy_missile_rects[n_enemy_missiles % MAXPJTL].w = fired_missile->getWidth(); 
              enemy_missile_rects[n_enemy_missiles% MAXPJTL].h =  fired_missile->getHeight();
              n_enemy_missiles++;
           }
           enemy_rects[i].x = enemies[i]->getPosx();
           enemy_rects[i].y = enemies[i]->getPosy();
           if(enemies[i]->getPosy() > SCREEN_HEIGHT) {
               enemies[i]->active = false;
           }
       } 
   }

   /* updating boss */
   if(cur_level->isBossLevel()) {
      if(!boss->isDead()) {
         EnemyProjectile *fired_projectile = boss->fireProjectile();
         EnemyMissile *fired_mssl = boss->fireMissile();
         if(fired_projectile != nullptr){
            enemyProjectiles[n_enemy_projectiles % MAXPJTL] = fired_projectile;
            enemy_projectile_imgs[n_enemy_projectiles % MAXPJTL] = IMG_LoadTexture(renderer, fired_projectile->icon_path);
            enemy_projectile_rects[n_enemy_projectiles % MAXPJTL].w = fired_projectile->getWidth(); 
            enemy_projectile_rects[n_enemy_projectiles % MAXPJTL].h = fired_projectile->getHeight();
            n_enemy_projectiles++;
         } else if(fired_mssl != nullptr){
            enemyMissiles[n_enemy_missiles % MAXPJTL] = fired_mssl;
            enemy_missile_imgs[n_enemy_missiles % MAXPJTL] = IMG_LoadTexture(renderer, fired_mssl->icon_path);
            enemy_missile_rects[n_enemy_missiles % MAXPJTL].w = fired_mssl->getWidth(); 
            enemy_missile_rects[n_enemy_missiles% MAXPJTL].h =  fired_mssl->getHeight();
            n_enemy_missiles++;
         }
      }
   }


   /* updating projectiles */
   for(int i = 0; i < n_projectiles; i++){
      if(projectiles[i]->active){
         projectiles[i]->move();
         projectile_rects[i].x = projectiles[i]->getPosx();
         projectile_rects[i].y = projectiles[i]->getPosy();
         /* checking for projectile hits */
         checkHitBuildings(projectiles[i], buildings, n_buildings);
         checkHitEnemies(projectiles[i], enemies, n_enemies); 
         checkHitEnemyMissiles(projectiles[i], enemyMissiles, n_enemy_missiles);
	 if(cur_level->isBossLevel()) {
            checkHitBoss(projectiles[i], boss);
	 }
      }
      //if(projectiles[n_projectiles] == nullptr) {
      //   n_projectiles--;
      //}
   }
   

   /* updating enemy projectiles */
   for(int i = 0; i < n_enemy_projectiles; i++){
      if(enemyProjectiles[i]->active){
         enemyProjectiles[i]->move();
         enemy_projectile_rects[i].x = enemyProjectiles[i]->getPosx();
         enemy_projectile_rects[i].y = enemyProjectiles[i]->getPosy();
         /* checking for projectile hits on buildings -
         check for null or inactive projectile must be done outside the function*/
         if(enemyProjectiles[i] != nullptr && enemyProjectiles[i]->active) {
            checkHitShip(enemyProjectiles[i], ship);
         }
      }
      //if(enemyProjectiles[n_enemy_projectiles] == nullptr) {
      //   n_enemy_projectiles--;
      //}
   }
   /* updating enemy missiles */
   for(int i = 0; i < n_enemy_missiles; i++) {
      if(enemyMissiles[i]->active) {
         enemyMissiles[i]->move(ship->getCenterPosx(), ship->getCenterPosy());
         enemy_missile_rects[i].x = enemyMissiles[i]->getPosx();
         enemy_missile_rects[i].y = enemyMissiles[i]->getPosy();
         /* checking for missile collisions -
         check for null or inactive projectile must be done outside the function*/
         if(enemyMissiles[i] != nullptr && enemyMissiles[i]->active) {
            if(ship->checkCollisionMissile(enemyMissiles[i])) {
               ship->takeDamage(enemyMissiles[i]->getDamage());
               enemyMissiles[i]->active=false;
            }
         }
      }
      //if(enemyProjectiles[n_enemy_missiles] == nullptr) {
      //   n_enemy_missiles--;
      //}
   }
   
   /* checking for collision of enemies with the ship */
   for(int i = 0; i < n_enemies; i++) {
       if(enemies[i]->active) {
          if(ship->checkCollision(enemies[i])){
              ship->takeDamage(enemies[i]->collision_damage);
              enemies[i]->active = false;
          }
       }
   }

   /* updating explosions */
   for(int i = 0; i < n_explosions; i++) {
      if(explosions[i]->active){
         explosions[i]->updateFrame();
      }
   }

   /* updating hits */
   for(int i = 0; i < n_hits; i++) {
      if(hits[i]->active){
        hits[i]->updateFrame();
      }
   }
   /* updating ship */
   ship_rect->x = ship->getPosx();
   ship_rect->y = ship->getPosy();

   /* updating health bar */
   float health_bar_ratio = float(ship->getHealth())/100;
   /* turn the health into a number between 0 and 1 and multiply by height */
   inner_health_bar.y = INNERHEALTHBARY  + int((1 - health_bar_ratio) * INNERHEALTHBARH);
   inner_health_bar.h = int(health_bar_ratio * INNERHEALTHBARH);
   if(inner_health_bar.h < 0) {
      inner_health_bar.h = 0;
      inner_health_bar.y = INNERHEALTHBARY + INNERHEALTHBARH;
   }

   /* checking if level has finished. Updating level if so */
      
   if(frame_cnt % FRAMERULE == 0) {
      if(cur_level->isBossLevel()) {
         if(boss->isDead()) {
             cur_level->finish();
             goToNextLevel(ship);
         }
      } else {             
         if(scroll_val > cur_level->getLength()){
             cur_level->finish();
             goToNextLevel(ship);
         }
      }
   }
}

void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Rect *ship_rect, SDL_Window *window){
   SDL_RenderClear(renderer);
   for(int i = 0; i < n_projectiles; i++) {
      if(projectiles[i]->active) {
         draw_projectile(projectile_imgs[i], &projectile_rects[i]);
      }
   }
   for(int i = 0; i < n_buildings; i++) {
      if(buildings[i] != nullptr) {
         if(buildings[i]->active) {
            draw_target(buildings[i]->icon_path, building_imgs[0], &building_rects[i]);
         }
      }
   }
   for(int i = 0; i < n_enemies; i++) {
      if(enemies[i] != nullptr) {
         if(enemies[i]->active) {
            draw_target(enemies[i]->icon_path, enemy_imgs[i], &enemy_rects[i]);
         }
      }
   }
   for(int i = 0; i < n_enemy_projectiles; i++) {
      if(enemyProjectiles[i] != nullptr) {
         if(enemyProjectiles[i]->active) {
            draw_target(enemyProjectiles[i]->icon_path, enemy_projectile_imgs[0], &enemy_projectile_rects[i]);
         }
      }
   }
   for(int i = 0; i < n_enemy_missiles; i++) {
      if(enemyMissiles[i] != nullptr) {
         if(enemyMissiles[i]->active) {
            draw_target(enemyMissiles[i]->icon_path, enemy_missile_imgs[0], &enemy_missile_rects[i]);
         }
      }
   }
   for(int i = 0; i < n_explosions; i++) {
      if(explosions[i]->active) {
         int current_frame = explosions[i]->getCurrentFrame();
         draw_animation(explosionTextures[current_frame], &explosionsFrames[i][current_frame]); 
      }
   }
   for(int i = 0; i < n_hits; i++) {
      if(hits[i]->active) {
         int current_frame = hits[i]->getCurrentFrame();
         draw_animation(hitTextures[current_frame], &hitFrames[i][current_frame]); 
      }
   }
   SDL_RenderCopy(renderer, img_ship, NULL, ship_rect);
   draw_info_components();   
   SDL_RenderPresent(renderer);
}

void present_g_o_sequence(){
   int n_blits = 10;
   int slow_factor;
   for(int i = 0; i < n_blits; i++){ 
      slow_factor = i * 10;
      SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
      SDL_UpdateWindowSurface(window);
      SDL_Delay(G_O_BLIT_MS + slow_factor);
      SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
      SDL_UpdateWindowSurface(window);
      SDL_Delay(G_O_BLIT_MS + slow_factor);
   }
} 

void play_theme(){
   if(Mix_PlayingMusic() == 0) {
      Mix_PlayMusic(themes[cur_level->getLevel()], -1);
   }
}

int main(int argc, char* args[]) {
   SDL_Surface *shipSurface = NULL;
   SDL_Surface *loadSurface = NULL;
  
   SDL_Texture *projectile = NULL;
   SDL_Rect ship_rect;
   Ship ship;
   frame_cnt = 0l;
   scroll_speed = 1;
   scroll_slow = 8;
   
   
   if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
      printf("%s\n", "Unable to initialize SDL");
      exit(1);
   }
   window = SDL_CreateWindow(TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if(window == NULL) {
      printf("%s\n", "Unable to create window");
      exit(1);
   }
   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if(renderer == NULL) {
      printf("%s\n", "Unable to create window");
      exit(1);
   }   
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      printf("%s\n", "Unable to initialize mixer");
      exit(1);
   }
      
   int imgFlags = IMG_INIT_PNG;
   if(!(IMG_Init(imgFlags) & imgFlags)) {
      printf("Unable to load image");
      exit(1);
   }
  
   /* initializing ship */ 
   img_ship = IMG_LoadTexture(renderer, ship.getIconPath());
   ship.setStartPosition();
   ship_rect.w = ship.getWidth();
   ship_rect.h = ship.getHeight(); 
   ship_rect.x = ship.getPosx();
   ship_rect.y = ship.getPosy(); 

   bool quit = false;
   /* initializing level */
   init_levels();
   cur_level = levels[0];
   init_buildings(cur_level->getLevel());
   printf("cur level: %d\n", cur_level->getLevel());
   init_enemies(cur_level->getLevel());
   init_info_components();
   init_animations();
   printf("animations initialized");
   
   themes[cur_level->getLevel()] = Mix_LoadMUS(cur_level->getThemePath());

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
            fire(&ship);
         }
      }
      play_theme();
      printf("updating\n");
      update(&ship, &ship_rect);
      draw(renderer, surface, &ship_rect, window);
      if(ship.cur_health <= 0) {
         present_g_o_sequence();
         quit = true; 
      }
   }
   SDL_DestroyWindow(window);
   SDL_Quit();
   return 0; 
}
