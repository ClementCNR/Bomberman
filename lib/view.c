//
// Created by Clément on 28/10/2022.
//
#include <Windows.h>
#include <stdio.h>

#include "view.h"
#include "colors.h"
#include "model.h"

// Take a Map struct and print it to stdout
void printMap(Map map, Player myPlayer){
    //system("cls");
    //purple();
    SetConsoleOutputCP(65001);
    char  *breakable = "▒";
    char *unbreakable = "█";

    int nbPlayer = 1;

    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++){

            if (map.map[myPlayer.place_x][myPlayer.place_y] == map.map[i][j]) {
                white();
                //map.map[i][j] = myPlayer.playerID;
                printf("%d", myPlayer.playerID);
            }
            if(map.map[i][j] == 'p'){
                printf(" ");
                nbPlayer++;
            }
            else if (map.map[i][j] == 'x'){
                red();
                printf("%s", unbreakable);
            }
            else if (map.map[i][j] == 'm'){
                cyan();
                printf("%s", breakable);
            }
            else{
                printf("%c", map.map[i][j]);
            }

            reset();
        }
        printf("\n");


    }
}

// Display all the maps
void printAllMaps(){
    int nbMap = nbMapFile();
    Player player1;
    for(int i = 1; i <= nbMap; i++){
        printf("\n === Map number %d ===\n\n", i);
        printMap(map(i) , player1);
    }
}