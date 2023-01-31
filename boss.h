#ifndef BOSS_H
#define BOSS_H

#include "floor.h"
#include "map.h"
#include "player.h"
#include "boss.h"
#include "shooter.h"
#include <stdio.h>
#include <stdlib.h>

#define DELAY_BOSS 10.0 //frames entre chaque action du boss

struct BOSS_MONSTER{
    int x;
    int y;
    int fly;
    int ss;
    int damage;
    double tirRate;
    double lastShot;
    int reloading;
    char facing;
    int health;
    int type;
    int active;
    int alive;
    double delay;
};
typedef struct BOSS_MONSTER BOSS_MONSTER;

typedef struct Floor Floor;
typedef struct PLAYER PLAYER;
typedef struct RoomItem RoomItem;
typedef struct SHOOT SHOOT;


/** Instance d'un boss
 * 
 * @param floor level en cour
 * @return Un nouveau boss
*/
BOSS_MONSTER* newBoss(int floor);

/** IA des différents boss
 * 
 * @param floor étage en cour
 * @param boss boss à manipuler
 * @param player joueur
 * @param projectiles liste des tirs
*/
void bossAI(Floor* floor, BOSS_MONSTER *boss, PLAYER *player, SHOOT** projectiles);

/** Check des collisions du boss
 * 
 * @param room tableau de caractères de la pièce
 * @param player joueur
 * @param boss boss à verifier
 * @param dir direction à checker
 * @return booléen
*/
int checkCollisionBoss(char** room,PLAYER *player, BOSS_MONSTER* boss, char dir);

/** Perte de vie du boss
 * 
 * @param hp points de vie à faire perdre
 * @param boss boss ciblé
 * @return Un booléen
*/
int looseHealthBoss(int hp, BOSS_MONSTER *boss);

/** Vérification des vies du boss
 * 
 * @param boss boss ciblé
 * @return Un booléen
*/
int checkHealthBoss(BOSS_MONSTER *boss);




#endif