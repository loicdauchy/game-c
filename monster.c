#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "monster.h"

MONSTER_LIST* spawn(int size, int roomX, int roomY, MAP *map){
    MONSTER_LIST* monster_list = NULL;
    for(int i = 0; i < size; i += 1){
        MONSTER_LIST* newMonster = malloc(sizeof(MONSTER_LIST));
        newMonster->roomX = roomX;
        newMonster->roomY = roomY;
        newMonster->size = size;

        int x,y;
        do{
            x = rand()%map->width;
            y = rand()%map->height;
        }while(map->room[y][x] != EMPTY);
        int index = rand()%(getNbMonster());
        newMonster->monster = getMonster(index, map, monsterLength(monster_list) + 1);
        newMonster->last = monster_list;
        monster_list = newMonster;
    }
    return monster_list;
}

// MONSTER* newMonster(MAP* map){
//     int x,y;
//     do{
//         x = rand()%map->width;
//         y = rand()%map->height;
//     }while(map->room[y][x] != EMPTY);
    
//     return monster;
// }

MONSTER* getMonster(int id, MAP* map, int ind){
    FILE * fp = fopen("./monster.tbob","r");
    if(fp == NULL){
        printf("ERROR");
    }else{
        int x,y;
        do{
            x = 1 + rand()%(map->width - 1);
            y = 1 + rand()%(map->height - 1);
        }while(map->room[y][x] != EMPTY);
        MONSTER* monster = malloc(sizeof(MONSTER));
        monster->alive = 1;
        monster->damage = 1;
        monster->delay = 20.0;
        monster->type = id;
        monster->ind = ind;
        monster->x = x;
        monster->y = y;
        monster->fly = 0;
        monster->ss = 0;
        int curId, curW, curH, ind = 0, next = 1;
        char str[100];
        char attribut[20];
        char c = ' ';
        fseek(fp,0,SEEK_END);
        int max = ftell(fp);
        fseek(fp,5,SEEK_SET);
        fseek(fp,5,SEEK_CUR);
        // fscanf(fp,"%s",str);
        // printf("%s\n",str);
        // printf("RESULT: %d\n",strcmp(str,"---"));
        while(ind <= id){
            while(next){
                fscanf(fp,"%s",str);
                if(strcmp(str,"---") && ind <= id){
                    if(ind == id){
                        strcpy(attribut,"");
                        int i = 0;
                        c = ' ';
                        while(c != '='){
                            c = str[i];
                            if(c != '='){
                                strncat(attribut,&c,1);
                            }
                            i += 1;
                        }
                        // printf("attribut : %s",attribut);
                        if(!strcmp(attribut,"hpMax")){
                            monster->health = (int)str[i] - 48;
                            // printf(" = %d\n", (int)str[i] - 48);
                        }else if(!strcmp(attribut,"flight")){
                            if(str[i] == 't'){
                                monster->fly = 1;
                                // printf(" = %s\n","True");
                            }
                        }else if(!strcmp(attribut,"shoot")){
                            if(str[i] == 't'){
                                monster->ss = 1;
                                // printf(" = %s\n","True");
                            }
                        }else printf("\n");
                    }
                    if(ftell(fp) == max){
                        ind += 1;
                    }
                }else{
                    next = 0;
                }
            }
            next = 1;
            ind += 1;
        }
        // MAP* map = malloc(sizeof(MAP));
        // map->room = initRoom(curH,curW);
        // map->height = curH;
        // map->width = curW;
        // map->status = 0;
        // for(int i = 0; i < curH; i += 1){
        //     for(int j = 0; j < curW; j += 1){
        //         map->room[i][j] = fgetc(fp);
        //         fseek(fp,1,SEEK_CUR);
        //         if(j == curW - 1)fseek(fp,1,SEEK_CUR);
        //     }
        // }
        // displayRoom(room,curH,curW);
        fclose(fp);
        return monster;
    }
}

void printMonsters(MONSTER_LIST* monster_list){
    while(monster_list){
        printMonster(monster_list);
        monster_list = monster_list->last;
    }
}

int getMonsterByCoord(MONSTER_LIST* monster_list, int x, int y){
    while(monster_list){
        if(monster_list->monster->x == x && monster_list->monster->y == y && monster_list->monster->alive)return monster_list->monster->type;
        monster_list = monster_list->last;
    }
    return 0;
}

// MONSTER* getMonsterByInd(MONSTER_LIST* monster_list, int ind){
//     while(monster_list != NULL && monster_list->monster->ind != ind){
//         monster_list = monster_list->last;
//     }
//     return monster_list->monster;
// }

void hitMonsterByCoord(int damage, MONSTER_LIST* monster_list, int x, int y){
    while(monster_list){
        if(monster_list->monster->x == x && monster_list->monster->y == y) looseHealthMonster(damage,monster_list->monster);
        monster_list = monster_list->last;
    }
}

void printMonster(MONSTER_LIST* monster_list){
    if(monster_list->monster->alive)printf("%d - [%d,%d] - hpMax: %d - fly: %d - shoot: %d\n",monster_list->monster->ind,monster_list->monster->x,monster_list->monster->y,monster_list->monster->health,monster_list->monster->fly,monster_list->monster->ss);
}

