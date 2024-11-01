#include <stdio.h>

#define N 100

// Funcție pentru a verifica dacă un număr este putere a lui doi
int is_power_of_two(int x) {
    return x && !(x & (x - 1));
}

// Funcție pentru a calcula produsul tuturor puterilor lui doi din vector,
// excluzând elementul curent
void product_of_powers_of_two(int v[N], int n, int result[N]) {
    int i, j;

    // Iterează prin fiecare element al vectorului
    for (i = 0; i < n; i++) {
        result[i] = 1; // Inițializează rezultatul pentru elementul curent cu 1

        // Iterează din nou prin vector pentru a găsi puteri ale lui doi
        for (j = 0; j < n; j++) {
            // Verifică dacă elementul curent nu este același cu elementul din
            // bucla cu i și dacă este putere a lui doi
            if (i != j && is_power_of_two(v[j])) {
                result[i] *= v[j]; // Înmulțește rezultatul cu numarul de pe pozitia `j`
            }
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
    int result[N];

    print_vector(v, 16);
    product_of_powers_of_two(v, 16, result);
    print_vector(v, 16);

    return 0;
}
