// Wczytuje punkty z pliku
// zapisuje je w tablicy  double, dwie pierwsze liczby to wymiary grafu
// nastepnie pierwszy wymiar okresla numer wierzcholka a w drugim jest
// zapisywana lista sasiedztwa dla tego wierzcholka wraz z odleglosciami

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_graf(char* name, double** t) {
    int i, j;
    char line[255];
    char* a;

    FILE* inf = fopen(name, "r");
    if(inf == NULL) {
        printf("ERROR: Cannot read the file");
        exit(-1);
    }

    fgets(line, 255, inf); //read one line
    t[0][0] = atoi(strtok(line, " "));    // takes first character
    t[0][1] = atoi(strtok(NULL, " "));
    printf("wymiary grafu:\nx = %d, y = %d\n", x, y);

    j = 1;
    i = 2;
    while(fgets(line, 255, inf) != NULL) {
        strtok(line, " ");
        while(a = strtok(NULL, " :")) {
            t[j][i] = atof(a);
            i++;
        }
        j++;
    }

    for(j = 0; j < i; j++) {
        printf(" %g ", t[j]);
    }

    return 0;
}