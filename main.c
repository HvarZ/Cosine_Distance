#include "neutral_functions.h"
#include "file_generator.h"

int main() {
  RandomFillBaseFile("file.txt", 10, 10);

  base_t base;
  ReadBaseFromFile(&base, "file.txt");

  vector_t vector;
  FillVector(&vector);

  const vector_t* nearestVector = MinVectorCosDistance(&base, &vector);

  for (size_t i = 0; i < nearestVector->size; ++i) {
    printf("%f ", nearestVector->data[i]);
  }
  printf("\n");


  ClearBase(&base);
  return 0;
}
