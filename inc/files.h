#ifndef FILES_H
#define FILES_H
#include "base.h"
#include "area.h"
#include "animal.h"

animal * importAnimalData();
area * importAreaData(int * vecArea);

void exportAnimalData(animal * a);
void exportAreaData(area * z, int size);

#endif
