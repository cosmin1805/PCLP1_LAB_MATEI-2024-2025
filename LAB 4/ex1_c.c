#include <stdio.h>

#define N 100

// Functie pentru a elimina elementul minim din vector
void remove_min(int v[N], int *n) {
    int min_index = 0;

    // Gaseste indexul elementului minim
    for (int i = 1; i < *n; i++) {
        if (v[i] < v[min_index]) {
            min_index = i;
        }
    }

    // Deplaseaza elementele spre stanga pentru a umple golul
    for (int i = min_index; i < *n - 1; i++) {
        v[i] = v[i + 1];
    }

    // Micsoreaza dimensiunea vectorului
    (*n)--;
}

// Functie pentru a elimina elementul maxim din vector
void remove_max(int v[N], int *n) {
    int max_index = 0;

    // Gaseste indexul elementului maxim
    for (int i = 1; i < *n; i++) {
        if (v[i] > v[max_index]) {
            max_index = i;
        }
    }

    // Deplaseaza elementele spre stanga pentru a umple golul
    for (int i = max_index; i < *n - 1; i++) {
        v[i] = v[i + 1];
    }

    // Micsoreaza dimensiunea vectorului
    (*n)--;
}

// functie pentru a afisa vectorul
void print_vector(int v[N], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// Functie pentru a procesa input-ul utilizatorului si a efectua actiuni asupra vectorului
void process_input(int v[N], int *n) {
    char c;

    while (1) {
        // Citeste un caracter de la utilizator
        scanf(" %c", &c);
        switch (c) {
            case 'q':
                // Iesire din bucla
                return;
            case 'm':
                // Elimina elementul minim din vector
                remove_min(v, n);
                break;
            case 'M':
                // Elimina elementul maxim din vector
                remove_max(v, n);
                break;
            case 'p':
                // Afiseaza vectorul
                print_vector(v, *n);
                break;
            default:
                // Afiseaza un mesaj de eroare pentru input invalid
                printf("Input invalid\n");
        }
    }
}

int main(void) {
    int v[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int n = 16;

    process_input(v, &n);

    return 0;
}
