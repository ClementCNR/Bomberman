//
// Created by Clément on 28/10/2022.
//

// Return a Map struct from the file

#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include <string.h>


Map map(int mapNumber){
    // FORMATAGE DU NOM DU FICHIER DE MAP
    char mapFilename[20] = "maps/map_";
    char temp[5];
    sprintf(temp,"%d",mapNumber);

    strcat(mapFilename, temp);
    strcat(mapFilename, ".txt");

    Map map;

    // OUVERTURE DU FICHIER ET TEST
    FILE *file = fopen(mapFilename, "r");

    if (file == NULL) {

        map.defaultBomb = 0;
        map.columns = 0;
        map.rows = 0;
        //map.map = "";
        return map;
    }
    char line[1024];

    fgets(line, 1024, file);

    map.defaultBomb = atoi(&line[0]);

    fgets(line, 1024, file);

    map.columns = atoi(strtok(line, " "));
    map.rows = atoi(strtok(line, " "));

    // CREATION DU TABLEAU EN 2D
    char** tab = malloc(map.rows * sizeof(char*));
    for(int i = 0; i < map.rows; i++){
        tab[i] = malloc(map.columns * sizeof(char));
    }
    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++){
            tab[i][j] = 0;
        }
    }

    char letter = ' ';
    int nbPlayer = 0;
    Player player;

    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++) {
            letter = fgetc(file);
            if(letter != '\n') {
                if(letter == 'p'){
                    nbPlayer++;
                }
                tab[i][j] = letter;
            }
        }
        fgetc(file);
    }

    map.map = tab;
    map.maxPlayer = nbPlayer;

    fclose(file);

    return map;
}

// Return the number of map created by checking the maps directory
int nbMapFile(){

    int mapNumber = 1;
    FILE *file;

    char mapBaseFilename[20] = "maps/map_";
    char mapFilename[20];

    strcpy(mapFilename, mapBaseFilename);
    char temp[5];
    sprintf(temp,"%d",mapNumber);

    strcat(mapFilename, temp);
    strcat(mapFilename, ".txt");

    file = fopen(mapFilename, "r");


    while (file != NULL){
        mapNumber++;
        sprintf(temp,"%d",mapNumber);

        strcpy(mapFilename, mapBaseFilename);
        strcat(mapFilename, temp);
        strcat(mapFilename, ".txt");

        fclose(file);
        file = fopen(mapFilename, "r");
    }

    return mapNumber - 1;
}

Node *ll_push_front(Node *first, Player newPlayer){
    Node *new = malloc(sizeof(Node));
    new->player = newPlayer;
    new->next = first;
    return new;
}

Node *ll_add_last(Node *first, Player newPlayer){
    Node *newNode = malloc(sizeof(Node));
    newNode->player = newPlayer;
    newNode->next = NULL;

    //if head is NULL, it is an empty list
    if(first == NULL){
        first = newNode;
    }
        //Otherwise, find the last node and add the newNode
    else
    {
        Node *lastNode = first;


        //last node's next address will be NULL.
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        //add the newNode at the end of the linked list
        lastNode->next = newNode;


    }
}


BombList *ll_push_bomb(BombList *first, Bomb aBomb){
    BombList *new = malloc(sizeof(BombList));
    new->aBomb = aBomb;
    new->next = first;
    return new;
}

//  ll add last
void ll_free(Node *first){
    if(first != NULL){
        ll_free(first->next);
        free(first);
    }
}

void ll_free_bomb(BombList *first){
    if(first != NULL){
        ll_free_bomb(first->next);
        free(first);
    }
}

void ll_print(Node *first){
    while(first != NULL){
        printf("player ID = %d / pos = %d - %d\n", first->player.playerID, first->player.place_y, first->player.place_x);
        first = first->next;

    }
}

Node *initPlayerList(Node *first, Map map){

    int playerID = map.maxPlayer;
    Player player;
    player.alive = 1;
    player.maxBomb = map.defaultBomb;
    player.live = 1;
    player.invincible = 0;
    player.heart = 1;
    player.pass_bomb = 0;
    player.bomb_kick = 0;
    player.yellow_fire = 0;
    player.red_fire = 0;
    player.blue_fire = 0;
    player.bomb_range = 2;
    BombList bomb;
    bomb.aBomb.idBomb = -1;
    bomb.aBomb.turnPut = -1;
    bomb.aBomb.place_x = -1;
    bomb.aBomb.place_y = -1;
    bomb.next = NULL;

    player.list_bomb = bomb;


    for(int i = map.rows - 1; i >= 0; i--){
        for(int j = map.columns - 1; j >= 0; j--){
            if(map.map[i][j] == 'p'){

                player.playerID = playerID;
                player.place_x = i;
                player.place_y = j;
                first = ll_push_front(first, player);
                //first = ll_add_last(first, player);
                playerID--;
            }
        }
    }

    return first;

}

void destroyWall(Map *map, int x, int y){
    for(int i = 0; i < map->rows; i++){
        for(int j = 0; j < map->columns; j++) {
            if(i == x && j == y){
                map->map[i][j] = ' ';
            }
        }
    }
}


void placeBomb(Map *map, int x, int y){

    map->map[x][y] = 'b';
    /*for(int i = 0; i < map->rows; i++){
        for(int j = 0; j < map->columns; j++) {
            if(i == x && j == y){
                map->map[i][j] = 'b';
            }
        }
    }*/
}

void removeP(Map *map){
    for(int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->columns; j++) {
            if(map->map[i][j] == 'p'){
                map->map[i][j] = ' ';
            }
        }
    }
}


