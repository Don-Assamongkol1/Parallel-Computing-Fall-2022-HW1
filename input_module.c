#include "input_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_input(char *filename, graph_t *graph) {
    FILE *input_file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];

    fgets(line, MAX_LINE_LENGTH, input_file);  // reads the first line of the file
    graph->N = line[0] - '0';                  // cast char to int
    graph->adjacency_matrix = calloc(graph->N, sizeof(int *));

    for (int i = 0; i < graph->N; i++) {
        fgets(line, MAX_LINE_LENGTH, input_file);

        int *row = calloc(graph->N, sizeof(int));
        char *delimeter = " ";
        int j = 0;
        char *ptr = strtok(line, delimeter);

        while (ptr != NULL) {
            if (ptr[0] == 'i') {
                row[j] = INFINITY;
            } else {
                row[j] = atoi(ptr);
            }
            ptr = strtok(NULL, delimeter);
            j += 1;
        }
        graph->adjacency_matrix[i] = row;
    }
}