int getNbMonster(void){
    FILE * fp = fopen("./monster.tbob","r");
    if(fp == NULL){
        printf("ERROR");
    }else{
        fseek(fp,1,SEEK_SET);
        int nb = 0;
        fscanf(fp,"%d",&nb);
        return nb;
    }
}

int looseHealthMonster(int hp, MONSTER *monster){
    monster->health -= hp;
    return checkHealthMonster(monster);
}

int checkHealthMonster(MONSTER *monster){
    if(monster->health <= 0){
        monster->alive = 0;
        return 0;
    }
    return 1;
}

int checkKills(MONSTER_LIST* monster_list){
    while(monster_list){
        if(monster_list->monster->alive)return 0;
        monster_list = monster_list->last;
    }
    return 1;
}

int monsterLength(MONSTER_LIST* monster_list){
    int i = 0;
    while(monster_list){
        i += 1;
        monster_list = monster_list->last;
    }
    return i;
}

void monsterAI(Floor* floor, MONSTER_LIST *monster_list, PLAYER *player, SHOOT** projectiles){
    RoomItem* room = getRoomByCoord(floor->list,player->roomX, player->roomY);
    int choice = rand()%2;
    while(monster_list && monster_list->monster->alive){
        int ss = monster_list->monster->ss;

        if(ss){
            if(choice > 0){
                if(player->x < monster_list->monster->x)checkCollisionMonster(room->map->room,player,monster_list->monster,'q');
                else if(player->x > monster_list->monster->x)checkCollisionMonster(room->map->room,player,monster_list->monster,'d');
                else if(player->y > monster_list->monster->y)checkCollisionMonster(room->map->room,player,monster_list->monster,'s');
                else if(player->y < monster_list->monster->x)checkCollisionMonster(room->map->room,player,monster_list->monster,'z');
            }else{
                if(player->x < monster_list->monster->x)shoot(projectiles,monster_list->monster->x,monster_list->monster->y,'q', 'x');
                else if(player->x > monster_list->monster->x)shoot(projectiles,monster_list->monster->x,monster_list->monster->y,'d', 'x');
                else if(player->y > monster_list->monster->y)shoot(projectiles,monster_list->monster->x,monster_list->monster->y,'s', 'x');
                else if(player->y < monster_list->monster->x)shoot(projectiles,monster_list->monster->x,monster_list->monster->y,'z', 'x');
            }
        }else{
           if(player->x < monster_list->monster->x)checkCollisionMonster(room->map->room,player,monster_list->monster,'q');
            else if(player->x > monster_list->monster->x)checkCollisionMonster(room->map->room,player,monster_list->monster,'d');
            else if(player->y > monster_list->monster->y)checkCollisionMonster(room->map->room,player,monster_list->monster,'s');
            else if(player->y < monster_list->monster->x)checkCollisionMonster(room->map->room,player,monster_list->monster,'z'); 
        }

        monster_list = monster_list->last;
    }
}

int checkCollisionMonster(char** room,PLAYER *player, MONSTER* monster, char dir){
switch (dir)
    {
    case 'q':
        if(room[monster->y][monster->x - 1] == 'W') return 0;
        if(monster->y == player->y && monster->x - 1 == player->x ){
            looseHealth(monster->damage,player);
            return 0;
        }
        if(room[monster->y][monster->x - 1] == 'G' && !monster->fly) return 0;
        if(room[monster->y][monster->x - 1] == 'R' && !monster->fly) return 0;
        monster->x -= 1;
        return 1;
        break;
    case 'z':
        if(room[monster->y - 1][monster->x] == 'W') return 0;
        if(monster->y - 1 == player->y && monster->x == player->x ){
            looseHealth(monster->damage,player);
            return 0;
        }
        if(room[monster->y - 1][monster->x] == 'G' && !monster->fly) return 0;
        if(room[monster->y - 1][monster->x] == 'R' && !monster->fly) return 0;
        monster->y -= 1;
        return 1;
        break;
    case 'd':
        if(room[monster->y][monster->x + 1] == 'W') return 0;
        if(monster->y == player->y && monster->x + 1 == player->x ){
            looseHealth(monster->damage,player);
            return 0;
        }
        if(room[monster->y][monster->x + 1] == 'G' && !monster->fly) return 0;
        if(room[monster->y][monster->x + 1] == 'R' && !monster->fly) return 0;
        monster->x += 1;
        return 1;
        break;
    case 's':
        if(room[monster->y + 1][monster->x] == 'W') return 0;
        if(monster->y + 1 == player->y && monster->x == player->x ){
            looseHealth(monster->damage,player);
            return 0;
        }
        if(room[monster->y + 1][monster->x] == 'G' && !monster->fly) return 0;
        if(room[monster->y + 1][monster->x] == 'R' && !monster->fly) return 0;
        monster->y += 1;
        return 1;
        break;
    }
}

void killAll(MONSTER_LIST* monster_list){
    while(monster_list){
        monster_list->monster->alive = 0;
        monster_list = monster_list->last;
    }
}