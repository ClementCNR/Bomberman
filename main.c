#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> // used for rand
#include "lib/view.h"
#include "lib/model.h"
#include "lib/controller.h"

#define CMD_WIDE 120

int arraySum(int *tab, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += tab[i];
    }
    return sum;
}

int main(){
    Player player1;
    player1.playerID = 0;
    player1.alive = 1;
    player1.heart = 1;
    player1.place_x = 1;
    player1.place_y = 1;
    Map myMap;
    Game myGame;
    myGame.statusGame = 1;
    int nbMapInDir = nbMapFile();
    if(nbMapInDir==0){
        printf("\nNo map files where found.\nPlease verify the integrity of the project.\n");
        return -1;
    }
    int lastPlayedMap = 0;

    // Nombre de joueur dans la partie
    scanf("%d", &myGame.playerNumber);

    int selection[nbMapInDir];
    for(int i=0; i<nbMapInDir; i++){
        selection[i] = 0;
    }

    // MAPS SELECTION LOOP
    int mapNumber = -1;
    while(mapNumber != 0 && arraySum(selection, nbMapInDir) == 0){

        if (mapNumber >= 1 && mapNumber <= nbMapInDir){

            if (selection[mapNumber - 1] != 1){
                selection[mapNumber - 1] = 1;
            }
            else {
                selection[mapNumber - 1] = 0;
            }
        }

        system("cls");
        printAllMaps();
        printf("\n === Select 1 or more maps (between 1 and %d) ===", nbMapInDir);
        printf("\n    === Enter 0 to validate your selection ===\n\n");

        printf("\n\nSelected maps at the moment : ");
        for (int i=0; i<=nbMapInDir; i++){
            if (selection[i] == 1){
                printf("%d ", i+1);
            }
        }
        printf("\n");

        scanf("%d", &mapNumber);
    }
    //================================================================================================+
    // THE PLAYER SELECTED THE MAPS WHERE HE WANTED TO PLAY                                           |
    // NOW WE PICK A RANDOM MAP IN THIS SELECTION WHILE AVOIDING TO PICK THE LAST PLAYED MAP          |
    //================================================================================================+

    system("cls");

    //printf("\nmapNumber = %d\n", mapNumber);
    srand(time(NULL));
    do {
        mapNumber = (rand() % nbMapInDir) + 1;
    } while (selection[mapNumber-1] != 1 && mapNumber != lastPlayedMap);
    lastPlayedMap = mapNumber;
    myMap = map(mapNumber);


    printMap(myMap,player1);


    for(int i = 0; i < CMD_WIDE; i++) {
        printf("=");
    }

    printf("\n\n");


    scanf("%d", &mapNumber);

    /*  ================================ Start Section ================================ */

    if (myGame.playerNumber != 0 && mapNumber != NULL){
        myGame.statusGame = 1;
    }

    /*  ================================ Player Section ================================ */
    if (myGame.statusGame == 1){
        myGame.turn = 0;
        char mover, ac;
        //while (myGame.statusGame){
                scanf("%c", &mover);
                move_player(myMap, &player1, mover);
                printMap(myMap,player1);
                //items_take(myMap, player1);
                /*scanf("%c", &ac);
                switch (ac){
                    case 'b': put_bomb(myMap ,  Player , );
                    case 'r': /* Ne rien faire ;
                }*/
                // Si mort décrement map.nplayer
                myGame.turn++;
        //}
        system("cls");
        return 0;

    }


    // https://stackoverflow.com/questions/41383062/c-how-to-break-scanf-with-no-enter-and-no-string
}
