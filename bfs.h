
#ifndef GRAF_W_C_BFS_H
#define GRAF_W_C_BFS_H

#include <stdlib.h>
#include "points.h"


void que_init();

void add_to_que(int data);

int remove_from_que();

int is_que_empty();

int bfs(graph_t *g);

#endif //GRAF_W_C_BFS_H
