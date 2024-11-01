#include <math.h> // am inclus math.h pt functia sqrt()
#include <stdio.h>
#define N 100

// Functia modify_vector modifica vectorul v in functie de anumite conditii
void modify_vector(int v[N], int n) {
    int i;

    for (i = 0; i < n; i++) {
        // Daca elementul curent are un vecin in stanga si este par,
        // adaugam valoarea vecinului din stanga la elementul curent
        if (i > 0 && v[i] % 2 == 0) {
            v[i] += v[i - 1];
        }
        // Daca elementul curent are un vecin in dreapta si este impar,
        // adaugam partea intreaga a radicalului vecinului din dreapta la
        // elementul curent
        else if (i < n - 1 && v[i] % 2 != 0) {
            v[i] += (int)sqrt(v[i + 1]);
        }
    }
}

void print_vector(int v[N], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
    int v[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    print_vector(v, 16);
    modify_vector(v, 16);
    print_vector(v, 16);

    return 0;
}
