// see integrity.c for integrity statement

// Implementation file for queue-a module

// This version is implemented in a traditional array
// where the front of queue is always in index 0 (q->data[0])

#include "queue-a.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


///////////////////////////////////////
// DO NOT MODIFY THIS STRUCTURE
///////////////////////////////////////
struct queue {
  int *data;
  int len;
  int maxlen;
};
///////////////////////////////////////

struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->len = 0;
  q->maxlen = 1;
  q->data = malloc(q->maxlen * sizeof(int));
  return q;
}

bool queue_is_empty(const struct queue *q) {
  assert(q);
  return q->len == 0;
}


void queue_add_back(int i, struct queue *q) {
  assert(q);
  
  //resize
  if (q->len == q->maxlen) {
    q->maxlen *= 2;
    q->data = realloc(q->data, q->maxlen * sizeof(int));
  }
  q->data[q->len] = i;
  q->len++;
}


int queue_remove_front(struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  
  int retval = q->data[0];
  int len = q->len - 1;
  for(int i = 0; i < len; i++) {
    q->data[i] = q->data[i + 1];
  }
  q->len--;
  // resize
  if (q->len == q->maxlen / 4 && q->maxlen >= 4) {
    q->maxlen /= 2;
    q->data = realloc(q->data, q->maxlen * sizeof(int));
  }
  return retval;
}

// O(1)
int queue_front(const struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  
  return q->data[0];
}


void queue_destroy(struct queue *q) {
  assert(q);
  
  free(q->data);
  free(q);
}


void queue_print(const struct queue *q) {
  assert(q);
  
  if (q->len == 0) {
    printf("[empty]\n");
  } else if (q->len == 1) {
    printf("[%d]\n", q->data[0]);
  } else {
    printf("[");
    for (int i = 0; i < q->len - 1; i++) {
      printf("%d->", q->data[i]);
    }
    printf("%d]\n", q->data[q->len - 1]);
  }
}