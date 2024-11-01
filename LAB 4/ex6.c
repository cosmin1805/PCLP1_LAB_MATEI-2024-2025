#include <stdio.h>
#define N 100

// Funcție care reordonează vectorul astfel încât toate elementele pare să fie înaintea celor impare
void reorder_even_odd(int v[N], int n) {
    int left = 0, right = n - 1;
    
    while (left < right) {
        
        // Găsim primul element impar de la început
        while (left < right && v[left] % 2 == 0) {
            left++;
        }
        
        // Găsim primul element par de la sfârșit
        while (left < right && v[right] % 2 != 0) {
            right--;
        }
        
        // Schimbăm elementele găsite
        if (left < right) {
            int temp = v[left];
            v[left] = v[right];
            v[right] = temp;
            left++;
            right--;
        }
    }
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
    
    // Reordonăm vectorul astfel încât elementele pare să fie înaintea celor impare
    reorder_even_odd(v, n);
    
    // Afișăm vectorul reordonat
    printf("Vectorul reordonat este: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    
    return 0;
}