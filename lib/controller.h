#include "structs.h"
#include <stdlib.h>

#ifndef PROJET_CONTROLLER_H
#define PROJET_CONTROLLER_H


// petite fct qui renvoie l ID d un item si un item spawn
int spawnItem();

// call 1 fois apres la creation de la map
Player initPlayer();

int move_player(Map map, Player player, char move);

Player items_take (Map map, int columns,int line,int item_place, Player player);

void movePlayerUp(Node *playerList, int playerToMoveID);

void movePlayerDown(Node *playerList, int playerToMoveID);

void movePlayerLeft(Node *playerList, int playerToMoveID);

void movePlayerRight(Node *playerList, int playerToMoveID);

int checkPlayerAlive(Node *playerList, int playerToCheckID);

void killPlayer(Node *playerList, int playerToKillID);

// return 10 for non item spawn, else between 0 and 9 (see define in struct.h)
int randItemSpawn();

#endif //PROJET_CONTROLLER_H
