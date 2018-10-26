#include <assert.h>
#include "dynvec.h"

/* The basics */
void test1() {
  dynamic_vector_t* dv;
  int i;
  
  /* A dynamic vector is created using DVCreate(), taking a number of
     elements and the size of each element as parameters.*/
  dv = DVCreate(100, sizeof(int));

  /* The size of the vector is returned by DVSize() */
  assert(DVSize(dv) == 100);

  /* DVItemAddress() returns the address of a given element,
     facilitating update and retrieval. */
  for(i = 0; i < 100; i++) {
    *(int*)DVItemAddress(dv, i) = i;
  }
  for(i = 0; i < 100; i++) {
    assert(*(int*)DVItemAddress(dv, i) == i);
  }

  /* DVItemAddress() checks if the given index is within the array's
     bounds. If it isn't, it returns NULL. */
  assert(DVItemAddress(dv, 100) == NULL);

  /* DVPushBack() adds an element to the array, adding 1 to its
     capacity. */
  i = 200;
  DVPushBack(dv, &i);
  assert(DVSize(dv) == 101);
  assert(DVItemAddress(dv, 100) != NULL);
  assert(*(int*)DVItemAddress(dv, 100) == 200);

  /* DVDestroy() frees both the array and the object. */
  DVDestroy(dv);
}

/* Capacity */
void test2() {
  dynamic_vector_t* dv;
  int i;
  void* p;

  dv = DVCreate(100, sizeof(int));

  /* The dynamic vector has a capacity, visible using DVCapacity(), to
     which it can be reserved. The original capacity is the original
     array size. */
  assert(DVCapacity(dv) == 100);

  /* DVReserve() makes sure the reserved allocation is at least
     the given number of elements. If less, a reallocation is
     performed. */
  p = DVItemAddress(dv, 2);
  DVReserve(dv, 50); /* This does not trigger reallocation */
  assert(DVItemAddress(dv, 2) == p);
  assert(DVCapacity(dv) == 100);
  DVReserve(dv, 150); /* This triggers reallocation */
  assert(DVCapacity(dv) == 150);

  /* Adding elements within the reserved capacity does not cause
     a reallocation (thus element addresses remain the
     same). */
  p = DVItemAddress(dv, 2);
  for(i = 0; i < 50; i++) {
    DVPushBack(dv, &i);
  }
  assert(DVItemAddress(dv, 2) == p);

  /* When DVPushBack() is called with insufficient capacity, we double
     the capacity, to make sure the number of reallocations is
     logarithmic with the number of pushes.*/
  i = 555;
  DVPushBack(dv, &i);
  assert(DVCapacity(dv) == 300);
  
  DVDestroy(dv);
}

/* Shrinking */
void test3() {
  dynamic_vector_t* dv;
  int i;
  void* p;

  dv = DVCreate(100, sizeof(int));
  for(i = 0; i < 100; i++) {
    *(int*)DVItemAddress(dv, i) = i;
  }

  /* DVPopBack() removes the last element in the dynamic vector,
     reducing its size by one. */
  DVPopBack(dv);
  assert(DVSize(dv) == 99);

  /* Once the size shrinks below a quarter of the capacity, the
     capacity is reduced in half. */
  for(i = 99; i >= 25; i--) {
    DVPopBack(dv);
  }
  assert(DVSize(dv) == 24);
  assert(DVCapacity(dv) == 50);
  
  for(i = 0; i < 24; i++) {
    assert(*(int*)DVItemAddress(dv, i) == i);
  }

  DVDestroy(dv);
}

int main(int argc, char* argv[]) {
  test1();
  test2();
  test3();
}
