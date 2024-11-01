#include <stdio.h>
#define N 100

// Funcție care calculează media aritmetică a valorilor pare din vector
void calculate_average_of_even_elements(int v[N], int n) {
    int sum = 0; // Inițializăm suma cu 0
    int counter = 0; // Inițializăm counter-ul cu 0

    // Parcurgem fiecare element din vector
    for (int i = 0; i < n; i++) {
        // Verificăm dacă elementul este par
        if (v[i] % 2 == 0) {
            // Dacă da, îl adăugăm la sumă și incrementăm counter-ul
            sum += v[i];
            counter++;
        }
    }

    // Verificăm dacă există elemente pare în vector
    if (counter > 0) {
        // Calculăm și afișăm media aritmetică
        printf("%f\n", (float)sum / counter);
    } else {
        // Afișăm mesajul specific dacă nu există elemente pare
        printf("Niciun element par in vector!\n");
    }
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

    // Calculăm și afișăm media aritmetică a valorilor pare din vector
    printf("Rezultat: \n");
    calculate_average_of_even_elements(v, n);

    return 0;
}

/* EXPLICATIE EXEMPLU
Explicație pentru vectorul: 3 5 4 7 2 4 0
    1.Elementele pare: 4, 2, 4, 0
    2.Suma elementelor pare: 4 + 2 + 4 + 0 = 10
    3.Numărul elementelor pare: 4
    4.Media aritmetică: 10 / 4 = 2.5
Deci, pentru vectorul 3 5 4 7 2 4 0, se va afișa 2.500000.
*/