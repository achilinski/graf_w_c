// zawiera algorytm BFS
#include <stdio.h>

#include "bfs.h"

int *tab;
int n = 0;

void add_to_que(int data) {
    if (n == 0) {
        tab = malloc(sizeof *tab);
        n++;
    } else
        tab = realloc(tab, ++n * sizeof *tab);

    tab[n - 1] = data;

}

int remove_from_que() {
    int tr, i;
    tr = tab[0];
    for (i = 1; i < n; i++) {
        tab[i - 1] = tab[i];
    }

    n--;
    return tr;
}

int is_que_empty() {
    if (n == 0)
        return 1;
    return 0;
}

int bfs(graph_t *g) {
    add_to_que(0);

    int *visited = calloc(g->n, sizeof(int));
    visited[0] = 1;
    int v;
    while (is_que_empty() == 0) {
        v = remove_from_que();
        int j = 0;
        for (; j < g->points[v].n; j++) {
            if (visited[g->points[v].adjacent[j]] == 1)
                continue;
            add_to_que(g->points[v].adjacent[j]);
            visited[g->points[v].adjacent[j]] = 1;
        }
    }
    int i = 0;
    for (; i < g->n; i++)
        if (visited[i] == 0) {
            printf("Nieodw: %d\n", i);
            return 0;
        }
    return 1;
}
