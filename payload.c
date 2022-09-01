/* User defined libraries */
#include "payload.h"

static payload_t* payload_create(priority_t priority, spi_payload_t* spi) {

    payload_t* payload = (payload_t*)malloc(sizeof(payload_t));

    if (payload == NULL) {
        return NULL;
    }

    payload->priority = priority;
    payload->spi = spi;

    return payload;
}

payload_t* payload_create_spi(priority_t priority, device_t* device, const uint8_t* data, uint8_t number_of_bytes, callback_fn* callback) {

    spi_payload_t* spi_payload = (spi_payload_t*)malloc(sizeof(spi_payload_t));

    if (spi_payload == NULL) {
        return NULL;
    }

    spi_payload->device = device;
    spi_payload->data = data;
    spi_payload->number_of_bytes = number_of_bytes;
    spi_payload->callback = callback;
    spi_payload->container = NULL;

    payload_t* payload = payload_create(priority, spi_payload);

    return payload;
}
