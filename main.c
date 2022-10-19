#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// used to format the console output to print unicode
#include <Windows.h>

typedef struct{
    int defaultBomb;
    int columns;
    int rows;
    char **map;
} Map;

typedef struct{
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

    system("cls");

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

int main(){

    Map myMap;
    int nbMap = nbMapFile();


    int mapNumber = 0;
    printf("\n === Select a map (between 1 and %d) ===\n\n", nbMap);
    scanf("%d", &mapNumber);
    myMap = map(mapNumber);


    printMap(myMap);

    scanf("%d", &mapNumber);

    return 0;

    // https://stackoverflow.com/questions/41383062/c-how-to-break-scanf-with-no-enter-and-no-string
}
