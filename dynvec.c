#include "dynvec.h"
#include <string.h>
#include <stdio.h>

#define TRY(X) { int status = X; if(status != 0) return status; }

int checked_realloc(void **pp, size_t new_size) {
  void *p = realloc(*pp, new_size);
  if(p == NULL) {
    return 1;
  }
  *pp = p;
  return 0;
}

dynamic_vector_t* DVCreate(size_t num_elems, size_t elem_size) {
  dynamic_vector_t *self;

  self = malloc(sizeof(dynamic_vector_t));
  self->elem_size = elem_size;
  self->num_elems = num_elems;
  self->capacity = 0;
  self->array = NULL;
  DVReserve(self, self->num_elems);
  return self;
}

void DVDestroy(dynamic_vector_t* self) {
  free(self->array);
  free(self);
}

void* DVItemAddress(dynamic_vector_t* self, size_t index) {
  if(index >= self->num_elems) {
    return NULL;
  }
  return self->array + index * self->elem_size;
}

int DVPushBack(dynamic_vector_t* self, void *data) {
  self->num_elems += 1;
  if(self->capacity < self->num_elems) {
    TRY(DVReserve(self, self->capacity * 2))
  }
  memcpy(DVItemAddress(self, self->num_elems - 1), data, self->elem_size);
  return 0;
}

int DVReserve(dynamic_vector_t* self, size_t new_capacity) {
  if(new_capacity > self->capacity) {
    self->capacity = new_capacity;
    TRY(checked_realloc(&self->array, self->capacity * self->elem_size));
    if(self->array == NULL) {
      exit(1);
    }
  }
  return 0;
}

size_t DVSize(dynamic_vector_t* self) {
  return self->num_elems;
}

size_t DVCapacity(dynamic_vector_t* self) {
  return self->capacity;
}

void DVPopBack(dynamic_vector_t* self) {
  self->num_elems -= 1;
  if(self->num_elems < self->capacity / 4) {
    void *shrunk;

    self->capacity = self->capacity / 2;
    shrunk = malloc(self->capacity * self->elem_size);
    memcpy(shrunk, self->array, self->capacity * self->elem_size);
    free(self->array);
    self->array = shrunk;
  }
}
