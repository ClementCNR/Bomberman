//
// Created by Clément on 28/10/2022.
//

#ifndef PROJET_STRUCTS_H
#define PROJET_STRUCTS_H

#define BombUp 1
#define BombDown 2

#define YellowFlame 3
#define BlueFlame 4
#define RedFlame 5

#define BombPass 6
#define Bombkick 7

#define Invicibility 8
#define Heart 9
#define Life 10

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
