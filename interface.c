#include  "interface.h"
void findDebug(area * z, int zSize);

static void clear_screen(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void printTxt(char * filename){
  FILE * f = NULL;
  char c;

  f = fopen(filename,"rt");
  if(!f){
    printf("Interface corrupted! Exiting program...");
    exit(1);
  }

  while((c = fgetc(f)) != EOF)
    putchar(c);

  fclose(f);
}

void menu(animal ** a, area ** z, int * zSize){
  int option;

  do {
    clear_screen();
    printTxt("menu.txt");
    scanf("%d", &option);
    getchar();
    //fflush(stdin);

    switch (option) {
      case 1:                      //AREAS
        do{
          clear_screen();
          printTxt("areas.txt");
          scanf("%d", &option);
          getchar();
          //fflush(stdin);
          clear_screen();

          switch (option) {
            case 1:
            break;

            case 2:
            break;

            case 3:
              listAreas(*z, *zSize);
            break;

            case 4:
            break;

            default:
            printf("Option selected invalid! Press Enter to Continue...\n");
            getchar();
          }
        }while(option != 4);
      break;

      case 2:                   //ANIMALS
      do{
        clear_screen();
        printTxt("animals.txt");
        scanf("%d", &option);
        getchar();
        //fflush(stdin);
        clear_screen();

        switch (option) {
          case 1:
            do {
              clear_screen();
              printTxt("animal_info.txt");
              scanf("%d", &option);
              getchar();
              // fflush(stdin);
              clear_screen();

              switch (option) {
                case 1:
                  listAnimal(*a);
                  getchar();
                break;

                case 2:
                break;

                case 3:
                break;

                case 4:
                break;

                case 5: // BACK
                break;

                default:
                printf("Option selected invalid! Press Enter to Continue...\n");
                getchar();
              }
            } while(option !=5);
          break;

          case 2:
          break;

          case 3:
          break;

          case 4:
          break;

          case 5:
            addAnimal(a, *z, *zSize);
          break;

          case 6: // BACK
          break;

          default:
          printf("Option selected invalid! Press Enter to Continue...\n");
          getchar();
        }
      }while(option != 6);
      break;

      case 3:                     //SAVE AND QUIT
      break;

      default:
        printf("Option selected invalid! Press Enter to Continue...\n");
        getchar();
    }
  } while(option != 3);

  //findDebug(*z, *zSize);
}
/*
void findDebug(area * z, int zSize){
  for(int i = 0; i < zSize; i++)
    if(strcmp(z[i].name, "AreaZ") == 0){
      printf("%s", EASTEREGG);
      getchar();
      clear_screen();
      break;
    }
}
*/
