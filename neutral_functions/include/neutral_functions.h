#ifndef INDIVIDUAL_TASK_2_NEUTRAL_FUNCTIONS_H
#define INDIVIDUAL_TASK_2_NEUTRAL_FUNCTIONS_H

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ACOS 3.14f
#define LENGTH_SEGMENT 2000
#define HALF_LENGTH_SEGMENT 1000

typedef struct vector {
  float *data;
  size_t size;
} vector_t;

typedef struct vectors {
  vector_t *data;
  size_t size;
} base_t;

void CreateBase(base_t *base, size_t numberLines, size_t numberElements);
void ClearBase(base_t *base);

void ClearVector(vector_t *vector);
void FillVector(vector_t *vector);
void RandomFillVector(vector_t *vector, size_t size);

float Dot(vector_t *vector1, vector_t *vector2);
float Length(vector_t *vector);
float CosDistance(vector_t *vector1, vector_t *vector2);

void ReadBaseFromFile(base_t *base, char *filename);
const vector_t *MinVectorCosDistance(base_t *base, vector_t *vector);

void OutputVector(char *filename, vector_t *vector);

#endif  // INDIVIDUAL_TASK_2_NEUTRAL_FUNCTIONS_H
