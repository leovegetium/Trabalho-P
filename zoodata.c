#include "zoodata.h"

// AREA CHECK FUNCTIONS
int getAreaCapacityUsed(animal * a, char * areaName){
  float sum = 0;

  for(; a != NULL; a = a->next){
    if(strcmp(a->location, areaName) == 0)
      sum += a->weight;
  }

  return sum;
}

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

// ANIMAL FUNCTIONS
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

void birthAnimal(animal * a, area * z, int zSize){
}

void transferAnimal(animal * a, area * z, int zSize){
  char name[20];
}

// AREA FUNCTIONS
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

void deleteArea(animal * a, area ** z, int *size){
  int i, ignore;
  animal * curr = a;
  area * tmp = NULL;

  // PRINT ALL AREAS SO USER CAN SELECT ONE TO DELETE
  do {
    for(i = 0; i < *size; i++){
      printf("%d - %s\n", i + 1, (*z)[i].name);
    }

    printf("\n\nSelect an area: ");
    scanf("%d", &ignore);
    getchar();

    if(ignore < 0 || ignore > *size){
      printf("Select a number from the list. Enter to continue...");
      getchar();
    }
  } while(ignore < 0 || ignore > *size);

  // CHECK AREA IS EMPTY
  while(curr){
    if(strcmp(curr->location, (*z)[ignore - 1].name) == 0){
      printf("Animals in area selected. Not deleting area.\n"
             "Enter to continue\n");
      getchar();
      return;
    }

    curr = curr->next;
  }

  tmp = malloc(sizeof(area) * (*size - 1));
  if(!tmp){
    printf("Memory allocation error. Exiting...");
    exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION E
  }

  ignore -= 1;

  for(i = 0; i < *size; i++){
    if(i < ignore)
      tmp[i] = (*z)[i];
    else if(i == ignore)
      continue;
    else
      tmp[i - 1] = (*z)[i];
  }

  free(*z); // FREE PREVIOUS AREA VECTOR
  *z = tmp; // MAIN AREA PTR POINTS TO NEW AREA VECTOR
  (*size)--;
}
