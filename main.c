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


    printHomePage();
    int mainMenuSelection;
    mainMenuSelection = mainMenu();
    if(mainMenuSelection == 4){
        exit(0);
    }


    Map myMap;
    int nbMapInDir = nbMapFile();
    if(nbMapInDir==0){
        system("cls");
        printf("\nNo map files where found.\nPlease verify the integrity of the project.\n");
        return -1;
    }
    int lastPlayedMap = 0;

    int selection[nbMapInDir];
    for(int i=0; i<nbMapInDir; i++){
        selection[i] = 0;
    }

    // MAPS SELECTION LOOP
    int mapNumber = -1;
    while(mapNumber != 0 || arraySum(selection, nbMapInDir) == 0){

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

    Node *node = NULL;
    node = initPlayerList(node, myMap);


    printMap(myMap);


  /*  for(int i = 0; i < CMD_WIDE; i++) {
        printf("=");
    }*/

    printf("\n\n");


    scanf("%d", &mapNumber);


    //node->player.place_y--;
    movePlayerDown(node, 1);
    movePlayerUp(node, 1);
    movePlayerDown(node, 1);

    system("cls");
    printMapGame(myMap, node);
    ll_print(node);


    scanf("%d", &mapNumber);


    printf("joueur %d : %d", node->player.playerID, node->player.alive);

    scanf("%d", &mapNumber);

    ll_free(node);
    exit(0);

    /*  ================================ Player Section ================================ */
    if (myGame.statusGame == 1){
        myGame.turn = 0;
        char mover;
        char ac;
        while (myGame.statusGame ){
            for (int i = 0; i < 1; i++){
                scanf("%c", &mover);
                move_player(myMap, /* Work ing progress */, mover);
                items_take(myMap, /*player*/);
                scanf("%c", &ac);
                switch (ac){
                    case ' ': put_bomb(myMap , /* Player */);
                    case 'r': /* Ne rien faire*/ ;
                }
                // Si mort décrement map.nplayer
                myGame.turn++;
            }
        }
        system("cls");
        printMap(myMap);
        scanf("%c", &mover);
    }

    return 0;

    // https://stackoverflow.com/questions/41383062/c-how-to-break-scanf-with-no-enter-and-no-string
}
