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
    Player player1;
    for(int i = 1; i <= nbMap; i++){
        printf("\n === Map number %d ===\n\n", i);
        printMap(map(i));
    }
}

// Pretty land page, enter 0 to exit the game
void printHomePage(){
    system("cls");
    bomberman();

    printf("=============== PRESS 0 TO QUIT ================\n\n");

    int input = 0;
    scanf("%d", &input);

    if(input == 0){
        exit(0);
    }

}

// Choice between solo, host or join a game
int mainMenu(){
    int result = 0;
    while(result < 1 || result > 4){
        system("cls");
        bomberman();
        printf("================== Main Menu ===================\n\n");

        printf("1 - Solo Game\n\n");
        printf("2 - Host a Game\n\n");
        printf("3 - Join a Game\n\n");
        printf("4 - Quit\n\n");

        scanf("%d", &result);


    }
    return result;

}

// ASCII Art BOMBERMAN
void bomberman(){
    red();
    printf(" ___  ___  __  __ ___ ___ ___ __  __   _   _  _\n");
    yellow();
    printf("| _ )/ _ \\|  \\/  | _ ) __| _ \\  \\/  | /_\\ | \\| |\n");
    green();
    printf("| _ \\ (_) | |\\/| | _ \\ _||   / |\\/| |/ _ \\| .` |\n");
    blue();
    printf("|___/\\___/|_|  |_|___/___|_|_\\_|  |_/_/ \\_\\_|\\_|\n\n");
    reset();
}

// print map but p = ' ' and if find a player with x y, print player id
void printMapGame(Map map, Node *playerList){
    //system("cls");
    //purple();
    SetConsoleOutputCP(65001);
    char *breakable = "▒";
    char *unbreakable = "█";
    char *bomb = "ó";

    Node *loop = playerList;
    int found = 0;

    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++){

            loop = playerList;
            found = 0;
            while(loop != NULL){
                if(loop->player.place_x == i && loop->player.place_y == j){
                    if(loop->player.alive == 0){
                        found = 1;
                        break;
                    }
                    white();
                    printf("%d", loop->player.playerID);
                    found = 1;
                    break;
                }
                loop = loop->next;
            }

            if(found == 1){}
            else if(map.map[i][j] == 'p'){
                white();
                printf(" ");
            }
            else if (map.map[i][j] == 'x'){
                red();
                printf("%s", unbreakable);
            }
            else if (map.map[i][j] == 'm'){
                cyan();
                printf("%s", breakable);
            }
            else if (map.map[i][j] == 'b'){
                yellow();
                printf(bomb);
            }
            else{
                printf("%c", map.map[i][j]);
            }

            reset();
        }
        printf("\n");


    }
}

// HUD with player info
void playerInfo(Node *playerList){

    int player = 0;
    while(playerList != NULL){
        player++;
        playerList = playerList->next;
    }
}

