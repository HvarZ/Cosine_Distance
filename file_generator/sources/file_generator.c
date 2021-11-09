#include "file_generator.h"

void FillVectorFile(FILE* out, size_t numberElements) {
  if (out == NULL) {
    return;
  }
  if (numberElements == 0) {
    printf("elements is 0");
    return;
  }

  float buffer;
  for (size_t i = 0; i < numberElements; ++i) {
    scanf("%f", &buffer);
    fprintf(out, "%f ", buffer);
  }
  fprintf(out, "\n");
}

void FillBaseFile(char* filename, size_t numberLines, size_t numberElements) {
  if (filename == NULL) {
    printf("file not found");
    return;
  }
  if (numberLines == 0) {
    printf("elements is 0");
    return;
  }

  FILE* out = fopen(filename, "w");
  fprintf(out, "%zu", numberLines);
  fprintf(out, "%zu\n", numberElements);
  for (size_t i = 0; i < numberLines; ++i) {
    FillVectorFile(out, numberElements);
  }
  fclose(out);
}

void RandomFillVectorFile(FILE* out, size_t numberElements) {
  if (out == NULL) {
    return;
  }
  if (numberElements == 0) {
    printf("elements is 0");
    return;
  }

  for (size_t i = 0; i < numberElements; ++i) {
    fprintf(out, "%f ", (float)(rand() % LENGTH_SEGMENT) - HALF_LENGTH_SEGMENT);
  }
  fprintf(out, "\n");
}

void RandomFillBaseFile(char* filename, size_t numberLines,
                        size_t numberElements) {
  if (filename == NULL) {
    printf("file not found");
    return;
  }
  if (numberLines == 0) {
    printf("elements is 0");
    return;
  }
  FILE* out = fopen(filename, "w");
  fprintf(out, "%zu ", numberLines);
  fprintf(out, "%zu\n", numberElements);
  for (size_t i = 0; i < numberLines; ++i) {
    srand(time(NULL) + i);
    RandomFillVectorFile(out, numberElements);
  }

  fclose(out);
}
