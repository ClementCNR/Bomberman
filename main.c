#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>

typedef struct{
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

    // LECTURE DE LA 2EME LIGNE QUI CONTIENT LA TAILLE ET LA HAUTEUR
    char line[1024];
    fgets(line, 1024, file);
    fgets(line, 1024, file);


    //map.columns = atoi(&line[0]);
    //map.rows = atoi(&line[2]);

    map.columns = 9;
    map.rows = 5;

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

    SetConsoleOutputCP(65001);

    char  *breakable = "▒";
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

int main(){
    Map myMap;
    myMap = map(1);

    printf("\n\n");
    printMap(myMap);


    //printf("\n-\xE2-\x96-\x92-");

    //printf("%c%c%c", '\xE2', '\x96', '\x92');


    return 0;
}
