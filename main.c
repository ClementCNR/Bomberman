#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h> // used for rand
#include "colors.h" // Lib to modify the cli output colors

// used to format the console output to print unicode
#include <Windows.h>

#define CMD_WIDE 120



typedef struct{
    int defaultBomb;
    int columns;
    int rows;
    char **map;
}  Map;

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

typedef struct{
    int playerID;
    int place_x;
    int place_y;
    int alive;
    int maxBomb;
    int live;
    int invincible;
    int heart;
    int pass_bomb;
    int bomb_kick;
    int yellow_fire;
    int red_fire;
    int blue_fire;
    int bomb_range;
    // Items *list_items;
} Player;



int arraySum(int *tab, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += tab[i];
    }
    return sum;
}

Player items_take (Map map, int columns,int line,int item_place, Player player) {

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


// Déplacement d'un joueur
int move_player(Map map, Player player, char move){
    if (move == 'b') {
        if( map.map[player.place_x][player.place_y+1] != 'x' && map.map[player.place_x][player.place_y+1] != 'm')
            player.place_y++;
    }
}


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



// Display all the maps
void printAllMaps(){
    int nbMap = nbMapFile();

    for(int i = 1; i <= nbMap; i++){
        printf("\n === Map number %d ===\n\n", i);
        printMap(map(i));
    }
}




int main(){

    Map myMap;
    int nbMapInDir = nbMapFile();
    int lastPlayedMap = 0;


    int selection[nbMapInDir];
    for(int i=0; i<nbMapInDir; i++){
        selection[i] = 0;
    }


    int mapNumber = -1;
    while(mapNumber != 0 /*&& arraySum(selection, nbMapInDir) == 0*/){

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


    return 0;

    // https://stackoverflow.com/questions/41383062/c-how-to-break-scanf-with-no-enter-and-no-string
}
