#include "base.h"
#include "interface.h"
#include "files.h"
#include "zoodata.h"

int main(int argc, char const *argv[]) {
  animal * animalList = NULL;
  area * zoo = NULL;
  int sizeArea = 0;

  // IMPORT DATA
  zoo = importAreaData(&sizeArea);
  animalList = importAnimalData();

  // MENU
  menu(&animalList, &zoo, &sizeArea);

  // EXPORT DATA TO FILES
  exportAnimalData(animalList);
  exportAreaData(zoo, sizeArea);

  return 0;
}
