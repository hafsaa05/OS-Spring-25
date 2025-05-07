// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Struct declaration
typedef struct {
    char name[50];
    int age;
} Person;

// Function declarations
void greet(Person p);
void printMessage(Person p);

#endif
