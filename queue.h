#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include "./payload.h"

// #define QUEUE_MAX_SIZE 10

typedef struct queue_t queue_t;

typedef struct node_t node_t;

typedef struct payload_t payload_t;

queue_t* queue_new();

int queue_free(queue_t*);

void queue_flush(queue_t* queue);

int queue_empty(queue_t*);

uint8_t queue_enqueue(queue_t*, payload_t*);

payload_t* queue_dequeue(queue_t*);

#endif /* QUEUE_H_ */