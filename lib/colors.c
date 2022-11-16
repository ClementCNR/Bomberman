// check https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
// if my own lib isn't enough
//

#include <stdio.h>
#include "colors.h"

void black () {
    printf("\033[1;30");
}

void red() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[1;32m");
}

void yellow() {
    printf("\033[0;33m");
}

void blue() {
    printf("\033[0;34m");
}

void purple() {
    printf("\033[0;35m");
}

void cyan() {
    printf("\033[0;36m");
}

void white() {
    printf("\033[0;37m");
}

void bold() {
    printf("\033[1");
}

void reset() {
    printf("\033[0m");
}
