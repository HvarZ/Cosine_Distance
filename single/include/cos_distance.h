#ifndef INDIVIDUAL_TASK_2_COS_DISTANCE_H
#define INDIVIDUAL_TASK_2_COS_DISTANCE_H

#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct vector {
  float* data;
  size_t size;
} vector_t;

float Dot(vector_t* vector1, vector_t* vector2);
float Length(vector_t* vector);
float CosDistance(vector_t* vector1, vector_t* vector2);

#endif // INDIVIDUAL_TASK_2_COS_DISTANCE_H
