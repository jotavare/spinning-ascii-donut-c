#ifndef DONUT_H
#define DONUT_H

// libraries
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// macro for the rotation
#define R(mul, shift, x, y)               \
    temp = x;                             \
    x -= mul * y >> shift;                \
    y += mul * temp >> shift;             \
    temp = 3145728 - x * x - y * y >> 11; \
    x = x * temp >> 10;                   \
    y = y * temp >> 10;

// external declaration for buffers
extern int8_t b[1760], z[1760];

// functions
void initialize_buffers();
void render_shape(int sA, int cA, int sB, int cB);
void print_frame();

#endif