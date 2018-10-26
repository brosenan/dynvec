#include <stdlib.h>

typedef struct dynamic_vector {
  void* array;
  size_t elem_size;
  size_t num_elems;
  size_t capacity;
} dynamic_vector_t;

dynamic_vector_t* DVCreate(size_t num_elemes, size_t elem_size);
void DVDestroy(dynamic_vector_t* self);
size_t DVSize(dynamic_vector_t* self);
size_t DVCapacity(dynamic_vector_t* self);
void* DVItemAddress(dynamic_vector_t* self, size_t index);
int DVPushBack(dynamic_vector_t* self, void *data);
void DVPopBack(dynamic_vector_t* self);
int DVReserve(dynamic_vector_t* self, size_t new_capacity);
