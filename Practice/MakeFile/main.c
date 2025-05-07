// main.c
#include <stdio.h>
#include <string.h>
#include "functions.h"

int main() {
    Person p;
    strcpy(p.name, "Hafsa");
    p.age = 21;

    greet(p);
    return 0;
}
