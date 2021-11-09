#include "neutral_functions.h"

void CreateBase(base_t *base, size_t numberLines, size_t numberElements) {
  if (base == NULL) {
    return;
  }
  base->data = (vector_t *)malloc(numberLines * sizeof(vector_t));
  if (base->data == NULL) {
    return;
  }
  base->size = numberLines;

  for (size_t i = 0; i < numberLines; ++i) {
    base->data[i].data = (float *)malloc(numberElements * sizeof(float));
    if (base->data[i].data == NULL) {
      return;
    }
    base->data[i].size = numberElements;
  }
}

void ClearBase(base_t *base) {
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
  base->size = 0;
}


void ClearVector(vector_t *vector) {
  if (vector == NULL) {
    return;
  }
  if (vector->size == 0) {
    return;
  }
  free(vector->data);
  vector->size = 0;
}

float Dot(vector_t *vector1, vector_t *vector2) {
  if (vector1 == NULL || vector2 == NULL) {
    return -FLT_MAX;
  }
  if (vector1->size != vector2->size) {
    return -FLT_MAX;
  }
  if (vector1->size == 0 || vector2->size == 0) {
    return -FLT_MAX;
  }
  float result = 0;

  for (size_t i = 0; i < vector1->size; ++i) {
    result += (vector1->data[i] * vector2->data[i]);
  }

  return result;
}

float Length(vector_t *vector) {
  if (vector == NULL) {
    return -FLT_MAX;
  }
  float result = 0;

  for (size_t i = 0; i < vector->size; ++i) {
    result += powf(vector->data[i], 2);
  }

  return sqrtf(result);
}

float CosDistance(vector_t *vector1, vector_t *vector2) {
  if (vector1 == NULL || vector2 == NULL) {
    return -FLT_MAX;
  }
  if (vector1->size != vector2->size) {
    return -FLT_MAX;
  }
  if (vector1->size == 0 || vector2->size == 0) {
    return -FLT_MAX;
  }
  return acosf(Dot(vector1, vector2) / (Length(vector1) * Length(vector2)));
}

void ReadBaseFromFile(base_t *base, char *filename) {
  if (filename == NULL) {
    printf("file not found");
    return;
  }

  FILE *in = fopen(filename, "r");
  size_t numberLines, numberElements;
  fscanf(in, "%zu %zu", &numberLines, &numberElements);

  ClearBase(base);

  CreateBase(base, numberLines, numberElements);

  for (size_t i = 0; i < numberLines; i++) {
    for (size_t j = 0; j < numberElements; j++) {
      fscanf(in, "%f", &base->data[i].data[j]);
    }
  }
  fclose(in);
}
