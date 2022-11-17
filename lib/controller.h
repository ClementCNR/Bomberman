#include "structs.h"
#include <stdlib.h>

#ifndef PROJET_CONTROLLER_H
#define PROJET_CONTROLLER_H


Player move_player(Map map, Player *player, char move, Game myGame, Node *node);

Player items_take(Player *player, Game myGame, Map map);

int check_bombpass(Player *player);

int check_bombkick(Player *player);

Player shot_bomb(Player *myPlayer, Game myGame, int posX, int posY, char direction);

void movePlayerUp(Node *playerList, int playerToMoveID);

void movePlayerDown(Node *playerList, int playerToMoveID);

// Permet de poser une bomb
void put_bomb(Node *first, Game myGame, int playerPutBomb);

void movePlayerLeft(Node *playerList, int playerToMoveID);

int returnId(Node *playerList, int x, int y);

// Explosion des bombes
void bomb_blast(Map map, Player *myPlayer, Game myGame, Node *playerList);

void movePlayerRight(Node *playerList, int playerToMoveID);

int checkPlayerAlive(Node *playerList, int playerToCheckID);

void check_bomb(Map map, Node *first,Game myGame);

void killPlayer(Node *playerList, int playerToKillID);

// return 10 for non item spawn, else between 0 and 9 (see define in struct.h)
int randItemSpawn();

#endif //PROJET_CONTROLLER_H
