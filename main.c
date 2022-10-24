#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "colors.h" // Lib to modify the cli output colors

// used to format the console output to print unicode
#include <Windows.h>

typedef struct{
    int defaultBomb;
    int columns;
    int rows;
    char **map;
} Map;

typedef struct{
    int playerID;
    int place_x;
    int place_y;
    int alive;
    int maxBomb;
    int live;
    int invincible;
} Player;



// Return a Map struct from the file
Map map(int mapNumber){
    // FORMATAGE DU NOM DU FICHIER DE MAP
    char mapFilename[20] = "maps/map_";
    char temp[5];
    sprintf(temp,"%d",mapNumber);

    strcat(mapFilename, temp);
    strcat(mapFilename, ".txt");


    // OUVERTURE DU FICHIER ET TEST
    FILE *file = fopen(mapFilename, "r");

    /*if (file == NULL) {
        return NULL;
    }*/

    Map map;

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

    red();

    SetConsoleOutputCP(65001);

    char *breakable = "▒";
    char *unbreakable = "█";

    int nbPlayer = 1;


    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++){

            if(map.map[i][j] == 'p'){
                printf("%d", nbPlayer);
                nbPlayer++;
            }
            else if (map.map[i][j] == 'x'){
                printf("%s", unbreakable);
            }
            else if (map.map[i][j] == 'm'){
                printf("%s", breakable);
            }
            else{
                printf("%c", map.map[i][j]);
            }

        }
        printf("\n");


    }
    reset();
}



// Return the number of map created by checking de maps directory
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
    int nbMap = nbMapFile();

    int selectedMaps[nbMap];
    for(int i=0; i<nbMap; i++){
        selectedMaps[i] = 0;
    }


    int mapNumber = -1;
    while(mapNumber < 1 || mapNumber > nbMap){
        system("cls");
        printAllMaps();
        printf("\n === Select 1 or more maps (between 1 and %d) ===", nbMap);
        printf("\n    === Enter 0 to validate your selection ===\n\n");
        scanf("%d", &mapNumber);
    }

    system("cls");

    myMap = map(mapNumber);


    printMap(myMap);

    scanf("%d", &mapNumber);

    return 0;

    // https://stackoverflow.com/questions/41383062/c-how-to-break-scanf-with-no-enter-and-no-string
}
