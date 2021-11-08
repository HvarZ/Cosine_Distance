#include "cos_distance.h"

float Dot(vector_t* vector1, vector_t* vector2) {
  if (vector1->data == NULL || vector2->data == NULL) {
    return -FLT_MAX;
  }
  if (vector1->size != vector2->size) {
    return -FLT_MAX;
  }
  float result = 0;

  for(size_t i = 0; i < vector1->size; ++i) {
    result += (vector1->data[i] * vector2->data[i]);
  }

  return result;
}

float Length(vector_t* vector) {
  if (vector->data == NULL) {
    return -FLT_MAX;
  }
  float result = 0;

  for(size_t i = 0; i < vector->size; ++i) {
    result += powf(vector->data[i], 2);
  }

  return sqrtf(result);
}

float CosDistance(vector_t* vector1, vector_t* vector2) {
  return Dot(vector1, vector2) / (Length(vector1) * Length(vector2));
}
