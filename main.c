#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    int columns;
    int rows;
    char **map;
} Map;



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




void printMap(Map map){

    for(int i = 0; i < map.rows; i++){
        for(int j = 0; j < map.columns; j++){

            printf("%c", map.map[i][j]);
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

    return 0;
}
