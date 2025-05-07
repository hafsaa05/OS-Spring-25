// functions.c
#include <stdio.h>
#include "functions.h"

void greet(Person p) {
    printf("Hello, %s!\n", p.name);
    printMessage(p);
}
