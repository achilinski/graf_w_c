#ifndef GRAF_W_C_POINTS_H
#define GRAF_W_C_POINTS_H

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    int *adjacent;
    double *weights;
    int n;
} point_t;


typedef struct {
    point_t *points;
    int n;
    int en;
} graph_t;

point_t init_pt();

graph_t init_gt(int);


void add_to_point(point_t *p, int id, double weight);

void add_to_graph(graph_t *g, point_t p);

graph_t read_graph(char *name);

#endif //GRAF_W_C_POINTS_H

