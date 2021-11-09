#include "neutral_functions.h"

#include <pthread.h>
#include <unistd.h>

typedef struct thread_info {
  base_t* base;
  size_t indexFirst;
  size_t indexLast;
  vector_t* vector;
  vector_t* result;
} thread_info_t;


void* MinVectorCosDistancePartBase(void* args) {
  if (args == NULL) {
    return NULL;
  }

  thread_info_t* currentThread = (thread_info_t*)args;

  float min = 180;

  for (size_t i = currentThread->indexFirst; i < currentThread->indexLast;
       ++i) {
    float distance =
        CosDistance(currentThread->vector, &currentThread->base->data[i]);
    if (distance < min) {
      min = distance;
      currentThread->result = &currentThread->base->data[i];
    }
  }
  return currentThread->result;
}

const vector_t* MinVectorCosDistance(base_t *base, vector_t *vector) {
  if (base == NULL || vector == NULL) {
    return NULL;
  }
  if (base->size == 0) {
    return NULL;
  }
  if (base->data[0].size != vector->size) {
    return NULL;
  }

  const size_t threads_count = sysconf(_SC_NPROCESSORS_ONLN);  // 4
  pthread_t threads[threads_count];
  thread_info_t *threadsInfo =
      (thread_info_t *)malloc(threads_count * sizeof(thread_info_t));

  for (size_t i = 0; i < threads_count; ++i) {
    threadsInfo[i].base = base;
    threadsInfo[i].indexFirst = i * (base->size / threads_count);
    threadsInfo[i].indexLast = (i + 1) * (base->size / threads_count);
    threadsInfo[i].vector = vector;
    threadsInfo[i].result = &base->data[base->size - 1];
  }

  for (size_t i = 0; i < threads_count; ++i) {
    if (pthread_create(&threads[i], NULL, MinVectorCosDistancePartBase,
                                (void *)&threadsInfo[i]) != 0) {
      return NULL;
    }
  }

  void* resultVectors[threads_count];
  for (size_t i = 0; i < threads_count; ++i) {
    if (pthread_join(threads[i], &resultVectors[i]) != 0) {
      return NULL;
    }
  }

  float min = 3.14f;
  const vector_t* result = (vector_t*)&resultVectors[threads_count - 1];

  for (size_t i = 0; i < threads_count; ++i) {
    float distance = CosDistance(vector, resultVectors[i]);
    if (distance < min) {
      min = distance;
      result = resultVectors[i];
    }
  }

  return result;
}
