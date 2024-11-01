#include <stdio.h>
#define N 100

// Funcție care afișează elementele din vector care sunt mai mari decât indexul lor
void print_elements_greater_than_index(int v[N], int n) {
    // Parcurgem fiecare element din vector
    for (int i = 0; i < n; i++) {
        // Verificăm dacă elementul este mai mare decât indexul său
        if (v[i] > i) {
            // Dacă da, îl afișăm
            printf("%d ", v[i]);
        }
    }
    // Afișăm un newline la final
    printf("\n");
}

int main(void) {
    int v[N]; // Declarăm un vector de dimensiune N
    int n; // Variabilă pentru a stoca dimensiunea vectorului

    // Cerem utilizatorului să introducă dimensiunea vectorului
    printf("Introduceti dimensiunea vectorului: \n");
    scanf("%d", &n);

    // Cerem utilizatorului să introducă elementele vectorului
    printf("Introduceti elementele vectorului: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    // Apelăm funcția pentru a afișa elementele mai mari decât indexul lor
    printf("Rezultat: \n");
    print_elements_greater_than_index(v, n);

    return 0;
}