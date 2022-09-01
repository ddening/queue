#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_queue.h"
#include "../queue.h"

#define DATA_ARR_SIZE 5

static void test_empty(queue_t* queue);
static void test_data(queue_t* queue);

void test_queue() {

    queue_t* queue = queue_new();

    test_empty(queue);
    test_data(queue);

    queue_free(queue);
}

static void test_empty(queue_t* queue) {

    assert(queue_empty(queue) == 1);

    uint8_t* data = (uint8_t*)malloc(sizeof(uint8_t) * 10);

    payload_t* payload = payload_create_spi(PRIORITY_NORMAL, NULL, data, 10, NULL);

    for (int i = 0; i < 1000; i++) {
        queue_enqueue(queue, payload);
        assert(queue_empty(queue) == 0);
    }

    for (int i = 0; i < 1000; i++) {
        queue_dequeue(queue);
    }
    assert(queue_empty(queue) == 1);

    free(data);
    free(payload);
}

static void test_data(queue_t* queue) {

    assert(queue_empty(queue) == 1);

    uint8_t* data[DATA_ARR_SIZE];
    payload_t* payload[DATA_ARR_SIZE];

    uint8_t data_sequence[DATA_ARR_SIZE] = { 1, 2, 3, 4, 5 };
    uint8_t data_priority[DATA_ARR_SIZE] =
    { PRIORITY_LOW, PRIORITY_LOW, PRIORITY_NORMAL, PRIORITY_HIGH, PRIORITY_NORMAL };
    uint8_t data_sequence_expected[DATA_ARR_SIZE] = { 4, 3, 5, 1, 2 };

    /* create data array */
    for (int i = 0; i < DATA_ARR_SIZE; i++) {
        data[i] = (uint8_t*)malloc(sizeof(uint8_t) * 1);
    }

    for (int i = 0; i < DATA_ARR_SIZE; i++) {
        *(data[i]) = data_sequence[i];
    }

    /* create payload array */
    for (int i = 0; i < DATA_ARR_SIZE; i++) {
        payload[i] = payload_create_spi(data_priority[i], NULL, data[i], 1, NULL);
    }

    /* enqueue payloads */
    for (int i = 0; i < DATA_ARR_SIZE; i++) {
        queue_enqueue(queue, payload[i]);
    }

    payload_t* _payloud;

    for (int i = 0; i < DATA_ARR_SIZE; i++) {
        _payloud = queue_dequeue(queue);
        printf("Payload: %i, Priority: %i\n", (int)*(_payloud->spi->data), _payloud->priority);
        assert((int)*(_payloud->spi->data) == data_sequence_expected[i]);
    }

    assert(queue_empty(queue) == 1);

    for (int i = 0; i < DATA_ARR_SIZE; i++) {
        free(data[i]);
    }

    for (int i = 0; i < DATA_ARR_SIZE; i++) {
        free(payload[i]);
    }
}