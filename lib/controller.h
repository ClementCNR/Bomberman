//
// Created by Clément on 31/10/2022.
//
#include "structs.h"

#ifndef PROJET_CONTROLLER_H
#define PROJET_CONTROLLER_H

// fct globale appelée apres chaque input d un joueur, qui renvoie la map avec des modifs (joueur qui bouge, bombe posée ...)
Map action(Map map, char keyPressed, int player_ID);

// petite fct qui renvoie l ID d un item si un item spawn
int spawnItem();

// call 1 fois apres la creation de la map
Player initPlayer();

#endif //PROJET_CONTROLLER_H
