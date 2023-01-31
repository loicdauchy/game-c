#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "map.h"
#include "floor.h"
#include "player.h"
#include "boss.h"
#include "shooter.h"

#define SPEED 1500
#define SAFE 5.0

/** Lancement du jeu
 * @return Erreur
*/
int play(void);

#endif