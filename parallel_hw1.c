#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 10000000
#define MAX_LINE_LENGTH 1000

int main() {
    printf("Running Script...\n");

    /* make adjacency matrix from reading in input */
    FILE *input_file = fopen("sample_input.txt", "r");
    char line[MAX_LINE_LENGTH];

    fgets(line, MAX_LINE_LENGTH, input_file);  // reads the first line of the file
    int N = line[0] - '0';                     // cast char to int

    int *adjacency_matrix[N];  // should be N x N to begin with

    for (int i = 0; i < N; i++) {
        // read the line, turn it into an int array
        // int row_array[N];  // I had just this previously, but it didn't work. why?
        int *row_array = malloc(sizeof(int) * N);  // is the reason that the above not work because row_array variable gets deallocated thus I'm pointing towards nothing?
        fgets(line, MAX_LINE_LENGTH, input_file);

        printf("line: %s\n", line);

        char delimeter[] = " ";
        int row_array_idx = 0;
        char *ptr = strtok(line, delimeter);
        while (ptr != NULL) {
            if (ptr[0] == 'i') {
                row_array[row_array_idx] = INFINITY;
            } else {
                row_array[row_array_idx] = atoi(ptr);  // convert the ptr str to an int
            }
            ptr = strtok(NULL, delimeter);
            row_array_idx += 1;
        }
        adjacency_matrix[i] = row_array;
    }
    printf("adjacency_matrix[0][0]: %d\n", adjacency_matrix[0][0]);
    printf("adjacency_matrix[0][1]: %d\n", adjacency_matrix[0][1]);
    printf("adjacency_matrix[0][2]: %d\n", adjacency_matrix[0][2]);
    printf("adjacency_matrix[1][0]: %d\n", adjacency_matrix[1][0]);
    printf("adjacency_matrix[1][1]: %d\n", adjacency_matrix[1][1]);
    printf("adjacency_matrix[1][2]: %d\n", adjacency_matrix[1][2]);
    printf("adjacency_matrix[2][0]: %d\n", adjacency_matrix[2][0]);
    printf("adjacency_matrix[2][1]: %d\n", adjacency_matrix[2][1]);
    printf("adjacency_matrix[2][2]: %d\n", adjacency_matrix[2][2]);

    /* run the algorithm */
    int distances[N][N];
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            if (u == v) {
                distances[u][u] = 0;  // assume that weight of edge to self is 0, this should be what the input file has
            } else {
                distances[u][v] = adjacency_matrix[u][v];
                // printf("adjacency_matrix[u][v]: %d\n", adjacency_matrix[u][v]);
                // printf("distances[u][v]: %d\n", distances[u][v]);
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
        // how much space do I need to allocate here? Print neg numbers, print inf?
        char *str_to_write = malloc(sizeof(char) * (N + 1));
        // char str_to_write[N + 1];

        for (int v = 0; v < N; v++) {
            // printf("distances[u][v]: %d\n", distances[u][v]);
            str_to_write[v] = distances[u][v] + '0';  // distances is an int, convert to char
        }
        str_to_write[N + 1] = '\0';
        printf("str_to_write: %s\n", str_to_write);
        fputs(str_to_write, output_file);
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