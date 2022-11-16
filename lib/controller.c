//
// Created by Clément on 31/10/2022.
//
#include <stdio.h>
#include "colors.h"

#include "controller.h"

// Finir bomb blast, items prit invincibilité, mouvement en focntion des items possédé
// revoir les items heart
// revoir switch items


// fct globale appelée apres chaque input d un joueur, qui renvoie la map avec des modifs (joueur qui bouge, bombe posée ...)
Map modifyMapPlayer(Map map, Player myPlayer){
    map.map[myPlayer.place_x][myPlayer.place_y] = myPlayer.playerID;
    printf("%d", myPlayer.playerID);
    return map;
}

// Add Item for player
Player items_take(Map map, Player *player, Game myGame) {
    // Important revoir la fonction uen fois la structure Items utiliser
    // ajouter &
    char pos = map.map[player->place_x][player->place_y];
    switch (pos){
        case 'b' : player->maxBomb++;
            break;
        case 'd' : player->maxBomb--;
            break;
        case 'c' : player->bomb_range++;
            break;
        case 'e' : player->bomb_range--;
            break;
        case 'r' : // appel fonction pour mettre la valuer de la bombe au max
                // au colonne si il y  a plus de colonne ou de ligne ou autre
            break;
        case 'l' : if (player->heart == 0 ) { // l = heart
                player->heart++;
            }break;
        case 'i' : player->invincible = 1;
                    player->invincible_take = myGame.turn;
            break;
        case 'p' : if (player->bomb_kick == 1) { // Check si possede l'item de pousser les bomb
                player->bomb_kick = 0; // retire l'item bomb kick
            }
            player->pass_bomb = 1;
            break;
        case 'k' : if (player->pass_bomb == 1) { // Check si possede l'item de passer sur les bomb
                player->pass_bomb = 0; // retire l'item de passer sur les bombes
            }
            player->bomb_kick = 1;
            break;
    }
}


// Player moving
Player move_player(Map map, Player *player, char move, Game myGame){
    // IMPORTANT ajouter la vérification des items pour les bombs etc
    switch (move){
        case 'z' : if (player->alive >= 1 ) { // Up mouvement
                        if (map.map[player->place_x][player->place_y - 1] == 'x' ||
                            map.map[player->place_x][player->place_y - 1] == 'm' ||
                            map.map[player->place_x][player->place_y - 1] == 'p') {
                            break;
                        }else {
                            int posX = map.map[player->place_x];
                            int posY = map.map[player->place_y-1];
                            if (map.map[player->place_x][player->place_y- 1] == 'b') {
                                if(check_bombkick(player)){
                                    shot_bomb(player, myGame, posX, posY, move);
                                    break;
                                }else if(check_bombpass(player)){
                                    player->place_x--;
                                    break;
                                }

                            }
                            player->place_y++;
                        }
                    }break;
        case 'q' : if (player->alive >= 1) { // Left move
                        if (map.map[player->place_x - 1][player->place_y] == 'x' ||
                            map.map[player->place_x - 1][player->place_y] == 'm' ||
                            map.map[player->place_x - 1][player->place_y] == 'p') {
                            break;
                        }else {
                            int posX = map.map[player->place_x-1];
                            int posY = map.map[player->place_y];
                            if (map.map[player->place_x- 1][player->place_y] == 'b') {
                                if(check_bombkick(player)){
                                    shot_bomb(player, myGame, posX, posY, move);
                                    break;
                                }else if(check_bombpass(player)){
                                    player->place_x--;
                                    break;
                                }

                            }
                            player->place_x--;
                        }
                    }break;
        case 's' : if(player->alive >= 1 ) { // Down move
                        if( map.map[player->place_x][player->place_y+1] == 'x' ||
                            map.map[player->place_x][player->place_y+1] == 'm' ||
                            map.map[player->place_x][player->place_y+1] == 'p') {
                            break;
                        }else {
                            int posX = map.map[player->place_x];
                            int posY = map.map[player->place_y+1];
                            if (map.map[player->place_x][player->place_y+1] == 'b') {
                                if(check_bombkick(player)){
                                    shot_bomb(player, myGame, posX, posY, move);
                                    break;
                                }else if(check_bombpass(player)){
                                    player->place_y++;
                                    break;
                                }
                                break;
                            }
                            player->place_y++;
                        }
                    }break;
        case 'd' : if(player->alive >= 1 ) { // Right move
                        if (map.map[player->place_x + 1][player->place_y] == 'x' ||
                            map.map[player->place_x + 1][player->place_y] == 'm' ||
                            map.map[player->place_x + 1][player->place_y] == 'p') {
                            break;
                        }else {
                            int posX = map.map[player->place_x + 1];
                            int posY = map.map[player->place_y];
                            if ( map.map[player->place_x + 1][player->place_y] == 'b') {
                                if(check_bombkick(player)){
                                    shot_bomb(player, myGame, posX, posY, move);
                                    break;
                                }else if(check_bombpass(player)){
                                    player->place_x++;
                                    break;
                                }
                                break;
                            }
                            player->place_x++;
                        }
                    }break;
        default : printf("default");
    }
}

