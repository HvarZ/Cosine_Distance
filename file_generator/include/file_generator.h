#ifndef INDIVIDUAL_TASK_2_FILE_GENERATOR_H
#define INDIVIDUAL_TASK_2_FILE_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH_SEGMENT 2000
#define HALF_LENGTH_SEGMENT 1000

void RandomFillVectorFile(FILE *out, size_t numberElements);
void RandomFillBaseFile(char *filename, size_t numberLines,
                        size_t numberElements);

#endif  // INDIVIDUAL_TASK_2_FILE_GENERATOR_H
