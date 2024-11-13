#include <stdio.h>
#include <stdlib.h>

int main() {
    int vector[5] = {10, 20, 30, 40, 50};
    int *ptr;

    // Point to the first element of the vector
    ptr = vector;

    // Print the vector elements using the pointer
    printf("Vector elements using pointer:\n");
    for (int i = 0; i < 5; i++) {
        printf("vector[%d] = %d\n", i, *(ptr + i));
    }

    // Modify the vector elements using the pointer
    for (int i = 0; i < 5; i++) {
        *(ptr + i) += 10;
    }

    // Print the modified vector elements
    printf("\nModified vector elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("vector[%d] = %d\n", i, vector[i]);
    }

    // Print the modified vector elements
    printf("\nModified vector elements using a wierd way:\n");
    for (int i = 0; i < 5; i++) {
        printf("vector[%d] = %d\n", i, i[vector]); // same as *(i + vector)
    }

    return 0;
}