#ifndef ENEMY_PROJECTILE_H_
#define ENEMY_PROJECTILE_H_
#define ENEMYPROJECTILEPATH1	"assets/enemy_projectile1.png"

#define TYPE_1			1
#define TYPE_1_DMG		5
#define	TYPE_1_SPEED		1
#define TYPE_1_WIDTH		10
#define TYPE_1_HEIGHT		20

#define TYPE_2			2


class EnemyProjectile {
    public:    
    int speed;
    int damage;
    int posx;
    int posy;
    int w;
    int h;
    int type;
    bool active;
    int counter;
    int direction;
    char* icon_path;

    EnemyProjectile(){}

    EnemyProjectile(int s_posx, int s_posy, int s_type, int s_direction);
    int getPosx(void);
    int getPosy(void);
    int getWidth(void);
    int getHeight(void);
    void move(void);
    int getDamage(void);
};
#endif
