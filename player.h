/** Génération du joueur
 * Date 26/10/2022
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "floor.h"
#include "map.h"
#include "player.h"

struct PLAYER{
    int x;
    int y;
    int fly;
    int ss;
    double tirRate;
    int damage;
    double lastShot;
    int reloading;
    int roomX;
    int roomY;
    char facing;
    int health;
    int shield;
    int nextLevel;
};
typedef struct PLAYER PLAYER;

typedef struct Floor Floor;

/** Déplacement du joueur
 * @param floor étage
 * @param player joueur
 * @param dir direction
*/
void movePlayer(Floor* floor, PLAYER* player, char dir);

/** Vérification des collisions
 * @param room pièce
 * @param player joueur
 * @param dir direction
 * @param status Status de la pièce
 * @return booleen de possibilité de déplacement
*/
int checkCollision(char** room, PLAYER* player, char dir, char status);

/** Perte de points de vie du joueur
 * 
 * @param hp Dégats à infliger
 * @param player Joueur
 * 
 * @return Booléen
*/
int looseHealth(int hp, PLAYER *player);

/** Vérifications des points de vie du joueur
 * 
 * @param player Joueur
 * 
 * @return Booléen
*/
int checkHealth(PLAYER player);

#endif