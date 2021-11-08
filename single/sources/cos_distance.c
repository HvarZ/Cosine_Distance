#include "cos_distance.h"

void CreateBase(base_t* base, size_t numberLines,
                   size_t numberElements) {
  if (base == NULL) {
    return;
  }
  base->data = malloc(numberLines * sizeof(vector_t));
  base->size = numberLines;

  for (size_t i = 0; i < numberLines; ++i) {
    base->data[i].data = malloc(numberElements * sizeof(float));
    base->data[i].size = numberElements;
  }
}

void ClearBase(base_t* base) {
  if (base == NULL || base->data == NULL) {
    return;
  }

  if (base->size > 0) {
    for (size_t i = 0; i < base->size; i++) {
      if (base->data[i].data != NULL) {
        free(base->data[i].data);
      }
    }
    free(base->data);
  }
}

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

void ReadBaseFromFile(base_t* base, char* filename) {
  if (filename == NULL) {
    printf("file not found");
    return;
  }

  FILE* in = fopen(filename, "r");
  size_t numberLines, numberElements;
  fscanf(in, "%lu %lu", &numberLines, &numberElements);

  ClearBase(base);

  CreateBase(base, numberLines, numberElements);

  for (size_t i = 0; i < numberLines; i++) {
    for (size_t j = 0; j < numberElements; j++) {
      fscanf(in, "%f", &base->data[i].data[j]);
    }
  }
  fclose(in);
}
