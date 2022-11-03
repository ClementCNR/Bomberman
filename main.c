#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> // used for rand
#include "lib/view.h"
#include "lib/model.h"
#include "lib/controller.h"

#define CMD_WIDE 120

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

int arraySum(int *tab, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += tab[i];
    }
    return sum;
}

// Add Item for player
Player items_take(Map map, Player player) {
    // Important revoir la fonction uen fois la structure Items utiliser
    /*if (map.map[player_x][player_y] == 'p' && map.map[player_x][player_y] != ' ' && map.map[player_x][player_y] != 'n') {
        return player;
    }else*/
    switch (map.map[player.place_x][player.place_y]){
        case ('b') : player.maxBomb++;
        case ('d') : player.maxBomb--;
        case ('c') : player.bomb_range++;
        case ('e') : player.bomb_range--;
        case ('r') : // appel fonction pour mettre la valuer de la bombe au max
                     // au colonne si il y  a plus de colonne ou de ligne ou autre
        case ('l') : if (player.heart == 0 ) { // l = heart
                         player.heart++;
                     }
        case ('i') : // Wait turn playing
        case ('p') : if (player.bomb_kick == 1) { // Check si possede l'item de pousser les bomb
                         player.bomb_kick = 0; // retire l'item bomb kick
                     }
                     player.pass_bomb = 1;
        case ('k') : if (player.pass_bomb == 1) { // Check si possede l'item de passer sur les bomb
                         player.pass_bomb = 0; // retire l'item de passer sur les bombes
                     }
                     player.bomb_kick = 1;
    }
    return player;/*
    if (map.map[player_x][player_y] == 'b'){ // b = une bombe en plus
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
    return player;*/
}


// Player moving
Player move_player(Map map, Player player, char move){
    // IMPORTANT ajouter la vérification des items pour les bombs etc
    switch (move){
        case ('z') : if (player.alive >= 1 ) { // Up mouvement
                        if (map.map[player.place_x][player.place_y - 1] != 'x' &&
                            map.map[player.place_x][player.place_y - 1] != 'm' &&
                            map.map[player.place_x][player.place_y - 1] != 'p') {
                            player.place_y--;
                            items_take(map, player);
                        }
                     }
        case ('q') : if (player.alive >= 1) { // Left move
                        if (map.map[player.place_x - 1][player.place_y] != 'x' &&
                            map.map[player.place_x - 1][player.place_y] != 'm' &&
                            map.map[player.place_x - 1][player.place_y] != 'p') {
                            player.place_x--;
                            items_take(map, player);
                        }
                     }
        case ('s') : if(player.alive >= 1 ) { // Down move
                        if( map.map[player.place_x][player.place_y+1] != 'x' &&
                            map.map[player.place_x][player.place_y+1] != 'm' &&
                            map.map[player.place_x][player.place_y+1] != 'p') {
                            player.place_y++;
                            items_take(map, player);
                        }
                     }
        case ('d') : if(move == 'd' && player.alive >= 1 ) { // Right move
                        if (map.map[player.place_x + 1][player.place_y] != 'x' &&
                            map.map[player.place_x + 1][player.place_y] != 'm' &&
                            map.map[player.place_x + 1][player.place_y] != 'p') {
                            player.place_x++;
                            items_take(map, player);
                        }
                    }
    }
    return player;
    /*if (move == 'z' && player.alive >= 1 ) { // Up mouvement
        if( map.map[player.place_x][player.place_y-1] != 'x' && map.map[player.place_x][player.place_y-1] != 'm' && map.map[player.place_x][player.place_y-1] != 'p') {
            player.place_y--;
            items_take(map, player);
        }
    }else if (move == 'q' && player.alive >= 1) { // Left move
        if( map.map[player.place_x-1][player.place_y] != 'x' && map.map[player.place_x-1][player.place_y] != 'm' && map.map[player.place_x-1][player.place_y] != 'p') {
            player.place_x--;
            items_take(map, player);
        }
    }else if(move == 's' && player.alive >= 1 ) { // Down move
        if( map.map[player.place_x][player.place_y+1] != 'x' && map.map[player.place_x][player.place_y+1] != 'm' && map.map[player.place_x][player.place_y+1] != 'p') {
            player.place_y++;
            items_take(map, player);
        }
    }else if(move == 'd' && player.alive >= 1 ) { // Right move
        if( map.map[player.place_x+1][player.place_y] != 'x' && map.map[player.place_x+1][player.place_y] != 'm' && map.map[player.place_x+1][player.place_y] != 'p') {
            player.place_x++;
            items_take(map, player);
        }
    }*/
}

/*
// Return a Map struct from the file
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

    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++) {
            letter = fgetc(file);
            if(letter != '\n') {
                tab[i][j] = letter;
            }
        }
        fgetc(file);
    }

    map.map = tab;

    fclose(file);

    return map;
}
*/

/*
// Take a Map struct and print it to stdout
void printMap(Map map, Game game, Player player){
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
*/



/*
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
*/

/*// Display all the maps
void printAllMaps(){
    int nbMap = nbMapFile();

    for(int i = 1; i <= nbMap; i++){
        printf("\n === Map number %d ===\n\n", i);
        printMap(map(i));
    }
}*/

int main(){

    Map myMap;
    Game myGame;
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


    printMap(myMap);


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
