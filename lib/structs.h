//
// Created by Clément on 28/10/2022.
//

#ifndef PROJET_STRUCTS_H
#define PROJET_STRUCTS_H

typedef struct{
    int defaultBomb;
    int columns;
    int rows;
    char **map;
}  Map;

typedef struct{
    int idBomb;
    int turnPut;
    int place_x;
    int place_y;
}Bomb;

typedef struct{
    int playerID;
    int place_x;
    int place_y;
    int alive;
    int maxBomb;
    int live;
    int invincible;
    int invincible_take;
    int heart;
    int pass_bomb;
    int bomb_kick;
    int yellow_fire;
    int red_fire;
    int blue_fire;
    int bomb_range;
    Bomb *list_bomb;
    // Items *list_items;
} Player;

typedef struct{
    int statusGame;
    int playerNumber;
    int turn;
    Map mapPlayed;
    Player **playerList;
} Game;

typedef struct{

} List;

/* typedef struct {
        int live;
        int invincible;
        int heart;
        int pass_bomb;
        int bomb_kick;
        int yellow_fire;
        int red_fire;
        int blue_fire;
        int bomb_up;
        int bomb_down;
    } Items;
*/

#endif //PROJET_STRUCTS_H
