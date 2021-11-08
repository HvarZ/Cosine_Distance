#ifndef UNDIVIDUAL_TASK_2_NEUTRAL_FUNCTIONS_H
#define UNDIVIDUAL_TASK_2_NEUTRAL_FUNCTIONS_H

#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

typedef struct vector {
  float* data;
  size_t size;
} vector_t;

typedef struct vectors {
  vector_t* data;
  size_t size;
} base_t;

void CreateBase(base_t* base, size_t numberLines,
                size_t numberElements);
void ClearBase(base_t* base);
void FillVector(vector_t* vector);

float Dot(vector_t* vector1, vector_t* vector2);
float Length(vector_t* vector);
float CosDistance(vector_t* vector1, vector_t* vector2);

void ReadBaseFromFile(base_t* base, char* filename);

#endif // UNDIVIDUAL_TASK_2_NEUTRAL_FUNCTIONS_H
