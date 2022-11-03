//
// Created by Clément on 28/10/2022.
//
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

#endif //PROJET_MODEL_H
