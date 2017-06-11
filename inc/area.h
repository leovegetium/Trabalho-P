#ifndef AREA_H
#define AREA_H
#include "base.h"

typedef struct area area;
struct area{
  char name[10];
  int capacity;
  int areasAround;
  char ** adjec; // STRINGS SIZE ARE ALWAYS 10
};

void listAreas(area * a, int size);
void addArea(area ** a, int *size);
void deleteArea(area ** a, int *size);

int checkAreaExist(area * z, int zSize, char * areaName);
int getAreaCapacity(area * z, int zSize, char * areaName);

#endif
