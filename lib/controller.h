//
// Created by Clément on 31/10/2022.
//
#include "structs.h"

#ifndef PROJET_CONTROLLER_H
#define PROJET_CONTROLLER_H

Map modifyMapPlayer(Map map, Player myPlayer);

Map modifyMapWall(Map map, Game myGame, char keyPressed, Player myPlayer);

Map modifyPlayerDie(Map myMap, Game myGame, Player myPlayer);

Player move_player(Map map, Player *player, char move, Game myGame);

Player items_take(Map map, Player *player, Game myGame);

int check_bombpass(Player *player);

int check_bombkick(Player *player);

Player shot_bomb(Player *myPlayer, Game myGame, int posX, int posY, char direction);


// petite fct qui renvoie l ID d un item si un item spawn
int spawnItem();

// call 1 fois apres la creation de la map
Player initPlayer();

// Permet de poser une bomb
Player put_bomb(Player *myPlayer, Game myGame, Bomb aBomb);

// Explosion des bombes
void bomb_blast(Map map, Player myPlayer, Game myGame);

int check_bomb(Player myPlayer, Game myGame);



#endif //PROJET_CONTROLLER_H
