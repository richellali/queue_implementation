// see integrity.c for integrity statement

// Implementation file for queue-b module

// This version is implemented in a circular array

#include "queue-b.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "cs136-trace.h"
///////////////////////////////////////
// DO NOT MODIFY THIS STRUCTURE
///////////////////////////////////////
struct queue {
  int *data;
  int front;     // the index of the front item
  int len;
  int maxlen;
};
///////////////////////////////////////


struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->front = 0;
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
  //trace_int(q->front);
  int old_max = q->maxlen;
  if (q->len == q->maxlen) {
    int *old_q = q->data;
    int rest_len = q->front + q->len - q->maxlen;
    q->maxlen *= 2;
    q->data = malloc(q->maxlen * sizeof(int));
    int index = 0;
    for (int i = q->front; i < q->front + q->len && i < old_max; i++) {
      q->data[index] = old_q[i];
      index++;
    }
    if (rest_len > 0) {
      for (int i = 0; i < rest_len; i++) {
        q->data[index] = old_q[i];
        index++;
      }
    }
    q->front = 0;
    free(old_q);
  }

  if (q->front + q->len >= q->maxlen) {
    q->data[q->front + q->len - q->maxlen] = i;
  } else {
    q->data[q->front + q->len] = i;
  }
  trace_int(q->maxlen);
  trace_int(q->front);
  trace_int(q->data[q->front]);
  q->len++;

}

int queue_remove_front(struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));

  int retval = q->data[q->front];
  q->front++;
  q->len--;
  int old_max = q->maxlen;
  if (q->len == q->maxlen / 4 && q->maxlen >= 4) {
    int *old_q = q->data;
    int rest_len = q->front + q->len - q->maxlen;
    q->maxlen /= 2;
    q->data = malloc(q->maxlen * sizeof(int));
    int index = 0;
    for (int i = q->front; i < q->front + q->len && i < old_max;
         i++) {
      q->data[index] = old_q[i];
      index++;
    }
    if (rest_len > 0) {
      for (int i = 0; i < rest_len; i++) {
        q->data[index] = old_q[i];
        index++;
      }
    }
    q->front = 0;
    free(old_q);
  }
  if (q->front == q->maxlen) {
    q->front = 0;
  }
  trace_int(q->front);
  trace_int(q->maxlen);
  trace_int(q->data[q->front]);
  return retval;
}

int queue_front(const struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));

  return q->data[q->front];
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
    printf("[%d]\n", q->data[q->front]);
  } else {
    printf("[");
    int rest_len = q->front + q->len - q->maxlen;
    for (int i = q->front; i < q->front + q->len - 1
         && i < q->maxlen; i++) {
      printf("%d->", q->data[i]);
    }
    if (rest_len > 0) {
      for (int i = 0; i < rest_len - 1; i++) {
        printf("%d->", q->data[i]);
      }
      printf("%d]\n", q->data[rest_len - 1]);
      return;
    }
    printf("%d]\n", q->data[q->front + q->len - 1]);
  }
}