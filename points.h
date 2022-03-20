#ifndef GRAF_W_C_POINTS_H
#define GRAF_W_C_POINTS_H

#include <stdio.h>

typedef struct {
    int num;
    double* weight;
}points_t;

int read_pts(FILE* inf, points_t *pts);

#endif //GRAF_W_C_POINTS_H

