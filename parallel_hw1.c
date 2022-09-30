#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 10000000
#define MAX_LINE_LENGTH 100000
#define MAX_INT_LENGTH 1000
#define MAX_STRING_LENGTH 10

typedef struct graph {
    int N;
    int **adjacency_matrix;
} graph_t;

int main() {
    printf("Running Script...\n");

    /* make adjacency matrix from reading in input */
    graph_t *graph = calloc(1, sizeof(graph_t));
    FILE *input_file = fopen("sample_input.txt", "r");
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

    /* run the algorithm */
    int distances[graph->N][graph->N];
    for (int u = 0; u < graph->N; u++) {
        for (int v = 0; v < graph->N; v++) {
            if (u == v) {
                distances[u][u] = 0;  // assume that weight of edge to self is 0, this should be what the input file has
            } else {
                distances[u][v] = graph->adjacency_matrix[u][v];
            }
        }
    }

    for (int k = 0; k < graph->N; k++) {
        for (int i = 0; i < graph->N; i++) {
            for (int j = 0; j < graph->N; j++) {
                if (distances[i][j] > distances[i][k] + distances[k][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }

    /* output a txt file that contains the answer */
    remove("sample_output.txt");
    FILE *output_file = fopen("sample_output.txt", "a");
    if (output_file == NULL) {
        printf("Error opening output file");
        exit(1);
    }

    for (int u = 0; u < graph->N; u++) {
        char output_row_weights[MAX_LINE_LENGTH] = "";

        for (int v = 0; v < graph->N; v++) {
            if (distances[u][v] == INFINITY) {
                strncat(output_row_weights, "i ", MAX_STRING_LENGTH);
            } else {
                char buffer[MAX_INT_LENGTH];
                sprintf(buffer, "%d ", distances[u][v]);
                strncat(output_row_weights, buffer, MAX_STRING_LENGTH);
            }
        }
        fputs(output_row_weights, output_file);
        fputs("\n", output_file);
    }
    fclose(output_file);

    return 0;
}