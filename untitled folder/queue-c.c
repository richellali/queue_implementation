// see integrity.c for integrity statement

// Implementation file for queue-c module

// This version is implemented with two stacks

#include "stack.h"
#include "queue-c.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "cs136-trace.h"
///////////////////////////////////////
// DO NOT MODIFY THIS STRUCTURE
///////////////////////////////////////
struct queue {
  struct stack *a;
  struct stack *b;
};
///////////////////////////////////////

// O(1)
struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->a = stack_create();
  q->b = stack_create();
  return q;
}

// O(1)
void queue_add_back(int i, struct queue *q) {
  assert(q);
  stack_push(i, q->a);
}

// O(1)
bool queue_is_empty(const struct queue *q) {
  assert(q);
  return stack_is_empty(q->a) && stack_is_empty(q->b);
}

// stack_flip(dest, src) puts integers in src into dest in a
// reverse order.
// effect: modifies *dest, *src

void stack_flip(struct stack *dest, struct stack *src) {
  assert(dest);
  assert(src);
  while (!stack_is_empty(src)) {
      int temp = stack_pop(src);
      stack_push(temp, dest);
    }
}

// O(1) or O(n)
int queue_remove_front(struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  int retval = 0;

  if (stack_is_empty(q->b)) {
    stack_flip(q->b, q->a);
  }
  retval = stack_pop(q->b);
  return retval;
}
// O(1) or O(n)
int queue_front(struct queue *q) {
  assert(q);
  assert(!queue_is_empty(q));
  
  if (stack_is_empty(q->b)) {
    stack_flip(q->b, q->a);
  }
  int retval = stack_top(q->b);
  return retval;
}

// O(1)
void queue_destroy(struct queue *q) {
  assert(q);
  stack_destroy(q->a);
  stack_destroy(q->b);
  free(q);
}

// O(n)
void queue_print(struct queue *q) {
  assert(q);

  // empty queue
  if (queue_is_empty(q)) {
    printf("[empty]\n");
    return;
  } 
  if (stack_is_empty(q->a)) {
    int temp = stack_pop(q->b);
    if (stack_is_empty(q->b)) {
      printf("[%d]\n", temp);
      stack_push(temp, q->b);
      return;
    } else {
      stack_push(temp, q->b);
      struct stack *new_stack = stack_create();
      stack_flip(new_stack, q->b);
      int top = stack_pop(new_stack);
      stack_flip(q->b, new_stack);
      printf("[");
      while(!stack_is_empty(q->b)) {
        int item = stack_pop(q->b);
        printf("%d->", item);
        stack_push(item, new_stack);
      }
      printf("%d]\n", top);
      stack_push(top, new_stack);
      stack_flip(q->b, new_stack);
      stack_destroy(new_stack);
      return;
    }
  } else if (stack_is_empty(q->b)) {
    int temp = stack_pop(q->a);
    if (stack_is_empty(q->a)) {
      printf("[%d]\n", temp);
      stack_push(temp, q->a);
    } else {
      struct stack *new_stack = stack_create();
      stack_flip(new_stack, q->a);
      printf("[");
      while(!stack_is_empty(new_stack)) {
        int item = stack_pop(new_stack);
        printf("%d->", item);
        stack_push(item, q->a);
      }
      printf("%d]\n", temp);
      stack_push(temp, q->a);
      stack_destroy(new_stack);
      return;
    }
  } else {
    int temp = stack_pop(q->a);
    struct stack *new_stack = stack_create();
    printf("[");
    while(!stack_is_empty(q->b)) {
      int item = stack_pop(q->b);
      printf("%d->", item);
      stack_push(item, new_stack);
    }
    stack_flip(q->b, new_stack);
    stack_flip(new_stack, q->a);
    while(!stack_is_empty(new_stack)) {
      int item = stack_pop(new_stack);
      printf("%d->", item);
      stack_push(item, q->a);
    }
    printf("%d]\n", temp);
    stack_push(temp, q->a);
    stack_destroy(new_stack);
  }
}

