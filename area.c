#include "area.h"

int checkAreaExist(area * z, int zSize, char * areaName){
  for(int i = 0; i < zSize; i++)
    if(strcmp(z[i].name, areaName) == 0)
      return 1;

  return 0;
}

int getAreaCapacity(area * z, int zSize, char * areaName){
  for(int i = 0; i < zSize; i++)
    if(strcmp(z[i].name, areaName) == 0)
      return z[i].capacity;
}

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

void addArea(area ** a, int * size){
  char str[10];
  int i;

  printf("Adding which area? ");
  scanf("%s", str);
  getchar();

  for(i = 0; i < *size; i++)
    if(strcmp((*a)[i].name, str) == 0){
      printf("Area already exists...");
      getchar();
      return;
    }

  * a = realloc(* a, sizeof(area) * ((*size) + 1));
  if(!(*a)){
    printf("Memory allocation error. Exiting...");
    exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
  }

  strcpy((*a)[*size].name, str);

  printf("Capacity: ");
  scanf("%d", &(*a)[*size].capacity);

  do {
    printf("Areas Around: ");
    scanf("%d", &(*a)[*size].areasAround);
    getchar();

    if((*a)[*size].areasAround > 2 || (*a)[*size].areasAround < 0){
      printf("An area can't have more than 2 adjacent areas or less then 0.\nEnter to continue");
      getchar();
    }
  } while((*a)[*size].areasAround > 2 || (*a)[*size].areasAround < 0);


  if((*a)[*size].areasAround > 0){
    (*a)[*size].adjec = malloc(sizeof(char *) * (*a)[*size].areasAround);
    if(!((*a)[*size].adjec)){
      printf("Memory allocation error. Exiting...");
      exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
    }

    for(int i = 0; i < (*a)[*size].areasAround; i++){
      (*a)[*size].adjec[i] = malloc(sizeof(char) * 10);
      if(!(*a)[*size].adjec[i]){
        printf("Memory allocation error. Exiting...");
        exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
      }

      do {
        printf("Area Around %d name: ", i+1);
        scanf("%s", (*a)[*size].adjec[i]);

        if(!checkAreaExist(*a, *size, (*a)[*size].adjec[i])){
          printf("Area doesnt exist. Enter to continue");
          getchar();
        }
        getchar();
      } while(!checkAreaExist(*a, *size, (*a)[*size].adjec[i]));
    }
  }
  else
    (*a)[*size].adjec = NULL;

  (*size)++;
}

void deleteArea(area ** a, int *size){
}
