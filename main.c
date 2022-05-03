// steruje praca programu
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "points.h"
#include "bfs.h"
#include "dijkstra.h"
#include "gen.h"
#include <sys/time.h>

int czy_n(char *n) {
    while (*n != 0)
        if (isdigit(*n))
            n++;
        else
            return 0;
    return 1;
}

int main(int argc, char **argv) {

	struct timeval begin, end;
	gettimeofday(&begin, 0);
	

    int generate = 0, route = 0, integrity = 0, time = 0, size_x, size_y, route_a, route_b;
    int in_f_i = -1, out_f_i = -1;
    //program zwraca kod błędu 2 dla złego formatu argumentów programu.
    if (argc < 2){
        printf("Należy podać argumenty wywołania programu\n--size x y – określa wymiar grafu\n--route a b – określa najkrótszą ścieżkę między wybranymi punktami\n--input <File_Name> - program wczytuje dane z pliku o podanej nazwie. Gdy niepodajemy pliku do wczytania należy podać wymiaru grafu do wygenerowania.\n--output <File_Name> - program zapisuje wyniki do pliku o podanej nazwie\n--int – program zapisuje do pliku wynikowego informacje czy graf jest spójny\n");
        exit(2);
    }
    int i;
    for (i = 1; i < argc; i++)
        if (strcmp(argv[i], "--size") == 0) {
            if (i + 2 >= argc) {
                printf("Zły argument w --size.\n");
                exit(2);
            }

            if (!czy_n(argv[i + 1]) || !czy_n(argv[i + 2])) {
                printf("Zły argument w --size.\n");
                exit(2);
            }

            generate = 1;
            size_x = atoi(argv[++i]);
            size_y = atoi(argv[++i]);


        } else if (strcmp(argv[i], "--route") == 0) {
            if (i + 2 >= argc) {
                printf("Zły argument w --route.\n");
                exit(2);
            }

            if (!czy_n(argv[i + 1]) || !czy_n(argv[i + 2])) {
                printf("Zły argument w --route.\n");
                exit(2);
            }

            route = 1;
            route_a = atoi(argv[++i]);
            route_b = atoi(argv[++i]);


        } else if (strcmp(argv[i], "--int") == 0)
            integrity = 1;
        else if (strcmp(argv[i], "--input") == 0) {
            if (i + 1 >= argc) {
                printf("Zły argument w --input.\n");
                exit(2);
            }

            in_f_i = ++i;
        } else if (strcmp(argv[i], "--output") == 0) {
            if (i + 1 >= argc) {
                printf("Zły argument w --output.\n");
                exit(2);
            }

            out_f_i = ++i;
	}else if(strcmp(argv[i], "--time")==0) {
		time = 1;
        } else {
            printf("Zły argument - nieznany!!\n");
            exit(2);
        }

    if (in_f_i == -1 && generate == 0) {
	    fprintf(stderr, "Nalezy podac wymiary grafu do generowania lub plik do otwarcia z grafem");
	    exit(2);
    }
	
    graph_t g;
    if (generate == 1) {
        if(out_f_i==-1){
            fprintf(stderr, "Nie podano pliku do zapisu grafu! --output <plik> \n");
            exit(2);
        }
        g = gen_graph(size_x, size_y);//read_graph(argv[in_f_i]);
        write_tf(argv[out_f_i], &g, size_x, size_y);
    } else {
        g = read_graph(argv[in_f_i]);
    }

    if (route == 1) {
        if(bfs(&g)==0){
            fprintf(stderr, "Graf nie jest spojny, nie mozna uzyc alg. Dijkstry!\n");
            exit(6);
        }
        dijkstra(&g, route_a, route_b);
    }
    if (integrity == 1)
        printf("czy spojny: %d\n", bfs(&g));

    if (time == 1) {
	FILE * tfile = fopen("time_recorded.txt", "a");
	if(tfile == NULL) {
		fprintf(stderr, "Blad w otwarciu pliku %s do zapisu czasu", tfile);
		exit(4);
	}
	
	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds*1e-6;
	fprintf(stderr, "minelo: %.3f seconds.\n", elapsed);
	fprintf(tfile, "%f	%d\n", elapsed, g.n);
    }

    return 0;
}

