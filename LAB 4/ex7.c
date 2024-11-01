#include <stdio.h>
#define N 100

// Funcție care găsește elementul duplicat din vector
int find_duplicate(int v[N], int n) {
    int sum = 0;
    int expected_sum = (n - 1) * n / 2; // Suma primelor (n-1) numere naturale

    // Calculăm suma elementelor din vector
    for (int i = 0; i < n; i++) {
        sum += v[i];
    }

    return sum - expected_sum; // Diferența va fi numărul duplicat
}

int main(void) {
    int v[N] = {1, 3, 4, 2, 5, 3}; // Vector exemplu cu un duplicat
    int n = 6; // Lungimea vectorului

    // Afișăm elementul duplicat
    printf("Elementul duplicat este: %d\n", find_duplicate(v, n));

    return 0;
}