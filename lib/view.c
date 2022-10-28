//
// Created by Clément on 28/10/2022.
//
#include <Windows.h>
#include <stdio.h>

#include "view.h"
#include "colors.h"
#include "model.h"

// Take a Map struct and print it to stdout
void printMap(Map map){
    //system("cls");
    //purple();
    SetConsoleOutputCP(65001);
    char  *breakable = "▒";
    char *unbreakable = "█";

    int nbPlayer = 1;

    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++){

            if(map.map[i][j] == 'p'){
                white();
                printf("%d", nbPlayer);
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

    for(int i = 1; i <= nbMap; i++){
        printf("\n === Map number %d ===\n\n", i);
        printMap(map(i));
    }
}