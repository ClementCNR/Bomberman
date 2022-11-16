#include "controller.h"
#include <stdio.h>
#include <time.h> // used for rand
#include <stdlib.h>


// Player moving
int move_player(Map map, Player player, char move){
    // IMPORTANT ajouter la vérification des items pour les bombs etc
    if (move == 'z') { // Up mouvement
        if( map.map[player.place_x][player.place_y-1] != 'x' && map.map[player.place_x][player.place_y-1] != 'm' && map.map[player.place_x][player.place_y-1] != 'p') {
            player.place_y--;
        }
    }else if (move == 'q') { // Left move
        if( map.map[player.place_x-1][player.place_y] != 'x' && map.map[player.place_x-1][player.place_y] != 'm' && map.map[player.place_x-1][player.place_y] != 'p') {
            player.place_x--;
        }
    }else if(move == 's') { // Down move
        if( map.map[player.place_x][player.place_y+1] != 'x' && map.map[player.place_x][player.place_y+1] != 'm' && map.map[player.place_x][player.place_y+1] != 'p') {
            player.place_y++;
        }
    }else if(move == 'd') { // Right move
        if( map.map[player.place_x+1][player.place_y] != 'x' && map.map[player.place_x+1][player.place_y] != 'm' && map.map[player.place_x+1][player.place_y] != 'p') {
            player.place_x++;
        }
    }
}


// Add Item for player
Player items_take (Map map, int columns,int line,int item_place, Player player) {
    // Important revoir la fonction uen fois la structure Items utiliser
    int player_y = player.place_y;
    int player_x = player.place_x;
    if (map.map[player_x][player_y] != 'p' && map.map[player_x][player_y] != ' ' && map.map[player_x][player_y] != 'n') {
        return player;
    }else if (map.map[player_x][player_y] == 'b'){ // b = une bombe en plus
        player.maxBomb++;
    }else if (map.map[player_x][player_y] == 'd'){ // d = une bombe en moins
        player.maxBomb--;
    }else if (map.map[player_x][player_y] == 'c') { // c = portée +1
        player.bomb_range++;
    }else if(map.map[player_x][player_y] == 'e') { // e = portée -1
        player.bomb_range--;
    }else if(map.map[player_x][player_y] == 'r'){ // r = portée max
        // appel fonction pour mettre la valuer de la bombe au max
        // au colonne si il y  a plus de colonne ou de ligne ou autre
    }else if (map.map[player_x][player_y] == 'l' && player.heart == 0 ) { // l = heart
        player.heart++;
    }else if (map.map[player_x][player_y] == 'i'){ // i = invincible
        // Wait turn playing
    }else if(map.map[player_x][player_y] == 'p'){ // p = pass_bomb
        if (player.bomb_kick == 1) { // Check si possede l'item de pousser les bomb
            player.bomb_kick = 0; // retire l'item bomb kick
        }
        player.pass_bomb = 1;
    }
    else if(map.map[player_x][player_y] == 'k'){ // k = bomb_kick
        if (player.pass_bomb == 1) { // Check si possede l'item de passer sur les bomb
            player.pass_bomb = 0; // retire l'item de passer sur les bombes
        }
        player.bomb_kick = 1;
    }
}


void movePlayerUp(Node *playerList, int playerToMoveID){
    while(playerList != NULL){
        if(playerList->player.playerID == playerToMoveID){
            playerList->player.place_x--;
            break;
        }
        playerList = playerList->next;
    }
}

void movePlayerDown(Node *playerList, int playerToMoveID){
    while(playerList != NULL){
        if(playerList->player.playerID == playerToMoveID){
            playerList->player.place_x++;
            break;
        }
        playerList = playerList->next;
    }
}

void movePlayerLeft(Node *playerList, int playerToMoveID){
    while(playerList != NULL){
        if(playerList->player.playerID == playerToMoveID){
            playerList->player.place_y--;
            break;
        }
        playerList = playerList->next;
    }
}

void movePlayerRight(Node *playerList, int playerToMoveID){
    while(playerList != NULL){
        if(playerList->player.playerID == playerToMoveID){
            playerList->player.place_y++;
            break;
        }
        playerList = playerList->next;
    }
}

int checkPlayerAlive(Node *playerList){
    while(playerList != NULL){
        if(playerList->player.alive == 1){
            return 1;
        }
        playerList = playerList->next;
    }
    return 0;
}

void killPlayer(Node *playerList, int playerToKillID){
    while(playerList != NULL){
        if(playerList->player.playerID == playerToKillID){
            playerList->player.alive = 0;
        }
        playerList = playerList->next;
    }
}

// return 10 for non item spawn, else between 0 and 9 (see define in struct.h)
int randItemSpawn(){
    srand(time(NULL));
    if(rand() % 3 < 2){
        return 10;
    }
    else{
        srand(time(NULL));
        return rand() % 10;
    }

}
