#ifndef ZOODATA_H
#define ZOODATA_H
#include "base.h"

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

typedef struct area area;
struct area{
  char name[10];
  int capacity;
  int areasAround;
  char ** adjec; // STRINGS SIZE ARE ALWAYS 10
};


// ANIMAL FUNCTIONS
void addAnimal(animal ** a, area * z, int zSize);
void deleteAnimal(animal ** a); // TODO CHECK THIS SHIT
void listAnimal(animal * a);
void birthAnimal(animal * a, area * z, int zSize);
void transferAnimal(animal * a, area * z, int zSize);

// AREA FUNCTIONS
void listAreas(area * a, int size);
void addArea(area ** a, int *size);
void deleteArea(animal * a, area ** z, int *size);

#endif
