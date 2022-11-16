#include "structs.h"
#ifndef PROJET_MODEL_H
#define PROJET_MODEL_H

Map map(int mapNumber);

Map modifyMap(Map mapToModify);

int nbMapFile();

Node *ll_push_front(Node *first, Player newPlayer);

void ll_free(Node *first);

void ll_print(Node *first);

Node *initPlayerList(Node *first, Map map);

//
//called during explosion
//will change the 'm' by ' '
//will call spawnItem to randomise the ' ' by an item
void destroyWall(Map *map, int x, int y);

#endif //PROJET_MODEL_H
