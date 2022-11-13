//
// Created by Clément on 31/10/2022.
//
#include <stdio.h>
#include "colors.h"

#include "controller.h"

// fct globale appelée apres chaque input d un joueur, qui renvoie la map avec des modifs (joueur qui bouge, bombe posée ...)
Map modifyMapPlayer(Map map, Player myPlayer){
    map.map[myPlayer.place_x][myPlayer.place_y] = myPlayer.playerID;
    printf("%d", myPlayer.playerID);
    return map;
}

// fonction destruction d'un mur
Map modifyMapWall(Map map, Game myGame, char keyPressed, Player myPlayer);/*{
    if (map.map[bomb.touch_x][bomb.touch_y] == 'm' ) {
        map.map[bomb.touch_x][bomb.touch_x] == ' ';
    }
}*/

// Blast bomb kill
Map modifyPlayerDie(Map myMap, Game myGame, Player myPlayer);/*{
    if (myMap.map[bomb.touch_x][bomb.touch_y] ==  myPlayer.playerID) {
        myPlayer.heart--;
    }
}*/

// Add Item for player
Player items_take(Map map, Player *player) {
    // Important revoir la fonction uen fois la structure Items utiliser
    // ajouter &
    switch (map.map[player->place_x][player->place_y]){
        case ('b') : player->maxBomb++;
        case ('d') : player->maxBomb--;
        case ('c') : player->bomb_range++;
        case ('e') : player->bomb_range--;
        case ('r') : // appel fonction pour mettre la valuer de la bombe au max
            // au colonne si il y  a plus de colonne ou de ligne ou autre
        case ('l') : if (player->heart == 0 ) { // l = heart
                player->heart++;
            }
        case ('i') : // Wait turn playing
        case ('p') : if (player->bomb_kick == 1) { // Check si possede l'item de pousser les bomb
                player->bomb_kick = 0; // retire l'item bomb kick
            }
            player->pass_bomb = 1;
        case ('k') : if (player->pass_bomb == 1) { // Check si possede l'item de passer sur les bomb
                player->pass_bomb = 0; // retire l'item de passer sur les bombes
            }
            player->bomb_kick = 1;
    }
}


// Player moving
Player move_player(Map map, Player *player, char move){
    // IMPORTANT ajouter la vérification des items pour les bombs etc
    switch (move){
        case 'z' : if (player->alive >= 1 ) { // Up mouvement
                        if (map.map[player->place_x][player->place_y - 1] != 'x' &&
                            map.map[player->place_x][player->place_y - 1] != 'm' &&
                            map.map[player->place_x][player->place_y - 1] != 'p') {
                            player->place_y--;
                            //items_take(map, player);
                            //modifyMapPlayer(map, player);
                        }
                    }break;
        case 'q' : if (player->alive >= 1) { // Left move
                        if (map.map[player->place_x - 1][player->place_y] != 'x' &&
                            map.map[player->place_x - 1][player->place_y] != 'm' &&
                            map.map[player->place_x - 1][player->place_y] != 'p') {
                            player->place_x--;
                            //items_take(map, player);
                            //modifyMapPlayer(map, player);
                        }
                    }break;
        case 's' : if(player->alive >= 1 ) { // Down move
                        if( map.map[player->place_x][player->place_y+1] != 'x' &&
                            map.map[player->place_x][player->place_y+1] != 'm' &&
                            map.map[player->place_x][player->place_y+1] != 'p') {
                            player->place_y++;
                            //items_take(map, player);
                            //modifyMapPlayer(map, player);
                        }
                    }break;
        case 'd' : if(player->alive >= 1 ) { // Right move
                        if (map.map[player->place_x + 1][player->place_y] != 'x' &&
                            map.map[player->place_x + 1][player->place_y] != 'm' &&
                            map.map[player->place_x + 1][player->place_y] != 'p') {
                            player->place_x++;
                            //items_take(map, player);
                            //modifyMapPlayer(map, player);
                        }
                    }break;
        default : printf("tg");
    }
}

int check_bomb(Player myPlayer, Game myGame){
    int rep = NULL;
    for (int i = 0; i < sizeof(myPlayer.list_bomb) ; i++){
        if(myPlayer.list_bomb[i].turnPut + 2 == myGame.turn){
            rep = i;
        }
    }
    return rep;
}

Player put_bomb(Player *myPlayer, Game myGame, Bomb aBomb){
    // gerer le max bomb
    int add = 0;
    int i = 0;
    while ( add == 0 && i < sizeof(myPlayer->list_bomb) ) {
        if (NULL == myPlayer->list_bomb[i].idBomb){
            add = 1;
            // Création d'une bomb
            aBomb.idBomb = i;
            aBomb.turnPut = myGame.turn;
            aBomb.place_y = myPlayer->place_y;
            aBomb.place_x = myPlayer->place_x;
            // Ajout de la bombe crée dans la liste de bombe du joueur
            myPlayer->list_bomb[i] = aBomb;
        }
        i++;
    }
}

void bomb_blast(Map map, Player myPlayer, Game myGame){
    int result = check_bomb( myPlayer, myGame);
    if ( result == NULL ) {
        return ;
    }else {
        int res, res2, res3, res4, propagation ;
        propagation = 1;
        for (int i = 1; i < myPlayer.bomb_range; i++){
            res = map.map[myPlayer.list_bomb[result].place_x + i][myPlayer.list_bomb[result].place_y];
            if (propagation == 1) {
                switch (res){
                    case 'x': propagation = 0;
                    case 'm': /* casse le mur et bloque le propagation*/ ;
                    case 'p': /* Tu le joueur et continue la propagation*/ ;
                    case 'i': /* détruit l'objet et continue lma propagation*/ ;
                }
            }
            res2 = map.map[myPlayer.list_bomb[result].place_x - i][myPlayer.list_bomb[result].place_y];
            switch (res2){
                case 'x': /* bloque la propagation et rien ne se passe*/ ;
                case 'm': /* casse le mur et bloque le propagation*/ ;
                case 'p': /* Tu le joueur et continue la propagation*/ ;
                case 'i': /* détruit l'objet et continue lma propagation*/ ;
            }
            res3 = map.map[myPlayer.list_bomb[result].place_x][myPlayer.list_bomb[result].place_y + i];
            switch (res3){
                case 'x': /* bloque la propagation et rien ne se passe*/ ;
                case 'm': /* casse le mur et bloque le propagation*/ ;
                case 'p': /* Tu le joueur et continue la propagation*/ ;
                case 'i': /* détruit l'objet et continue lma propagation*/ ;
            }
            res4 = map.map[myPlayer.list_bomb[result].place_x][myPlayer.list_bomb[result].place_y - i];
            switch (res4){
                case 'x': /* bloque la propagation et rien ne se passe*/ ;
                case 'm': /* casse le mur et bloque le propagation*/ ;
                case 'p': /* Tu le joueur et continue la propagation*/ ;
                case 'i': /* détruit l'objet et continue lma propagation*/ ;
            }

        }
    }

}

