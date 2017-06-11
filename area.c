#include "area.h"

void listAreas(area * a, int size){
  int i, j;

  for(i = 0; i < size; i++){
    printf("Area: %s\nCapacity: %d\n Areas Around: %d -> ", a[i].name, a[i].capacity, a[i].areasAround);
    for(j = 0; j < a[i].areasAround; j++)
      printf("%s ", a[i].adjec[j]);

    getchar();
    printf("\n");
  }
}

void addArea(area * a, int size){
}

void deleteArea(area * a, int size){
}
