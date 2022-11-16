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
    Game myGame;
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




    //  ================================ Player Section ================================

    if (myGame.statusGame == 1){
        myGame.turn = 0;
        char action;
        Node *loop;
        loop = node;
        while (myGame.statusGame){
            while(checkPlayerAlive(loop, loop->player.playerID) == 0) {
                loop = loop->next;
                if(loop == NULL){
                    loop = node;
                }
            }
            printf("Entrée soit r pour ne rien faire ou un espace pour poser une bombe");
            scanf("%c", &action);
            switch (action){
                case ' ': put_bomb( node, myGame, loop->player.playerID);
                    break;
                case 'r':  break;
                case 'default':
                    printf("Entrée soit r pour ne rien faire ou ' ' pour poser une bombe");
                    break;
            }
            printf("Entrée une direction 'zqsd'");
            scanf("%c", &action);
            move_player( myMap, &loop->player, action, myGame);

            bomb_blast( myMap,  &loop->player,  myGame);
            myGame.turn++;
        }
        system("cls");
        printMap(myMap);
    }

    ll_free(node);
    return 0;

    // https://stackoverflow.com/questions/41383062/c-how-to-break-scanf-with-no-enter-and-no-string
}
