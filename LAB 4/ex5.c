#include <stdio.h>
#define N 100

// Funcție care sortează vectorul în ordine descrescătoare folosind algoritmul Bubble Sort
void bubble_sort_desc(int v[N], int n) {
    int temp; // Variabilă temporară pentru a face schimbul de elemente
    
    // Parcurgem vectorul de n ori
    for (int i = 0; i < n - 1; i++) {
        // Parcurgem vectorul până la elementul n-i-1
        for (int j = 0; j < n - i - 1; j++) {
            // Verificăm dacă elementul curent este mai mic decât următorul element
            if (v[j] < v[j + 1]) {
                // Dacă da, facem schimbul de elemente
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Funcție care implementează algoritmul de căutare binară iterativă
int binary_search(int v[N], int n, int x) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Verificăm dacă x este prezent la mijloc
        if (v[mid] == x) {
            return mid;
        }
        
        // Dacă x este mai mare, ignorăm jumătatea stângă
        if (v[mid] < x) {
            right = mid - 1;
        }
        // Dacă x este mai mic, ignorăm jumătatea dreaptă
        else {
            left = mid + 1;
        }
    }
    
    // Dacă ajungem aici, înseamnă că elementul nu este prezent în vector
    return -1;
}

int main(void) {
    int v[N]; // Declarăm un vector de dimensiune N
    int n;    // Variabilă pentru a stoca dimensiunea vectorului
    int x;    // Variabilă pentru a stoca valoarea de căutat
    
    // Cerem utilizatorului să introducă dimensiunea vectorului
    printf("Introduceti dimensiunea vectorului: \n");
    scanf("%d", &n);
    
    // Cerem utilizatorului să introducă elementele vectorului
    printf("Introduceti elementele vectorului: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    
    // Sortăm vectorul în ordine descrescătoare
    bubble_sort_desc(v, n);
    
    // Afișăm vectorul sortat
    printf("Vectorul sortat descrescator este: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    
    // Cerem utilizatorului să introducă valoarea de căutat
    printf("Introduceti valoarea de cautat: \n");
    scanf("%d", &x);
    
    // Verificăm dacă valoarea se găsește în vector folosind căutarea binară
    printf("Rezultat: \n");
    int result = binary_search(v, n, x);
    if (result != -1) {
        printf("Valoarea %d se gaseste in vector la pozitia %d.\n", x, result);
    } else {
        printf("Valoarea %d nu se gaseste in vector.\n", x);
    }
    
    return 0;
}