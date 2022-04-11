#include "gen.h"
#include <time.h>
#include <stdlib.h>

double get_rand(){
    return rand()/(double)RAND_MAX;
}

graph_t gen_graph(int x_in, int y_in) {
    srand(time(NULL));
    graph_t g = init_gt(x_in * y_in);
    int  x, y;
    for (y = 0; y < y_in; y++) {
        for (x = 0; x < x_in; x++) {
            point_t p=init_pt();
            int this_id=y*x_in+x;
            p.id=this_id;
            if (y < y_in-1) {
                //dół
                add_to_point(&p,this_id+x_in, get_rand());
            }
            if (y>0){
                //góra
                add_to_point(&p,this_id-x_in, get_rand());
            }
            if(x<x_in-1){
                //w prawo
                add_to_point(&p,this_id+1, get_rand());
            }
            if(x>0){
                //w lewo
                add_to_point(&p,this_id-1, get_rand());
            }
            add_to_graph(&g,p);
        }
    }
    printf("Wygenerowano graf...\n");
    return g;

}

void write_tf(const char * filename, graph_t *g, int x, int y){
    FILE *f=fopen(filename, "w");
    if(f==NULL){
        fprintf(stderr, "Blad w otwieraniu pliku %s", filename);
        exit(4);
    }
    fprintf(f, "%d %d\n", x, y);
    int  i,j;
    for(i=0;i<g->n;i++){
        for(j=0;j<g->points[i].n;j++)
            fprintf(f, "%d :%g ", g->points[i].adjacent[j], g->points[i].weights[j]);
        fprintf(f, "\n");
    }
    fclose(f);
}
