#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
code to show how declaring an array on the stack as opposed to the heap (done via
calloc) means that this array can be corrupted.
*/

int main() {
    printf("running script...\n");
    int* array_ptr;

    for (int i = 0; i < 3; i++) {
        int row_array[3];
        row_array[0] = i * 10;
        row_array[1] = i * 10;
        row_array[2] = i * 10;
        array_ptr = row_array;

        for (int i = 0; i < 3; i++) {
            printf("array_ptr idx {%d} has value {%d}\n", i, array_ptr[i]);
        }
        printf("\n");
    }

    /* this just devolves to garbage, since the program no longer allocates space
       for the row_array variable */
    for (int i = 0; i < 3; i++) {
        printf("array_ptr idx {%d} has value {%d}\n", i, array_ptr[i]);
    }
}