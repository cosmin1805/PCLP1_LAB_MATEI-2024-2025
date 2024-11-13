#include <stdio.h>
#include <stdlib.h>

int main() {
	// Demonstrating malloc
	int *arr1 = (int *)malloc(5 * sizeof(int));
	if (arr1 == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}

	for (int i = 0; i < 5; i++) {
		arr1[i] = i + 1;
	}

	printf("Array allocated with malloc: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr1[i]);
	}
	printf("\n");

	// Deliberate segmentation fault
	// printf("Accessing out of bounds memory to cause segmentation fault: %d\n",
	//	   arr1[100000]);

	// Demonstrating calloc
	int *arr2 = (int *)calloc(5, sizeof(int));
	if (arr2 == NULL) {
		printf("Memory allocation failed\n");
		free(arr1);
		return 1;
	}

	printf("Array allocated with calloc: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr2[i]);
	}
	printf("\n");

	// Demonstrating realloc
	int *arr3 = (int *)realloc(arr1, 10 * sizeof(int));
	if (arr3 == NULL) {
		printf("Memory reallocation failed\n");
		free(arr1);
		free(arr2);
		return 1;
	}
	for (int i = 5; i < 10; i++) {
		arr3[i] = i + 1;
	}

	printf("Array after realloc: ");
	for (int i = 0; i < 10; i++) {
		printf("%d ", arr3[i]);
	}
	printf("\n");

	// Free allocated memory
	free(arr2);
	free(arr3);

	return 0;
}