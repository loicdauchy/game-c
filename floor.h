/** Génération d'un étage de "The Binding of Briatte"
 * Date : 23/10/2022
*/

#ifndef FLOOR_H
#define FLOOR_H

#include "map.h"
#include "player.h"
#include "boss.h"
#include "shooter.h"
#include "monster.h"
#include "floor.h"

#define BOSS 'B' 
#define SPAWN 'S' 
#define ROOM 'R' 
#define ITEM 'I' 
#define EMPTY ' ' 

struct RoomItem {
    int x;
    int y;
    int id;
    int ind;
    int type;
    MONSTER_LIST* monster_list;
    struct MAP * map;
    struct RoomItem * last;
};
typedef struct RoomItem RoomItem;

struct Floor {
    char** chunck;
    int stage;
    int size;
    int curX;
    int curY;
    RoomItem* list;
};
typedef struct Floor Floor;


typedef struct BOSS_MONSTER BOSS_MONSTER;
typedef struct MONSTER MONSTER;
typedef struct MONSTER_LIST MONSTER_LIST;


/** Instance d'un nouvel étage
 * 
 * @param stage niveau de l'étage
 * @return L'étage instacié
*/
Floor* newFloor(int stage);

/** Affichage d'un étage
 * 
 * @param floor étage à afficher
*/
void printFloor(Floor floor);

/** Ajout d'une pièce à la liste
 * 
 * @param floor étage de la liste
 * @param y position verticale
 * @param x position horizontale
 * @param id id de la pièce à ajouter
 * @param type type de la pièce à ajouter
*/
void addRoom(Floor* floor, int y, int x, int id, int type);

/** Retourne la taille de la liste
 * 
 * @param rooms liste des pièces
 * @return la taille de la liste
*/
int length(RoomItem* rooms);

/** Récupération d'une pièce de la liste
 * 
 * @param rooms liste concernée
 * @param ind index de la pièce
 * @return la pièce
*/
RoomItem* getRoom(RoomItem* rooms, int ind);

/** Vérification de léxistence d'une pièce
 * @param rooms liste des pièces
 * @param x coordonnée x
 * @param y coordonnée y
 * @return 1 pour True 0 pour False
*/
RoomItem* getRoomByCoord(RoomItem* rooms, int x, int y);

/** Affichage de la liste des pièces
 * @param rooms liste des pièces
 * @param player joueur 
*/
void printRooms(RoomItem* rooms, PLAYER player);

/** Affichage d'une pièce
 * @param room pièce à afficher
 * @param player joueur
*/
void printRoom(RoomItem* room, PLAYER player);

/** Alimentation de l'étage
 * @param floor étage
*/
void fillFloor(Floor* floor);

/** Tentative d'ajout d'une pièce
 * @param floor étage
 * @param y coordonnée y
 * @param x coordonnée x
 * @param remain nombre de pièces restantes
 * @param type type de pièce à ajouter
 * @return booléen pour la réussite ou non de l'ajout
*/
int nextRoom(Floor* floor, int y, int x, int * remain, char type);

/** Ajout d'une pièce acollée à une pièce déjà existante
 * @param floor étage
 * @param remain nombre de pièces restantes
 * @param type type de la pièce à ajouter
*/
void placeRoom(Floor* floor, int* remain, char type);

/** Récupération du nombre de voisin d'une pièce
 * @param floor étage
 * @param x coordonnée x
 * @param y coordonnée y
 * @return le nombre de voisins
*/
int getVoisin(Floor* floor, int x, int y);

/** Libération d'une liste 
 * @param list liste à libérer
*/
void freeList(RoomItem* list);

/** Libération d'un étage
 * @param floor étage à libérer
*/
void freeFloor(Floor* floor);

/** Mise à jour des portes de la pièce
 * @param floor étage à mettre à jour
*/
void checkDoors(Floor* floor);

/** Prochaine salle
 * @param floor étage
 * @param player joueur
 * @param shoots liste des tirs
 * @param boss boss
*/
void nextStep(Floor* floor, PLAYER player, SHOOT* shoots, BOSS_MONSTER boss);

#endif