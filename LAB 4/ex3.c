#include <stdio.h>
#define N 100

void print_elements_with_smaller_neighbors(int v[N], int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            // Primul element, verificăm doar vecinul din dreapta
            if (v[i] > v[i + 1]) {
                printf("%d ", v[i]);
            }
        } else if (i == n - 1) {
            // Ultimul element, verificăm doar vecinul din stânga
            if (v[i] > v[i - 1]) {
                printf("%d ", v[i]);
            }
        } else {
            // Elementele din mijloc, verificăm ambii vecini
            if (v[i] > v[i - 1] && v[i] > v[i + 1]) {
                printf("%d ", v[i]);
            }
        }
    }
    printf("\n");
}

int main(void) {
    int v[N]; // Declarăm un vector de dimensiune N
    int n;    // Variabilă pentru a stoca dimensiunea vectorului

    // Cerem utilizatorului să introducă dimensiunea vectorului
    printf("Introduceti dimensiunea vectorului: \n");
    scanf("%d", &n);

    // Cerem utilizatorului să introducă elementele vectorului
    printf("Introduceti elementele vectorului: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    // Afișăm elementele care au vecinii cu valori mai mici decât ele
    printf("Rezultat: \n");
    print_elements_with_smaller_neighbors(v, n);

    return 0;
}