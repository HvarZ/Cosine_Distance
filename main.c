#include "neutral_functions.h"
#include "file_generator.h"

#include <getopt.h>
#include <time.h>
#include <string.h>

#define MAX_BASE_SIZE 1000000
#define MAX_VECTOR_SIZE 3

int main(int argc, char *argv[]) {
  int opt;
  char *opts = "i:o:gh";
  char *input = NULL;
  char *output = NULL;
  vector_t vector;

  while ((opt = getopt(argc, argv, opts)) != -1) {
    switch (opt) {
    case 'i':
      input = malloc((strlen(optarg) + 1) * sizeof(char));
      strcpy(input, optarg);
      break;
    case 'o':
      output = malloc((strlen(optarg) + 1) * sizeof(char));
      strcpy(output, optarg);
      break;
    case 'g':
      if (input != NULL) {
        RandomFillBaseFile(input, MAX_BASE_SIZE, MAX_VECTOR_SIZE);
      }
      break;
    case 'h':
      printf("Usage: %s [-h|-i|-o|-g] <args>\n", argv[0]);
      break;
    default:
      break;
    }
  }

  vector.size = MAX_VECTOR_SIZE;
  vector.data = (float*)malloc(MAX_VECTOR_SIZE * sizeof(float));
  if (vector.data == NULL) {
    exit(-1);
  }
  vector.data[0] = vector.data[1] = vector.data[2] = 0;

  base_t base;
  CreateBase(&base, MAX_BASE_SIZE, MAX_VECTOR_SIZE);
  ReadBaseFromFile(&base, input);

  struct timespec start, end;

  clock_gettime(CLOCK_MONOTONIC, &start);

  const vector_t* nearestVector = MinVectorCosDistance(&base, &vector);

  clock_gettime(CLOCK_MONOTONIC, &end);
  size_t time = (1000000000 * (end.tv_sec - start.tv_sec) +
                 (end.tv_nsec - start.tv_nsec)) / 1000;

  if (!output) {
    printf("Result : ");
    for (size_t i = 0; i < nearestVector->size; ++i) {
      printf("%f ", nearestVector->data[i]);
    }
    printf("\n");
    printf("Time : %zu mks\n\n", time);
  } else {
    FILE *file = fopen(output, "w");

    if (!file) {
      printf("Opening file failed\n");
      return 1;
    }

    fprintf(file, "Result : ");
    for (size_t i = 0; i < nearestVector->size; ++i) {
      fprintf(file, "%f ", nearestVector->data[i]);
    }
    fprintf(file,"\n");
    fprintf(file, "Time : %zu mks\n\n", time);

    if (fclose(file)) {
      printf("Closing file failed\n");
      return 1;
    }
  }

  ClearBase(&base);
  ClearVector(&vector);


  free(output);
  free(input);

  return EXIT_SUCCESS;
}
