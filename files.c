#include "files.h"

#define ANIMALFILE "animal.dat"
#define AREAFILE "manage_areas.txt"

animal * importAnimalData(){
  FILE   * f = NULL;
  animal * head = NULL;
  animal * curr = NULL;
  char str[20];
  int i, parentsSize = 0;

  //OPENS THE FILE
  f = fopen(ANIMALFILE,"rb");
  // CHECKS IF FILE IS OPEN CORRECTLY IF NOT RETURNS NULL
  if(!f){
    printf("File %s not found. Press Enter to continue... ", ANIMALFILE);
    getchar();
    return NULL;
  }

  // READS NAME OF ANIMAL UNTIL THE END OF THE FILE
  while(fread(str, sizeof(char), 20, f)){ // READ JUST THE NAME OF ANIMAL
    if(head){ // IF HEAD PTR IS NULL, MALLOC NULL
      curr->next = malloc(sizeof(animal));
      curr = curr->next;
      curr->next = NULL;
    }
    else{
      head = malloc(sizeof(animal));
      head->next = NULL;
      curr = head; // CURR PTR IS THE MANIPULATION PTR
    }

    strcpy(curr->name, str);
    fread(curr->specie, sizeof(char), 20, f);
    fread(curr->id, sizeof(char), 10, f);
    fread(&curr->weight, sizeof(float), 1, f);
    fread(curr->location, sizeof(char), 10, f);
    fread(&parentsSize, sizeof(int), 1, f);
    curr->parentsSize = parentsSize;

    if(parentsSize > 0){
      curr->parents = malloc(sizeof(char *) * parentsSize);
      if(!curr->parents){
        printf("Memory allocation error. Exiting...");
        exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
      }

      for(i = 0; i < parentsSize; i++){
        curr->parents[i] = malloc(sizeof(char) * 20);
        if(!curr->parents[i]){
          printf("Memory allocation error. Exiting...");
          exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
        }

        fread(curr->parents[i], sizeof(char), 20, f);
      }
    }
    else
      curr->parents = NULL;

    //parentsSize = 0;
    fread(&parentsSize, sizeof(int), 1, f);
    curr->descSize = parentsSize;

    if(parentsSize > 0){
      curr->descendents = malloc(sizeof(char *) * parentsSize);
      if(!curr->descendents){
        printf("Memory allocation error. Exiting...");
        exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
      }

      for(i = 0; i < parentsSize; i++){
        curr->descendents = malloc(sizeof(char) * 20);
        if(!curr->descendents[i]){
          printf("Memory allocation error. Exiting...");
          exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
        }

        fread(curr->descendents[i], sizeof(char), 20, f);
      }
    }
  }

  return head;
}

area * importAreaData(int * vecArea){
  FILE * f = NULL;
  area * head = NULL;
  int i, cap = 0, areaSize = 0;
  char str[10];

  f = fopen(AREAFILE,"rt");
  if(!f){ // CHECK IF FILE IS OPEN CORRECTLY
    printf("File %s not found. Exiting...", AREAFILE);
    exit(3); // EXIT CODE 3 -> AREA DATA FILE NOT FOUND OR CORRUPTED
  }

  while(fscanf(f, "%s %d %d", str, &cap, &areaSize) == 3){
    head = realloc(head, sizeof(area) * ++(*vecArea));
    if(!head){
      printf("Memory allocation error. Exiting...");
      exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
    }

    strcpy(head[(*vecArea) - 1].name, str);
    head[(*vecArea) - 1].capacity = cap;
    head[(*vecArea) - 1].areasAround = areaSize;

    head[(*vecArea) - 1].adjec = malloc(sizeof(char *) * areaSize);
    if(!head[(*vecArea) - 1].adjec){
      printf("Memory allocation error. Exiting...");
      exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
    }

    for(i = 0; i < areaSize; i++){
      head[(*vecArea) - 1].adjec[i] = malloc(sizeof(char) * 10);
      if(!head[(*vecArea) - 1].adjec[i]){
        printf("Memory allocation error. Exiting...");
        exit(2); // EXIT CODE 2 IS MEMORY ALLOCATION ERROR
      }

      fscanf(f, "%s", head[(*vecArea) - 1].adjec[i]);
    }
    fscanf(f,"\n");
  }

  fclose(f);

  return head;
}

void exportAnimalData(animal * a){
  FILE   * f = NULL;

  int i;

  //OPENS THE FILE
  f = fopen(ANIMALFILE, "wb");
  if(!f){ //CHECKS IF FILE IS OPEN CORRCTLY IF NOT RETURNS NULL
    printf("File %s not found. Press Enter to continue... ", ANIMALFILE);
    getchar();
    return;
  }

  while(a){
    fwrite(a->name, sizeof(char), 20, f);
    fwrite(a->specie, sizeof(char), 20, f);
    fwrite(a->id, sizeof(char), 10, f);
    fwrite(&a->weight, sizeof(float), 1, f);
    fwrite(a->location, sizeof(char), 10, f);

    fwrite(&a->parentsSize, sizeof(int), 1, f);
    for(i = 0; i < a->parentsSize; i++){
      fwrite(a->parents[i], sizeof(char), 20, f);
    }

    fwrite(&a->descSize, sizeof(int), 1, f);
    for(i=0; i < a->descSize; i++){
      fwrite(a->descendents[i], sizeof(char), 20, f);
    }

    a = a->next;
  }

  fclose(f);
}

void exportAreaData(area * z, int size){
  FILE * f = NULL;
  int i, j;

  //OPENS FILE
  f = fopen(AREAFILE,"wt");
  if(!f){
    printf("File %s not found. Exiting... ", AREAFILE);
    exit(3); // EXIT CODE 3 -> AREADATA FILE NOT FOUND
  }

  for(i = 0; i < size ; i++){
    fprintf(f, "%s %d %d ", z[i].name, z[i].capacity, z[i].areasAround);
    for(j = 0; j < z[i].areasAround; j++){
      fprintf(f, "%s ", z[i].adjec[j]);
    }
    fprintf(f,"\n");
  }
  fclose(f);
}
