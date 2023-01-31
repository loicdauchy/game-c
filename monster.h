#ifndef MONSTER_H
#define MONSTER_H

#include "shooter.h"
#include "player.h"
struct MONSTER{
    int x;
    int y;
    int fly;
    int ss;
    int damage;
    int health;
    int type;
    int ind;
    int alive;
    double delay;
};
typedef struct MONSTER MONSTER;

struct MONSTER_LIST{
    int roomX;
    int roomY;
    int size;
    MONSTER* monster;
    struct MONSTER_LIST* last;
};
typedef struct MONSTER_LIST MONSTER_LIST;

typedef struct MAP MAP;
typedef struct PLAYER PLAYER;
typedef struct SHOOT SHOOT;

/** Spawning des monstres
 * 
 * @param size Nombre de monstres
 * @param roomX Coordonnée X de la pièce
 * @param roomY Coordonnée Y de la pièce
 * @param map Pièce ciblée
 * 
 * @return Liste de monstres
*/
MONSTER_LIST* spawn(int size, int roomX, int roomY, MAP *map);

/** Instanciation d'un monstre
 * 
 * @param map Pièce concernée
 * 
 * @return Nouveau monstre
*/
MONSTER* newMonster(MAP* map);

/** Récupération d'un monstre
 * 
 * @param id Identifiant du monstre
 * @param map Piéce ciblée
 * @param ind Index du monstre dans la liste
 * 
 * @return Monstre récupéré
*/
MONSTER* getMonster(int id, MAP* map, int ind);

/** Affichage de la liste des monstres
 * 
 * @param monster_list Liste des monstres à afficher
*/
void printMonsters(MONSTER_LIST* monster_list);

/** Affichage des informations d'un monstre
 * 
 * @param monster_liste Liste des monstres
*/
void printMonster(MONSTER_LIST* monster_list);

/** Récupération du nombre de monstres disponibles
 * 
 * @return Le nombre de monstres disponibles dans le fichier monster.tbob
*/
int getNbMonster(void);

/** Vérification de l'existence d'un monstre en fonction de ses coordonnées
 * 
 * @param monster_list Liste des monstres
 * @param x Coordonnée x
 * @param y Coordonnée y
 * 
 * @return Booléen
*/
int getMonsterByCoord(MONSTER_LIST* monster_list, int x, int y);

/** Perte de points de vie d'un monstre
 * 
 * @param hp Dégats à infliger
 * @param monster Monstre ciblé
 * 
 * @return Booléen
*/
int looseHealthMonster(int hp, MONSTER *monster);

/** Vérification des points de vie d'un monstre
 * 
 * @param monster Monstre ciblé
 * 
 * @return Booléen
*/
int checkHealthMonster(MONSTER *monster);

/** Dégats au monstre en fonction des coordonnées
 * 
 * @param damage Dégats à infliger
 * @param monster_list Liste des monstres
 * @param x Coordonnée x
 * @param y Coordonnée y
*/
void hitMonsterByCoord(int damage, MONSTER_LIST* monster_list, int x, int y);

/** Récupération de la taille de la liste de monstre
 * 
 * @param monster_list Liste de monstres
 * 
 * @return Taille de la liste
*/
int monsterLength(MONSTER_LIST* monster_list);

/** Vérifications des morts
 * 
 * @param monster_list Liste des monstres
 * 
 * @return Booléen
*/
int checkKills(MONSTER_LIST* monster_list);

/** IA des monstres
 * 
 * @param floor Étage en cour
 * @param monster_list Liste des monstres
 * @param player Joueur
 * @param projectiles Liste des tirs
*/
void monsterAI(Floor* floor, MONSTER_LIST *monster_list, PLAYER *player, SHOOT** projectiles);

/** Check de collision du monstre
 * 
 * @param room Pièce en cour
 * @param player Joueur
 * @param monster Monstre ciblé
 * @param dir Direction souhaitée
 * 
 * @return Booléen
*/
int checkCollisionMonster(char** room,PLAYER *player, MONSTER* monster, char dir);

/** ORDER 66
 * 
 * @param monster_list Liste des monstres
*/
void killAll(MONSTER_LIST* monster_list);


#endif