#include "garbageCollector.h"

typedef struct GCPtr{

  void *ptr;
  struct GCPtr *prev;
  struct GCPtr *next;
}GCPtr;

static GCPtr *first;
static GCPtr *GetLastGCNode();
static GCPtr *GetGCNode(void *ptr);
static void AddGCNode(void *ptr);
static void RemoveGCNode(void *ptr);

static GCPtr *GetLastGCNode(){

  if(first == NULL)
    return NULL;

  GCPtr *result = first;
  while(result->next != NULL)
    result = result->next;

  return result;
}

static GCPtr *GetGCNode(void *ptr){

  if(ptr == NULL)
    return NULL;

  GCPtr *result = first;
  do{

    if(result->ptr == ptr)
      return result;
  }while(result->next != NULL);

  return NULL;
}

static void AddGCNode(void *ptr){

  if(ptr == NULL)
    return;

  GCPtr *result = malloc(sizeof(GCPtr));
  result->ptr = ptr;
  result->next = NULL;
  
  if(first == NULL){
    first = result;
    return;
  }
  
  GCPtr *last = GetLastGCNode();
  last->next = result;
  result->prev = last;
}

static void RemoveGCNode(void *ptr){

  if(ptr == NULL)
    return;
  
  GCPtr *find = GetGCNode(ptr);

  if(find == NULL)
    return;

  free(ptr);
  find->prev->next = find->next;
  find->next->prev = find->prev;
  free(find);
}

void *malloc_gc(size_t size){

  void *ptr = malloc(size);
  AddGCNode(ptr);
  return ptr;
}

void free_gc(void *ptr){
  RemoveGCNode(ptr);
}

void RunGC(){

  GCPtr *tmp;
  GCPtr *current = first;

  while(current->next != NULL){

    tmp = current->next;
    free(current->ptr);
    free(current);
    current = tmp;
  }
  free(current->ptr);
  free(current);
}
