/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"

#include "MLX90640.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS    500
// Default shift for MLX90640 in open air
#define TA_SHIFT              8

// for K64F
I2C i2c1(PTC11, PTC10);

static MLX90640 mlx(i2c1, MLX90640_ADDR);
static float mlx90640To[768];
static uint16_t frame[834];

int main()
{
    int status;
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    thread_sleep_for(BLINKING_RATE_MS);

    if (0 != mlx.init(frame))
        printf("MLX90650 paramter extraction failed\r\n");

    while (true) {

        for (int i = 0; i < 2; i++)
        {   
            if (0 > (status = mlx.getFrameData(frame)))
                printf("Get frame data Error: %d", status);

            const float Ta = mlx.getTa(frame);
            const float tr = Ta - TA_SHIFT;
            const float emissivity = 0.95f;
            mlx.calculateTo(frame, emissivity, tr, mlx90640To);
        }
        for (int i = 0; i < 10; i++) {
            printf("Pixel %d: %f °C\r\n", i, mlx90640To[i]);
        }

        led = !led;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
