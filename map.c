#include <stdio.h>
#include <stdlib.h>
#include "floor.h"
#include "map.h"
#include "player.h"
#include "boss.h"
#include "shooter.h"

MAP* getMap(int id){
    FILE * fp = fopen("./maps/maps.tbob","r");
    if(fp == NULL){
        printf("ERROR");
    }else{
        int curId, curW, curH;
        char str[100];
        fseek(fp,5,SEEK_SET);
        for(int i = 1; i < id; i += 1){
            fscanf(fp,"[%d|%d]%d\n",&curH,&curW,&curId);
            fseek(fp,(curH*(curW*2+1)),SEEK_CUR);
        } 
        fscanf(fp,"[%d|%d]%d\n",&curH,&curW,&curId);
        // printf("height: %d, width: %d, id: %d\n",curH,curW, curId);
        MAP* map = malloc(sizeof(MAP));
        map->room = initRoom(curH,curW);
        map->height = curH;
        map->width = curW;
        map->status = 0;
        for(int i = 0; i < curH; i += 1){
            for(int j = 0; j < curW; j += 1){
                map->room[i][j] = fgetc(fp);
                fseek(fp,1,SEEK_CUR);
                if(j == curW - 1)fseek(fp,1,SEEK_CUR);
            }
        }
        // displayRoom(room,curH,curW);
        fclose(fp);
        return map;
    }
    return NULL;
}

char** initRoom(int height, int width){    
    char** room = malloc(sizeof(char*)*height);
    for(int i = 0; i < height; i += 1){
        room[i] = malloc(sizeof(char)*width);
    }
    return room;
}

void displayRoom(char** room, int height, int width, PLAYER player, SHOOT* shoots, BOSS_MONSTER boss, MONSTER_LIST* monster_list){
    // printMonsters(monster_list);
    printf("HEALTH : ");
    for(int i = 0; i < player.health; i += 1){
        if(i%2==0)printf("<");
        else printf("3");
    }
    if(player.shield)printf("|");
    for(int i = 0; i < player.shield; i += 1){
        printf("D");
    }
    if(boss.active && boss.alive)printf("\n%s: %d",(boss.type == 1 ? "JAGGER" : (boss.type == 2 ? "LENINA" : "ATHINA")),boss.health);
    printf("\n");
    for(int i = 0; i < height; i += 1){
        for(int j = 0; j < width; j += 1){
            SHOOT* tmp = shoots;
            char proj = 'n';
            while(tmp){
                if(i == tmp->startY && j == tmp->startX){
                    proj = tmp->type;
                }
                tmp = tmp->last;
            }
            if(proj != 'n'){
                printf("%c ",proj);
            }else if(getMonsterByCoord(monster_list,j,i)){
                printf("%d ",getMonsterByCoord(monster_list,j,i));
            }else if(i == player.y && j == player.x){
                printf("%c ",'P');
            }else if(boss.active && i == boss.y && j == boss.x){
                printf("%c ",'B');
            }else{
                printf("%c ",room[i][j]);
            }
        }
        printf("\n");
    }
}

int nbMaps(void){
    FILE* fp = fopen("./maps/maps.tbob","r");
    int size;
    fscanf(fp,"{%d}",&size);
    fclose(fp);
    return size;
}