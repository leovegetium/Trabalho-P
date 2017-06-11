#include "animal.h"

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

int getAreaCapacityUsed(animal * a, char * areaName){
  float sum = 0;

  for(; a != NULL; a = a->next){
    if(strcmp(a->location, areaName) == 0)
      sum += a->weight;
  }

  return sum;
}

void showAnimalInfo(animal * a){
  printf("Name: %s\n"
         "Specie: %s\n"
         "Id: %s\n"
         "Weight: %.2f\n"
         "Location: %s\n",
         a->name, a->specie, a->id, a->weight, a->location);

  if(a->parentsSize > 0){
    printf("Parents: ");

    for(int i = 0; i < a->parentsSize; i++)
      printf("%s ", a->parents[i]);

    printf("\n");
  }

  if(a->descSize > 0){
    printf("Descendents: ");

    for(int i = 0; i < a->descSize; i++)
      printf("%s ", a->descendents[i]);

    printf("\n");
    getchar();

  }
}

int askAnimalInfo(animal * a, animal * head, area * z, int zSize) {
  printf("Name of Animal: ");
  scanf("%s", a->name);
  getchar();

  printf("Name of Specie: ");
  scanf("%[^\n]", a->specie);
  getchar();

  printf("Animal ID: ");
  scanf("%s", a->id);
  getchar();

  printf("Animal weight: ");
  scanf("%f", &a->weight);
  getchar();

  printf("Animal location: ");
  scanf("%s", a->location);
  getchar();

  if(!checkAreaExist(z, zSize, a->location)){
    printf("Area doesn't exist.\n");
    return 1;
  }

  // CHECK IF AREA HAS WEIGHT CAPACITY
  if(a->weight + getAreaCapacityUsed(head, a->location) > getAreaCapacity(z, zSize, a->location)){
    printf("Weight over capacity!\n");
    return 1;
  }

  printf("Animal number of parents: ");
  scanf("%d", &a->parentsSize);
  getchar();

  if(a->parentsSize > 0){
    a->parents = malloc(sizeof(char *) * a->parentsSize);
    if(!a->parents){
      printf("Memory allocation error. Exiting...");
      exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
    }

    for(int i = 0; i < a->parentsSize; i++){
      a->parents[i] = malloc(sizeof(char) * 20);
      if(!a->parents[i]){
        printf("Memory allocation error. Exiting...");
        exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
      }

      printf("Animal parent's name n%d: ", i + 1);
      scanf("%s", a->parents[i]);
      getchar();
    }
  }
  else
    a->parents = NULL;

  printf("Animal number of descendents: ");
  scanf("%d", &a->descSize);
  getchar();

  if(a->descSize > 0){
    a->descendents = malloc(sizeof(char *) * a->descSize);
    if(!a->descendents){
      printf("Memory allocation error. Exiting...");
      exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
    }

    for(int i = 0; i < a->descSize; i++){
      a->descendents[i] = malloc(sizeof(char) * 20);
      if(!a->descendents[i]){
        printf("Memory allocation error. Exiting...");
        exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
      }

      printf("Animal descendent's name n%d: ", i + 1);
      scanf("%s", a->descendents[i]);
      getchar();
    }
  }
  else
    a->descendents = NULL;

  return 0;
}

void deleteAnimal(animal ** a){
  char animalName[50];
  animal * curr = NULL;
  animal * beforeCurr = NULL;

  if(*a){
    curr = * a;

    //ASK USER THE NAME OF ANIMAL
    printf("Name of Animal: ");
    scanf("%s", animalName);

    //SEARCH ANIMAL
    while (curr) {
      if (strcmp(curr->name, animalName) == 0) {
        if(curr == *a){
          *a = curr->next;
          free(curr);
          break;
        }
        else{
          beforeCurr->next = curr->next;
          free(curr);
          break;
        }
        beforeCurr = curr;
        curr = curr->next;
      }
    }
  }
  else{
    printf("There is no animal in the ZOO!\nPress Enter to continue... ");
    getchar();
  }
}

void addAnimal(animal ** a, area * z, int zSize){
  animal * node = NULL;

  node = malloc(sizeof(animal));
  if(!node){
    printf("Error! Couldn't allocate memory for animal\n");
    return;
  }
  node->next = NULL;

  if(askAnimalInfo(node, *a, z, zSize)){
    free(node);
    printf("Animal wasn't added. Enter to continue");
    getchar();
    return;
  }

  if(a){
    while(*a)
      a = &(*a)->next;

    *a = node;
  }
  else
    * a = node;

  printf("Animal added. Enter to continue");
  getchar();
}
//TO DO
void birthAnimal(){
}
//TO DO
void transferAnimal(){
}

void listAnimal(animal * a){
  if(a){
    for(; a != NULL; a = a->next){
      showAnimalInfo(a);
      getchar();
    }
  }
  else{
    printf("There is no animal in the ZOO!\nPress Enter to continue... ");
    getchar();
  }
}
