// Wczytuje punkty z pliku
// zapisuje je w tablicy  double, dwie pierwsze liczby to wymiary grafu
// nastepnie pierwszy wymiar okresla numer wierzcholka a w drugim jest
// zapisywana lista sasiedztwa dla tego wierzcholka wraz z odleglosciami

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "points.h"

point_t init_pt(int id) {
    return (point_t) {.id=id, .n=0, .adjacent=malloc(sizeof(int)),
            .weights=malloc(sizeof(double))};
}

graph_t init_gt(int n) {
    graph_t g={.n=n, .points=malloc(n*sizeof(point_t))};
    int i=0;
    for(;i<n;i++)
        g.points[i]= init_pt(i);
    return g;
}

void add_to_point(point_t *p, int id, double weight) {
    p->adjacent = realloc(p->adjacent, ++p->n * sizeof *p->adjacent);
    p->weights = realloc(p->weights, p->n * sizeof *p->weights);
    p->adjacent[p->n - 1] = id;
    p->weights[p->n - 1] = weight;
}

void add_to_graph(graph_t *g, point_t p) {
    g->points[p.id] = p;
}

graph_t read_graph(char *name) {
    int i, j, x = -1, y = -1;
    char line[1024];
    char *a;

    FILE *inf = fopen(name, "r");
    if (inf == NULL) {
        fprintf(stderr, "ERROR: Cannot read the file: %s", name);
        exit(-1);
    }


    fgets(line, 1024, inf); //read one line
    x = atoi(strtok(line, " "));    // takes first character
    y = atoi(strtok(NULL, " "));
    printf("wymiary grafu:\nx = %d, y = %d\n", x, y);

    graph_t g= init_gt(x*y);

    int nl = 0;
    while (/*(fscanf(inf, "%[^\n]", line))*/ fgets(line, 1024, inf) != NULL) {


        point_t pkt = init_pt(nl);

        int c;
        char tmp_read[32];
        for (i = 0; i < strlen(line); i++) {
            int id=-1;
            double weight=-1;
            while (isspace(line[i])  && i < strlen(line))
                i++;


            if (!isdigit(line[i]) || i >= strlen(line))
                break;

            int r_i=0;
            while (isdigit(line[i]) && i<strlen(line))
                tmp_read[r_i++]=line[i++];
            tmp_read[r_i]=0;
            id= atoi(tmp_read);

            while((isspace(line[i]) || line[i]==':') && i<strlen(line))
                i++;


            r_i=0;
            while((isdigit(line[i]) || line[i]=='.')&& i<strlen(line))
                tmp_read[r_i++]=line[i++];
            tmp_read[r_i]=0;
            weight= atof(tmp_read);

            if(id!=-1 && weight!=-1)
                add_to_point(&pkt,id, weight);



        }

        add_to_graph(&g, pkt);
        nl++;
    }

    fclose(inf);

    return g;
}