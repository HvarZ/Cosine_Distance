#include <gtest/gtest.h>

extern "C" {
#include "neutral_functions.h"
}

TEST(dynamic, CreateBase) {
  base_t base;
  CreateBase(&base, 5, 5);
  ASSERT_EQ(base.size, 5);
  ASSERT_EQ(base.data[0].size, 5);

  ClearBase(&base);
}

TEST(dynamic, ClearTest) {
  base_t base;
  CreateBase(&base, 5, 5);

  ClearBase(&base);
  ASSERT_EQ(base.size, 0);
}

TEST(dynamic, RandomFillVector) {
  vector_t vector;
  RandomFillVector(&vector, 10);

  ASSERT_EQ(vector.size, 10);
  ClearVector(&vector);
}

TEST(dynamic, ClearVector) {
  vector_t vector;
  RandomFillVector(&vector, 10);

  ClearVector(&vector);
  ASSERT_EQ(vector.size, 0);
}

TEST(dynamic, Dot) {
  vector_t vector1;
  vector1.size = 0;
  vector_t vector2;
  vector2.size = 0;
  ASSERT_EQ(-FLT_MAX, Dot(&vector1, &vector2));
  vector1.size = 2;
  vector1.data = (float *)malloc(2 * sizeof(float));
  vector2.size = 2;
  vector2.data = (float *)malloc(2 * sizeof(float));
  vector1.data[0] = vector1.data[1] = vector2.data[0] = vector2.data[1] = 0;
  ASSERT_EQ(Dot(&vector1, &vector2), 0);
  ClearVector(&vector1);
  ClearVector(&vector2);
}

TEST(dynamic, Length) {
  vector_t vector1;
  vector1.size = 0;
  ASSERT_EQ(Length(&vector1), 0);
  vector1.data = (float *)malloc(1 * sizeof(float));
  vector1.size = 1;
  vector1.data[0] = 4;
  ASSERT_EQ(Length(&vector1), 4);
  ClearVector(&vector1);
}

TEST(dynamic, CosDistance) {
  vector_t vector1;
  vector1.size = 0;
  vector_t vector2;
  vector2.size = 0;
  ASSERT_EQ(-FLT_MAX, CosDistance(&vector1, &vector2));
  vector1.size = 1;
  vector1.data = (float *)malloc(1 * sizeof(float));
  vector2.size = 1;
  vector2.data = (float *)malloc(1 * sizeof(float));
  vector1.data[0] = 1;
  vector2.data[0] = 1;
  ASSERT_EQ(CosDistance(&vector1, &vector2), 0);
  ClearVector(&vector1);
  ClearVector(&vector2);
}

TEST(dynamic, ReadBaseFromFile) {
  base_t base;
  CreateBase(&base, 1000000, 3);
  ReadBaseFromFile(&base, (char *)"../results/result.txt");
  ASSERT_EQ(base.data[0].data[0], -961);
  ClearBase(&base);
}

TEST(dynamic, StressTest) {
  vector_t vector;
  vector.size = 3;
  vector.data = (float *)malloc(3 * sizeof(float));
  vector.data[0] = vector.data[1] = vector.data[2] = 0;

  base_t base;
  CreateBase(&base, 1000000, 3);
  ReadBaseFromFile(&base, (char *)"../results/input.txt");

  const vector_t *result = MinVectorCosDistance(&base, &vector);

  ASSERT_EQ(result->data[0], -137);
  ASSERT_EQ(result->data[1], -650);
  ASSERT_EQ(result->data[2], 520);

  ClearVector(&vector);
  ClearBase(&base);
}