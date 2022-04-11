// steruje praca programu
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "points.h"
#include "bfs.h"
#include "dijkstra.h"

int czy_n(char *n) {
    while (*n != 0)
        if (isdigit(*n))
            n++;
        else
            return 0;
    return 1;
}

int main(int argc, char **argv) {
    int generate = 0, route = 0, integrity = 0, size_x, size_y, route_a, route_b;
    int in_f_i = -1, out_f_i = -1;
    graph_t g= read_graph(argv[in_f_i]);

    //program zwraca kod błędu 2 dla złego formatu argumentów programu.

    int i;
    for (i = 1; i < argc; i++)
        if (strcmp(argv[i], "--size") == 0) {
            if (i + 2 >= argc) {
                printf("Zły argument w --size.\n");
                exit(2);
            }

            if (!czy_n(argv[i + 1]) || !czy_n(argv[i + 2])){
                printf("Zły argument w --size.\n");
                exit(2);
            }

            generate = 1;
            size_x = atoi(argv[++i]);
            size_y = atoi(argv[++i]);

        }
        else if (strcmp(argv[i], "--route") == 0) {
            if (i + 2 >= argc){
                printf("Zły argument w --route.\n");
                exit(2);
            }

            if (!czy_n(argv[i + 1]) || !czy_n(argv[i + 2])){
                printf("Zły argument w --route.\n");
                exit(2);
            }

            route = 1;
            route_a = atoi(argv[++i]);
            route_b = atoi(argv[++i]);
            dijkstra (&g, route_a, route_b);

        }
        else if (strcmp(argv[i], "--int") == 0)
            integrity=1;
        else if(strcmp(argv[i], "--input") == 0){
            if(i+1>=argc){
                printf("Zły argument w --input.\n");
                exit(2);
            }

            in_f_i=++i;
        }
        else if(strcmp(argv[i], "--output") == 0){
            if(i+1>=argc){
                printf("Zły argument w --output.\n");
                exit(2);
            }

            out_f_i=++i;
        }else{
            printf("Zły argument - nieznany!!\n");
            exit(2);
        }








    printf("czy sp: %d\n", bfs(&g));





    return 0;
}

