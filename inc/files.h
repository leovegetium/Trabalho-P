#ifndef FILES_H
#define FILES_H
#include "base.h"
#include "zoodata.h"

animal * importAnimalData();
area * importAreaData(int * vecArea);

void exportAnimalData(animal * a);
void exportAreaData(area * z, int size);

#endif
