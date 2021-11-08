#ifndef INDIVIDUAL_TASK_2_FILE_GENERATOR_H
#define INDIVIDUAL_TASK_2_FILE_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillVectorFile(FILE* out, size_t numberElements);
void FillVectorsFile(char* filename, size_t numberLines, size_t numberElements);

void RandomFillVectorFile(FILE* out, size_t numberElements);
void RandomFillVectorsFile(char* filename, size_t numberLines,
                           size_t numberElements);

#endif // INDIVIDUAL_TASK_2_FILE_GENERATOR_H
