#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct{
    int columns;
    int rows;
    char **map;
} Map;

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



Player items_take (Map map, int columns,int line,int item_place, Player player) {

    int player_y = player.place_y;
    int player_x = player.place_x;
    if (map.map[player_x][player_y] != 'p' && map[player_x][player_y] != ' ' && map[player_x][player_y] != 'bomb') {
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
