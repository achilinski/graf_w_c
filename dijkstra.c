// zawiera algorytm Dijkstry
#include "points.h"
#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

typedef struct {
    int *tab;
    int n;
    int size;
} int_t;

int_t init_it(int size, int val) {
    int_t t = {.size=size, .n=0, .tab=malloc(size * sizeof(int))};
    int i = 0;
    for (; i < t.size; i++)
        t.tab[i] = val;
    return t;
}

int is_empty(int_t *t) {
    return t->n == 0 ? 1 : 0;
}

void add_to_it(int_t *t, int item) {
    if (t->tab[item] != 1) {
        t->tab[item] = 1;
        t->n++;
    }
}

void remove_from_it(int_t *t, int item) {
    if (t->tab[item] == 1) {
        t->tab[item] = 0;
        t->n--;
    }
}



int get_min_index(double *d, int n, int_t *q) {
    int i = 0;
    double min=DBL_MAX;
    int i_m=-1;
    for (; i < n; i++)
        if (d[i] < min && q->tab[i]==1) {
            i_m=i;
            min=d[i];
        }
    return i_m;

}

void dijkstra(graph_t *g, int a, int b) {
    int i;
    int_t q = init_it(g->n, 1);
    q.n = g->n;
    int_t s = init_it(g->n, 0);

    double *d = malloc(g->n * sizeof *d);

    for (i = 0; i < g->n; i++)
        d[i] = DBL_MAX;

    int *p = malloc(g->n * sizeof *p);
    for (i = 0; i < g->n; i++)
        p[i] = -1;

    d[a] = 0;
    while (!is_empty(&q)) {
        int u = get_min_index(d, g->n, &q);
        remove_from_it(&q, u);
        add_to_it(&s, u);
        int j;
        for (j = 0; j < g->points[u].n; j++) {
            int w = g->points[u].adjacent[j];
            if (q.tab[w] == 0)
                continue;
            if (d[w] > d[u] + g->points[u].weights[j]) {
                d[w] = d[u] + g->points[u].weights[j];
                p[w] = u;
            }
        }
    }

    int *p_out = malloc(g->n * sizeof *p_out);
    double *d_out = malloc(g->n * sizeof *d_out);

    int now = b;
    p_out[0] = b;
    int n = 0;
    while (now != -1) {
        p_out[n + 1] = p[now];
        d_out[n++] = d[now];
        now = p_out[n];
    }


    printf("Najkrotsza sciezka (dl. %g):\n", d_out[0]);
    while(--n)
        printf("%d -> ",p_out[n]);
    printf("%d\n", p_out[n]);

}

