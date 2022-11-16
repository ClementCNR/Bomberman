#include "structs.h"
#include <stdlib.h>

#ifndef PROJET_CONTROLLER_H
#define PROJET_CONTROLLER_H

Map modifyMapPlayer(Map map, Player myPlayer);

Player move_player(Map map, Player *player, char move, Game myGame);

Player items_take(Map map, Player *player, Game myGame);

int check_bombpass(Player *player);

int check_bombkick(Player *player);

Player shot_bomb(Player *myPlayer, Game myGame, int posX, int posY, char direction);

void movePlayerUp(Node *playerList, int playerToMoveID);

void movePlayerDown(Node *playerList, int playerToMoveID);

// Permet de poser une bomb
Player put_bomb(Player *myPlayer, Game myGame, Bomb aBomb);

void movePlayerLeft(Node *playerList, int playerToMoveID);

// Explosion des bombes
void bomb_blast(Map map, Player myPlayer, Game myGame);

void movePlayerRight(Node *playerList, int playerToMoveID);

int check_bomb(Player myPlayer, Game myGame);

int checkPlayerAlive(Node *playerList);

void killPlayer(Node *playerList, int playerToKillID);

// return 10 for non item spawn, else between 0 and 9 (see define in struct.h)
int randItemSpawn();

#endif //PROJET_CONTROLLER_H
