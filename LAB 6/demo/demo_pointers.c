#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 10;
	int *p = &a;
	int **pp = &p;

	printf("a = %d\n", a);
	printf("p = %p\n", p);
	printf("*p = %d\n", *p);
	printf("pp = %p\n", pp);
	printf("*pp = %p\n", *pp);
	printf("**pp = %d\n", **pp);

	// Size of pointers
	printf("\n\n");
	printf("Size of void *: %lu\n", sizeof(void *));
	printf("Size of int *: %lu\n", sizeof(int *));
	printf("Size of int **: %lu\n", sizeof(int **));
	printf("Size of char *: %lu\n", sizeof(char *));
	printf("Size of char **: %lu\n", sizeof(char **));
	printf("Size of float *: %lu\n", sizeof(float *));
	printf("Size of float **: %lu\n", sizeof(float **));
	printf("Size of double *: %lu\n", sizeof(double *));
	printf("Size of double **: %lu\n", sizeof(double **));

	return 0;
}