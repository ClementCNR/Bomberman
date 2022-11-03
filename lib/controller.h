//
// Created by Clément on 31/10/2022.
//
#include "structs.h"

#ifndef PROJET_CONTROLLER_H
#define PROJET_CONTROLLER_H

// fct globale appelée apres chaque input d un joueur, qui renvoie la map avec des modifs (joueur qui bouge, bombe posée ...)
Map modifyMapPlayer(Map map, Game myGame, char keyPressed, Player myPlayer){
    for (int i = 0; i < myGame.playerNumber ; ++i) {
        map.map[myPlayer.place_x][myPlayer.place_y] = myPlayer.playerID;
    }
    return map;
}

// fonction destruction d'un mur
Map modifyMapWall(Map map, Game myGame, char keyPressed, Player myPlayer);/*{
    if (map.map[bomb.touch_x][bomb.touch_x] == 'm' ) {
        map.map[bomb.touch_x][bomb.touch_x] == ' ';
    }
}*/

// petite fct qui renvoie l ID d un item si un item spawn
int spawnItem();

// call 1 fois apres la creation de la map
Player initPlayer();

// Permet de poser une bomb
int put_bomb(Map myMap, Player myPlayer);

// Explosion des bombes
int bomb_blast(Map myMap, Player myPlayer );




#endif //PROJET_CONTROLLER_H