Player shot_bomb(Player *myPlayer, Game myGame, int posX, int posY, char direction){
    int bol = 1;
    for (int i = 0; i < sizeof(myGame.playerList); i++) {
        for(int j = 0; j < sizeof(myPlayer->list_bomb) ; j++){
            if (myPlayer->list_bomb[j].place_y == posY && myPlayer->list_bomb[j].place_x == posX){
                switch(direction){
                    case 'z':
                        while (bol){
                            if (myPlayer->list_bomb[j].place_y - 1 == 'x' ||
                                myPlayer->list_bomb[j].place_y - 1 == 'm' ||
                                myPlayer->list_bomb[j].place_y - 1 == 'p' ||
                                myPlayer->list_bomb[j].place_y - 1 == 'b'){
                                bol = 0;
                            }
                            if (bol) {
                                myPlayer->list_bomb[j].place_y--;
                            }
                        }
                        break;
                    case 's':
                        while (bol){
                            if (myPlayer->list_bomb[j].place_y + 1 == 'x' ||
                                myPlayer->list_bomb[j].place_y + 1 == 'm' ||
                                myPlayer->list_bomb[j].place_y + 1 == 'p' ||
                                myPlayer->list_bomb[j].place_y + 1 == 'b'){
                                bol = 0;
                            }
                            if (bol){
                                myPlayer->list_bomb[j].place_y++;
                            }
                        }
                        break;
                    case 'd':
                        while (bol){
                            if (myPlayer->list_bomb[j].place_x + 1 == 'x' ||
                                myPlayer->list_bomb[j].place_x + 1 == 'm' ||
                                myPlayer->list_bomb[j].place_x + 1 == 'p' ||
                                myPlayer->list_bomb[j].place_x + 1 == 'b'){
                                bol = 0;
                            }
                            if (bol){
                                myPlayer->list_bomb[j].place_x++;
                            }
                        }
                        break;
                    case 'q':
                        while (bol){
                            if (myPlayer->list_bomb[j].place_x - 1 == 'x' ||
                                myPlayer->list_bomb[j].place_x - 1 == 'm' ||
                                myPlayer->list_bomb[j].place_x - 1 == 'p' ||
                                myPlayer->list_bomb[j].place_x - 1 == 'b'){
                                bol = 0;
                            }
                            if (bol){
                                myPlayer->list_bomb[j].place_x--;
                            }
                        }
                        break;
                }
            }
        }
    }
}

int check_bombkick(Player *player){
    if (player->bomb_kick == 1){
        return 1;
    }
    return 0;
}

int check_bombpass(Player *player){
    if (player->pass_bomb == 1){
        //passe la bomb
        return 1;
    }
    return 0;
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
    int result = check_bomb(myPlayer, myGame);
    if ( result == NULL ) {
        return ;
    }else {
        int res, res2, res3, res4, propagation, propagation1, propagation2, propagation3 ;
        propagation = 1;
        propagation1 = 1;
        propagation2 = 1;
        propagation3 = 1;
        for (int i = 1; i < myPlayer.bomb_range; i++){
            res = map.map[myPlayer.list_bomb[result].place_x + i][myPlayer.list_bomb[result].place_y];
            if (propagation == 1) {
                switch (res){
                    case 'x': propagation = 0;
                        break;
                    case 'm': propagation = 0 ;
                            /*destroyWall()*/ ;
                        break;
                    case 'p': /*killPlayer()*/
                            propagation = 1;
                        break;
                    case 'b': propagation = 1;
                        break;
                    case 'i': /* détruit l'objet*/  propagation = 1 ;
                        break;
                }
            }
            res2 = map.map[myPlayer.list_bomb[result].place_x - i][myPlayer.list_bomb[result].place_y];
            if (propagation1 == 1) {
                switch (res2) {
                    case 'x':
                        propagation1 = 0;
                        break;
                    case 'm':
                        propagation1 = 0;
                        /*destroyWall()*/;
                        break;
                    case 'p': /*killPlayer();*/ propagation1 = 1;
                        break;
                    case 'i': /* détruit l'objet et continue la propagation*/ ;
                        break;
                }
            }
            res3 = map.map[myPlayer.list_bomb[result].place_x][myPlayer.list_bomb[result].place_y + i];
            if (propagation2 == 1) {
                switch (res3) {
                    case 'x':
                        propagation2 = 0;
                        break;
                    case 'm':
                        propagation2 = 0 /*destroyWall()*/ ;
                        break;
                    case 'p': /*killPlayer();*/
                        propagation2 = 1;
                        break;
                    case 'i': /* détruit l'objet et continue la propagation*/ ;
                        break;
                }
            }
            res4 = map.map[myPlayer.list_bomb[result].place_x][myPlayer.list_bomb[result].place_y - i];
            if (propagation3 == 1) {
                switch (res4) {
                    case 'x':
                        propagation3 = 0;
                        break;
                    case 'm':
                        propagation3 = 0 /*destroyWall()*/ ;
                        break;
                    case 'p': /*killPlayer();*/
                        propagation3 = 1;
                        break;
                    case 'i': /* détruit l'objet et continue la propagation*/ ;
                        break;
                }
            }
        }
    }

}

