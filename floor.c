/** Génération d'un étage de "The Binding of Briatte"
 * Auteur : Matthieu LEVASSEUR
 * Date : 23/10/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "floor.h"
#include "map.h"
#include "player.h"
#include "shooter.h"


void printFloor(Floor floor){
    for(int i = 0; i < floor.size; i += 1){
        for(int j = 0; j < floor.size; j += 1){
            printf("%c ",floor.chunck[i][j]);
        }
        printf("\n");
    }
}

void addRoom(Floor* floor, int y, int x, int id, int type){
    // srand(time(NULL));
    RoomItem* newRoom = malloc(sizeof(RoomItem));
    newRoom->x = x;
    newRoom->y = y;
    newRoom->id = id == 0 ? 0 : (rand() % nbMaps() + 1);
    newRoom->map = getMap(newRoom->id);
    newRoom->type = type;
    if(type == 0){
        newRoom->monster_list = spawn((rand()%4 + 2),x,y,newRoom->map);
        newRoom->map->status = 1;
    }else newRoom->monster_list = NULL;
    newRoom->ind = length(floor->list);
    newRoom->last = floor->list;
    floor->list = newRoom;
}

int length(RoomItem* rooms){
    int n = 0;
    while(rooms){
        n += 1;
        rooms = rooms->last;
    }
    return n;
}

RoomItem* getRoom(RoomItem* rooms, int ind){
    while(rooms != NULL && rooms->ind != ind){
        rooms = rooms->last;
    }
    return rooms;
}

// void printRooms(RoomItem *rooms, PLAYER player){
//     while(rooms)
//         {
//             printRoom(rooms, player);
//             rooms = rooms->last;
//         }
// }

// void printRoom(RoomItem* room, PLAYER player){
//     printf("x : %d - y : %d - id : %d - ind : %d\n",room->x, room->y, room->id, room->ind);
//     displayRoom(room->map->room,room->map->height,room->map->width, player);
//     printf("\n");
// }

Floor* newFloor(int stage){
    srand(time(NULL));
    Floor* floor = malloc(sizeof(Floor));
    floor->list = NULL;
    floor->stage = stage;
    floor->size = floor->stage * 4 + 1;

    floor->chunck = malloc(sizeof(char*) * floor->size);
    for(int i = 0; i < floor->size; i += 1){
        floor->chunck[i] = malloc(sizeof(char) * floor->size);
    }
    for(int i = 0; i < floor->size; i += 1){
        for(int j = 0; j < floor->size; j += 1){
            floor->chunck[i][j] = EMPTY;
        }
    }
    
    floor->curX = (floor->size - 1) / 2;
    floor->curY = (floor->size - 1) / 2;
    int remain = floor->size - 1;
    floor->chunck[floor->curY][floor->curX] = SPAWN;
    addRoom(floor,floor->curY,floor->curX,0,3);
    fillFloor(floor);
    return floor;
}

void fillFloor(Floor* floor){
    srand(time(NULL));
    int remain = floor->size - 1;
    placeRoom(floor,&remain,ROOM);
    remain = 1;
    placeRoom(floor, &remain, ITEM);
    remain = 1;
    placeRoom(floor, &remain, BOSS);
}

void placeRoom(Floor* floor, int* remain, char type){
    while(*remain > 0){
        int dir = rand() % 4;
        int ind = rand() % length(floor->list);
        int i,j;
        RoomItem* temp = getRoom(floor->list,ind);
        if(floor->chunck[temp->y][temp->x] == 'I') continue;
        switch(dir){
            case 0:
                i = temp->y;
                j = temp->x - 1;
            break;
            case 1:
                i = temp->y - 1;
                j = temp->x;
            break;
            case 2:
                i = temp->y;
                j = temp->x + 1;
            break;
            case 3:
                i = temp->y + 1;
                j = temp->x;
            break;
        }
        nextRoom(floor,i,j,remain, type);
    }
}

int nextRoom(Floor* floor, int y, int x, int * remain, char type){
    if(
        y > floor->size - 1
        || x > floor->size - 1
        || y < 0
        || x < 0
    ){
        return 0;
    }else if(type == BOSS || type == ITEM){
        if(getVoisin(floor,x,y) > 1) return 0;
    }
    // else if(getVoisin(floor,x,y) > 2) return 0;
    if(floor->chunck[y][x] == EMPTY){
        if(type == BOSS){
            if(x - 1 >= 0 && getVoisin(floor,x-1,y) == 0){
                floor->chunck[y][x-1] = ITEM;
                addRoom(floor,y,x-1,0,2);
            }else if(y - 1 >= 0 && getVoisin(floor,x,y-1) == 0){
                floor->chunck[y-1][x] = ITEM;
                addRoom(floor,y-1,x,0,2);
            }else if(x + 1 < floor->size && getVoisin(floor,x+1,y) == 0){
                floor->chunck[y][x+1] = ITEM;
                addRoom(floor,y,x+1,0,2);
            }else if(y + 1 >= 0 && getVoisin(floor,x,y+1) == 0){
                floor->chunck[y+1][x] = ITEM;
                addRoom(floor,y+1,x,0,2);
            }else{
                return 0;
            }
        }
        floor->chunck[y][x] = type;
        // srand(time(NULL));
        int index = type == ROOM ? 1 : 0;
        addRoom(floor,y,x,index,(type == ROOM ? 0 : 1));
        *remain -= 1;
        return 1;
    }
}

RoomItem* getRoomByCoord(RoomItem* rooms, int x, int y){
    while(rooms != NULL){
        if(rooms->x == x && rooms->y == y) return rooms;
        rooms = rooms->last;
    }
    return NULL;
}

int getVoisin(Floor* floor, int x, int y){
    int count = 0;
    if(getRoomByCoord(floor->list,x+1,y)) count += 1;
    if(getRoomByCoord(floor->list,x-1,y)) count += 1;
    if(getRoomByCoord(floor->list,x,y+1)) count += 1;
    if(getRoomByCoord(floor->list,x,y-1)) count += 1;
    return count;
}

void freeList(RoomItem* list){
    while(list){
        RoomItem* next = list->last;
        free(list);
        list = next;
    }
}

void freeFloor(Floor* floor){
    free(floor->list);
    for(int i = 0; i < floor->size; i += 1){
        free(floor->chunck[i]);
    }
    free(floor->chunck);
    free(floor);
}

void checkDoors(Floor* floor){
    RoomItem* rooms = floor->list;
    while(rooms){
        if(rooms->x == 0){
            rooms->map->room[(rooms->map->height - 1)/2][0] = 'W';
        }else{
            switch(floor->chunck[rooms->y][rooms->x-1]){
                case 'R':
                    rooms->map->room[(rooms->map->height - 1)/2][0] = 'D';
                    break;
                case 'I':
                    rooms->map->room[(rooms->map->height - 1)/2][0] = '$';
                    break;
                case 'B':
                    rooms->map->room[(rooms->map->height - 1)/2][0] = 'B';
                    break;
                case 'S':
                    rooms->map->room[(rooms->map->height - 1)/2][0] = 'D';
                    break;
                default :
                    rooms->map->room[(rooms->map->height - 1)/2][0] = 'W';
                    break;
            }
        }
        if(rooms->y == 0){
            rooms->map->room[0][(rooms->map->width - 1)/2] = 'W';
        }else{
            switch(floor->chunck[rooms->y-1][rooms->x]){
                case 'R':
                    rooms->map->room[0][(rooms->map->width - 1)/2] = 'D';
                    break;
                case 'S':
                    rooms->map->room[0][(rooms->map->width - 1)/2] = 'D';
                    break;
                case 'I':
                    rooms->map->room[0][(rooms->map->width - 1)/2] = '$';
                    break;
                case 'B':
                    rooms->map->room[0][(rooms->map->width - 1)/2] = 'B';
                    break;
                default :
                    rooms->map->room[0][(rooms->map->width - 1)/2] = 'W';
                    break;
            }
        }
        if(rooms->y == floor->size - 1){
            rooms->map->room[rooms->map->height-1][(rooms->map->width - 1)/2] = 'W';
        }else{
            switch(floor->chunck[rooms->y+1][rooms->x]){
                case 'R':
                    rooms->map->room[rooms->map->height-1][(rooms->map->width - 1)/2] = 'D';
                    break;
                case 'S':
                    rooms->map->room[rooms->map->height-1][(rooms->map->width - 1)/2] = 'D';
                    break;
                case 'I':
                    rooms->map->room[rooms->map->height-1][(rooms->map->width - 1)/2] = '$';
                    break;
                case 'B':
                    rooms->map->room[rooms->map->height-1][(rooms->map->width - 1)/2] = 'B';
                    break;
                default :
                    rooms->map->room[rooms->map->height-1][(rooms->map->width - 1)/2] = 'W';
                    break;
            }
        }
        if(rooms->x == floor->size - 1){
            rooms->map->room[(rooms->map->height - 1)/2][rooms->map->width - 1] = 'W';
        }else{
            switch(floor->chunck[rooms->y][rooms->x+1]){
                case 'R':
                    rooms->map->room[(rooms->map->height - 1)/2][rooms->map->width - 1] = 'D';
                    break;
                case 'S':
                    rooms->map->room[(rooms->map->height - 1)/2][rooms->map->width - 1] = 'D';
                    break;
                case 'I':
                    rooms->map->room[(rooms->map->height - 1)/2][rooms->map->width - 1] = '$';
                    break;
                case 'B':
                    rooms->map->room[(rooms->map->height - 1)/2][rooms->map->width - 1] = 'B';
                    break;
                default :
                    rooms->map->room[(rooms->map->height - 1)/2][rooms->map->width - 1] = 'W';
                    break;
            }
        }
        // printf("room[%d][%d] : %c - up : %c - down : %c - left : %c - right : %c\n",
        //     rooms->y,
        //     rooms->x,
        //     floor->chunck[rooms->y][rooms->x],
        //     floor->chunck[rooms->y-1][rooms->x],
        //     floor->chunck[rooms->y+1][rooms->x],
        //     floor->chunck[rooms->y][rooms->x-1],
        //     floor->chunck[rooms->y][rooms->x+1]);
        rooms = rooms->last;
    }
}

void nextStep(Floor* floor, PLAYER player, SHOOT* shoots, BOSS_MONSTER boss){
    RoomItem* room = getRoomByCoord(floor->list,player.roomX,player.roomY);
    displayRoom(room->map->room,room->map->height,room->map->width,player, shoots, boss,room->monster_list);
}