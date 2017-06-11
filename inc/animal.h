#ifndef ANIMAL_H
#define ANIMAL_H
#include "base.h"
#include "area.h"

typedef struct animal animal;
struct animal{
  char name[20];
  char specie[20];
  char id[10];
  float weight;
  char location[10];
  int parentsSize;
  char ** parents; // SIZE 20
  int descSize;
  char ** descendents; // SIZE 20

  animal * next;
};

void listAnimal(animal * a);
void addAnimal(animal ** a, area * z, int zSize);
#endif
