#include "game.h"

int play(void){

    SHOOT* projectiles = NULL;
    double invulnerability = SAFE;

    int newEntry = 1;

    // newShoot(&projectiles,2,2,'s','o');  

    int level = 1;
    
    Floor* floor = newFloor(level);
    BOSS_MONSTER* boss = newBoss(level++);
    double delay_boss = boss->delay;
    PLAYER player;
    player.fly = 0;
    player.health = 10;
    player.shield = 10;
    player.ss = 0;
    player.tirRate = 1000;
    player.damage = 200;
    player.nextLevel = 0;
    player.lastShot = 0.0;
    player.roomX = (floor->size-1)/2;
    player.roomY = (floor->size-1)/2;
    player.facing = 'z';
    player.x = (getRoomByCoord(
                floor->list,
                (floor->size-1)/2,
                (floor->size-1)/2
                )->map->width - 1) / 2;
    player.y = (getRoomByCoord(
                floor->list,
                (floor->size-1)/2,
                (floor->size-1)/2
                )->map->height - 1) / 2;
    printFloor(*floor);
    checkDoors(floor);
    nextStep(floor,player, projectiles, *boss);
    char dir;
    double frame = 1.0;
    getch();
    while (dir != 'p' && level < 5){
        RoomItem* room = getRoomByCoord(floor->list,player.roomX,player.roomY);
        if((int)frame%SPEED==0){
            if(boss->alive){
                if(room->type == 1){
                    boss->active = 1;
                    room->map->status = 1;
                    if(delay_boss >= boss->delay){
                        bossAI(floor,boss,&player,&projectiles);    
                        delay_boss = 0.0;            
                    }else{
                        delay_boss += 1.0;
                    }
                }
            }else if(boss->active){
                boss->active = 0;
                room->map->status = 0;
                room->map->room[room->map->height/2][room->map->width/2] = 'N';
            }
            if(room->type == 0 && room->map->status == 1){
                if(delay_boss >= boss->delay){ 
                    monsterAI(floor,room->monster_list,&player,&projectiles);
                    delay_boss = 0.0;            
                }else{
                    delay_boss += 1.0;
                }
                if(checkKills(room->monster_list)){
                    room->map->status = 0;
                }else{
                    // printMonsters(room->monster_list);
                }
            }
            updateShoots(&projectiles,room->map, &player, boss,room->monster_list);
            system("@cls||clear");
            displayRoom(room->map->room,room->map->height,room->map->width,player,projectiles, *boss, room->monster_list);
            if(player.tirRate - (frame - player.lastShot) <= 0) player.reloading = 1;
            if ( _kbhit() ){
                dir = _getch();
                movePlayer(floor,&player,dir);
                if(player.nextLevel && level < 5){
                    floor = newFloor(level);
                    boss = newBoss(level++);
                    delay_boss = boss->delay;
                    player.nextLevel = 0;
                    player.lastShot = 0.0;
                    player.roomX = (floor->size-1)/2;
                    player.roomY = (floor->size-1)/2;
                    player.facing = 'z';
                    player.x = (getRoomByCoord(
                                floor->list,
                                (floor->size-1)/2,
                                (floor->size-1)/2
                                )->map->width - 1) / 2;
                    player.y = (getRoomByCoord(
                                floor->list,
                                (floor->size-1)/2,
                                (floor->size-1)/2
                                )->map->height - 1) / 2;
                    printFloor(*floor);
                    checkDoors(floor);
                    nextStep(floor,player, projectiles, *boss);
                    frame = 1.0;
                    getch();
                }
                if(dir == 32){
                    if(player.reloading){
                        shoot(&projectiles,player.x,player.y,player.facing, 'o');
                        player.reloading = 0;
                        player.lastShot = frame;
                    }
                }
                if(dir == 'k')killAll(room->monster_list);
            }
            if(invulnerability >= SAFE){
                if(room->map->room[player.y][player.x] == 'S'){
                    if(looseHealth(1,&player)){
                        invulnerability = 0.0;
                    }else{
                        break;
                    }
                }
            }else{
                invulnerability += 1.0;
            }
            frame += 1.0;
        }
        if(!checkHealth(player))break;
        frame += 1.0/SPEED;
    }
    // printShoots(projectiles);
    // printf("%d",shootsLength(projectiles));
    freeFloor(floor);


    return 0;
}