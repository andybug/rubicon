#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>

#include "light_ws2812.h"

#define NUM_PIXELS 256

enum color {
        COLOR_RED = 0,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_NONE
};

struct cRGB pixels[NUM_PIXELS] = {0};


void set_pixel(uint8_t id, enum color c)
{
        struct cRGB pixel = {0};

        switch(c) {
        case COLOR_RED:
                pixel.r = 64;
                break;
        case COLOR_GREEN:
                pixel.g = 64;
                break;
        case COLOR_BLUE:
                pixel.b = 64;
                break;
        case COLOR_NONE:
                // already all-zeroes
                break;
        }

        pixels[id] = pixel;
}

void set_pixels(enum color c)
{
        uint8_t i;

        for (i = 0; i < NUM_PIXELS; i++) {
                set_pixel(i, c);
        }
}

int main(void)
{
        enum color current_color = COLOR_RED;
        uint8_t current_pixel = 0;
        uint8_t previous_pixel = 0;

        while (1) {
                //set_pixel(previous_pixel, COLOR_NONE);
                set_pixel(current_pixel, current_color);

                ws2812_setleds(pixels, NUM_PIXELS);
                _delay_ms(20);

                previous_pixel = current_pixel;
                current_pixel = (current_pixel + 1) % NUM_PIXELS;

                if (current_pixel == 0) {
                        current_color = (current_color + 1) % 3;
                }
        }

        return 0;
}
