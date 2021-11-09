#include "neutral_functions.h"

const vector_t* MinVectorCosDistance(base_t* base, vector_t* vector) {
  if (base == NULL || vector == NULL) {
    return NULL;
  }
  if (base->size == 0) {
    return NULL;
  }
  if (base->data[0].size != vector->size) {
    return NULL;
  }

  float min = 180;
  const vector_t* result = &base->data[base->size - 1];

  for (size_t i = 0; i < base->size; ++i) {
    float distance = CosDistance(vector, &base->data[i]);
    if (distance < min) {
      min = distance;
      result = &base->data[i];
    }
  }
  return result;
}
