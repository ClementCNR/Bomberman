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


    /*Map activeMap = map(3);

    Node *node = NULL;
    node = initPlayerList(node, activeMap);
    ll_print(node);
    ll_free(node);*/



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
    movePlayerUp(node, 2);
    movePlayerDown(node, 1);

    printMapGame(myMap, node);
    ll_print(node);
    scanf("%d", &mapNumber);


    exit(0);

    /*  ================================ Player Section ================================ */
    /*while (map.nb_player =! 1){
        // Turn play
        // Move Player
        // Action en lien
        // Si mort décrement map.nplayer
    }*/
    Player player1;
    player1.playerID = 1;
    player1.place_x = 1;
    player1.place_y = 1;
    player1.alive = 1;
    char mover;
    scanf("%c", &mover);
    move_player(myMap, player1, mover);
    system("cls");
    printMap(myMap);
    scanf("%c", &mover);

    return 0;

    // https://stackoverflow.com/questions/41383062/c-how-to-break-scanf-with-no-enter-and-no-string
}
