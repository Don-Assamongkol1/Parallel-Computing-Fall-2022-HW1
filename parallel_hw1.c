#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 10000000
#define MAX_LINE_LENGTH 100000
#define MAX_INT_LENGTH 1000
#define MAX_STRING_LENGTH 10

typedef struct adj {
    int N;
    int **weights;
} adj_t;

int main() {
    printf("Running Script...\n");

    /* make adjacency matrix from reading in input */
    // adj_t *adjacency_matrix_ = calloc(1, sizeof(adj_t));

    FILE *input_file = fopen("sample_input.txt", "r");
    char line[MAX_LINE_LENGTH];

    fgets(line, MAX_LINE_LENGTH, input_file);  // reads the first line of the file
    int N = line[0] - '0';                     // cast char to int

    int adjacency_matrix[N][N];

    for (int i = 0; i < N; i++) {
        fgets(line, MAX_LINE_LENGTH, input_file);

        char delimeter[] = " ";
        int j = 0;
        char *ptr = strtok(line, delimeter);
        while (ptr != NULL) {
            if (ptr[0] == 'i') {
                adjacency_matrix[i][j] = INFINITY;
            } else {
                adjacency_matrix[i][j] = atoi(ptr);  // convert the ptr str to an int
            }
            ptr = strtok(NULL, delimeter);
            j += 1;
        }
    }

    /* run the algorithm */
    int distances[N][N];
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            if (u == v) {
                distances[u][u] = 0;  // assume that weight of edge to self is 0, this should be what the input file has
            } else {
                distances[u][v] = adjacency_matrix[u][v];
            }
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (distances[i][j] > distances[i][k] + distances[k][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }

    /* output a txt file of the answer */
    remove("sample_output.txt");
    FILE *output_file = fopen("sample_output.txt", "a");
    if (output_file == NULL) {
        printf("Error opening output file");
        exit(1);
    }

    for (int u = 0; u < N; u++) {
        char output_row_weights[MAX_LINE_LENGTH] = "";

        for (int v = 0; v < N; v++) {
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

/*
Additional comments:
int a[10][20] assigns space for 200 int-sized locations
int *b[10] allocates space for 10 pointers. If you then have the pointers point
    to arrays of 20 ints, i.e. arrays that have space for 20 ints, then you have your
    2D array. You can see that in the latter case, you assign 210 memory locations
    instead of 200

*/