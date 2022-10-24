//
// Created by Clément on 24/10/2022.
//

#include <stdio.h>
#include "colors.h"

void red() {
    printf("\033[1;31m");
}

void bold() {
    printf("\033[1");
}

void reset() {
    printf("\033[0m");
}