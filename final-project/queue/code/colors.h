#ifndef COLOR_H
#define COLOR_H

typedef enum {
    blue,
    red,
    green,
    reset
} color;

void set_color(color choosed_color);

#endif