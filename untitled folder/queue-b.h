// SEASHELL_READONLY   [do not copy/paste this line into a .c file]

// This is a module that provides a queue of integers ADT

// NOTE: all queue parameters must be valid (non-null) queues

// times: n is the length of the queue (number of items)

#include <stdbool.h>

struct queue;

// queue_create() crates a new empty queue
// effects: allocates memory (client must call queue_destroy)
// time: O(1)
struct queue *queue_create(void);

// queue_add_back(i, q) adds i to the back of q
// effects: modifies q
// time: O(1) [amortized]
void queue_add_back(int i, struct queue *q);

// queue_remove_front(q) removes and returns the item at the front of q
// requires: q is not empty
// effects: modifies q
// time: O(1) [amortized]
int queue_remove_front(struct queue *q);

// queue_front(q) returns the item at the front of q
// requires: q is not empty
// time: O(1)
int queue_front(const struct queue *q);

// queue_is_empty(q) determines if q is empty
// time: O(1)
bool queue_is_empty(const struct queue *q);

// queue_destroy(q) frees all memory for q
// effects: q is no longer valid
// time: O(1)
void queue_destroy(struct queue *q);

// queue_print(q) prints the current queue
// notes: prints "[empty]\n" if q is empty
//        prints "[%d]\n" if q has a single item
//        prints "[%d->%d->...->%d]\n" otherwise 
//               so if the queue from front->back is 8, 6, 7, 5, 3, 0, 9
//               prints "[8->6->7->5->3->0->9]\n"
// effects: displays output
// time: O(n)
void queue_print(const struct queue *q);
