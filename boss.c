#include "boss.h"

BOSS_MONSTER* newBoss(int floor){
    BOSS_MONSTER* boss = malloc(sizeof(BOSS_MONSTER));
    switch (floor)
    {
    case 1: // JAGGER
        boss->damage = 1;
        boss->health = 100;
        boss->type = 1;
        boss->delay = 10.0;
        boss->x = 7;
        boss->y = 4;
        break;
    case 2: // LENINA
        boss->damage = 2;
        boss->health = 300;
        boss->type = 2;
        boss->delay = 15.0;
        boss->x = 7;
        boss->y = 4;
        break;
    case 3: // ATHINA
        boss->damage = 2;
        boss->health = 450;
        boss->type = 3;
        boss->delay = 15.0;
        boss->x = 7;
        boss->y = 4;
        break;
    
    default:
        break;
    }
    boss->active = 0;
    boss->alive = 1;
    return boss;
}

void bossAI(Floor* floor, BOSS_MONSTER *boss, PLAYER *player, SHOOT** projectiles){
    RoomItem* room = getRoomByCoord(floor->list,player->roomX, player->roomY);
    int choice = rand()%2;
    switch (boss->type)
    {
    case 1:
        if(choice > 0){
            if(player->x < boss->x)checkCollisionBoss(room->map->room,player,boss,'q');
            else if(player->x > boss->x)checkCollisionBoss(room->map->room,player,boss,'d');
            else if(player->y > boss->y)checkCollisionBoss(room->map->room,player,boss,'s');
            else if(player->y < boss->x)checkCollisionBoss(room->map->room,player,boss,'z');
        }else{
            if(player->x < boss->x)shoot(projectiles,boss->x,boss->y,'q', 'X');
            else if(player->x > boss->x)shoot(projectiles,boss->x,boss->y,'d', 'X');
            else if(player->y > boss->y)shoot(projectiles,boss->x,boss->y,'s', 'X');
            else if(player->y < boss->x)shoot(projectiles,boss->x,boss->y,'z', 'X');
        }

        break;

    case 2:        
        if(player->x < boss->x)shoot(projectiles,boss->x,boss->y,'q', 'X');
        else if(player->x > boss->x)shoot(projectiles,boss->x,boss->y,'d', 'X');
        else if(player->y > boss->y)shoot(projectiles,boss->x,boss->y,'s', 'X');
        else if(player->y < boss->x)shoot(projectiles,boss->x,boss->y,'z', 'X');
        break;

    case 3:        
        shoot(projectiles,boss->x,boss->y,'q', 'X');
        shoot(projectiles,boss->x,boss->y,'d', 'X');
        shoot(projectiles,boss->x,boss->y,'s', 'X');
        shoot(projectiles,boss->x,boss->y,'z', 'X');
        break;
    
    default:
        break;
    }
}

int checkCollisionBoss(char** room,PLAYER *player, BOSS_MONSTER* boss, char dir){
switch (dir)
    {
    case 'q':
        boss->facing = 'q';
        if(room[boss->y][boss->x - 1] == 'W') return 0;
        if(boss->y == player->y && boss->x - 1 == player->x ){
            looseHealth(boss->damage,player);
            return 0;
        }
        if(room[boss->y][boss->x - 1] == 'G' && !boss->fly) return 0;
        if(room[boss->y][boss->x - 1] == 'R' && !boss->fly) return 0;
        boss->x -= 1;
        return 1;
        break;
    case 'z':
        boss->facing = 'z';
        if(room[boss->y - 1][boss->x] == 'W') return 0;
        if(boss->y - 1 == player->y && boss->x == player->x ){
            looseHealth(boss->damage,player);
            return 0;
        }
        if(room[boss->y - 1][boss->x] == 'G' && !boss->fly) return 0;
        if(room[boss->y - 1][boss->x] == 'R' && !boss->fly) return 0;
        boss->y -= 1;
        return 1;
        break;
    case 'd':
        boss->facing = 'd';
        if(room[boss->y][boss->x + 1] == 'W') return 0;
        if(boss->y == player->y && boss->x + 1 == player->x ){
            looseHealth(boss->damage,player);
            return 0;
        }
        if(room[boss->y][boss->x + 1] == 'G' && !boss->fly) return 0;
        if(room[boss->y][boss->x + 1] == 'R' && !boss->fly) return 0;
        boss->x += 1;
        return 1;
        break;
    case 's':
        boss->facing = 's';
        if(room[boss->y + 1][boss->x] == 'W') return 0;
        if(boss->y + 1 == player->y && boss->x == player->x ){
            looseHealth(boss->damage,player);
            return 0;
        }
        if(room[boss->y + 1][boss->x] == 'G' && !boss->fly) return 0;
        if(room[boss->y + 1][boss->x] == 'R' && !boss->fly) return 0;
        boss->y += 1;
        return 1;
        break;
    }
}

int looseHealthBoss(int hp, BOSS_MONSTER *boss){
    boss->health -= hp;
    return checkHealthBoss(boss);
}

int checkHealthBoss(BOSS_MONSTER *boss){
    if(boss->health <= 0){
        boss->alive = 0;
        return 0;
    }
    return 1;
}