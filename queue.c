#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct queue_t {
    node_t* head;
    node_t* tail;
} queue_t;

typedef struct node_t {
    node_t* next_node;
    node_t* prev_node;
    payload_t* payload;
} node_t;

queue_t* queue_new() {

    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));

    if (queue == NULL) {
        return NULL;
    }

    queue->head = queue->tail = NULL;

    return queue;
}

int queue_free(queue_t* queue) {

    if (queue == NULL) return 1;

    while (queue->head != NULL) {

        node_t* node = queue->head;

        queue->head = queue->head->next_node;

        free(node->payload);
        free(node);
    }

    free(queue);

    return 0;
}

void queue_flush(queue_t* queue) {   
    queue->head = NULL;
    queue->tail = NULL;
}

int queue_empty(queue_t* queue) {

    if (queue == NULL || queue->head == NULL) {
        return 1;
    }

    return 0;
}

uint8_t queue_enqueue(queue_t* queue, payload_t* payload) {

    if (queue == NULL) return 1;

    node_t* node = (node_t*)malloc(sizeof(node_t));

    if (node == NULL) {
        return 1;
    }

    node->payload = payload;
    node->next_node = NULL;
    node->prev_node = NULL;

    if (queue->tail == NULL) {
        queue->head = queue->tail = node;
    }
    else {

        node_t* _node = queue->head;

        if (node->payload->priority > _node->payload->priority) {
            node->next_node = _node;
            _node->prev_node = node;
            queue->head = node;
        }
        else {
            while (_node->next_node != NULL && node->payload->priority <= _node->payload->priority) {
                _node = _node->next_node;
            }

            if (node->payload->priority > _node->payload->priority) {

                node->prev_node = _node->prev_node;
                node->next_node = _node;

                _node->prev_node->next_node = node;
                _node->prev_node = node;
            }
            else {
                queue->tail->next_node = node;
                node->prev_node = queue->tail;
                queue->tail = node;
            }
        }
    }
    
    return 0;
}

payload_t* queue_dequeue(queue_t* queue) {

    if (queue == NULL || queue->head == NULL) return NULL;

    payload_t* payload = queue->head->payload;

    node_t* node = queue->head;

    queue->head = queue->head->next_node;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(node);

    return payload;
}