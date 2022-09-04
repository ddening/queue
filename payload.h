#ifndef PAYLOAD_H_
#define PAYLOAD_H_

/* General libraries */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct spi_payload_t spi_payload_t;

typedef struct i2c_payload_t i2c_payload_t;

/* ==================================
            GENERIC PAYLOAD
   ================================== */

typedef enum priority_t {
    PRIORITY_LOW,
    PRIORITY_NORMAL,
    PRIORITY_HIGH
} priority_t;

typedef struct payload_t {
    priority_t priority;
    spi_payload_t* spi;
    i2c_payload_t* i2c;
} payload_t;

/* ==================================
            CUSTOM PAYLOADS
   ================================== */

typedef struct device_t device_t;

typedef void (callback_fn)(void);

typedef enum read_write_t {
    WRITE,
    READ,
    READ_WRITE
} read_write_t;

typedef struct spi_payload_t {
    device_t* device;
    const uint8_t* data;
    uint8_t number_of_bytes;
    callback_fn* callback;
    uint8_t* container;
    read_write_t mode;
} spi_payload_t;

payload_t* payload_create_spi(priority_t priority, device_t* device, const uint8_t* data, uint8_t number_of_bytes, callback_fn* callback);

#endif /* PAYLOAD_H_ */