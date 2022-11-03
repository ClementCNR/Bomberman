//
// Created by Clément on 28/10/2022.
//

#ifndef PROJET_STRUCTS_H
#define PROJET_STRUCTS_H

typedef struct{
    int defaultBomb;
    int maxPlayer;
    int columns;
    int rows;
    char **map;
}  Map;

/* typedef struct {
 *      int live;
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

typedef struct{
    int playerID;
    int place_x;
    int place_y;
    int alive;
    int maxBomb;
    int live;
    int invincible;
    int heart;
    int pass_bomb;
    int bomb_kick;
    int yellow_fire;
    int red_fire;
    int blue_fire;
    int bomb_range;
    // Items *list_items;
} Player;

typedef struct Node Node;
struct Node {
    Player player;
    Node *next;
};


typedef struct{
    int statusGame;
    int playerNumber;
    int turn;
    Map mapPlayed;
    Player **playerList;
}  Game;


#endif //PROJET_STRUCTS_H
