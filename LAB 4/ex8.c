#include <stdio.h>
#define N 100

// Funcție care calculează suma maximă a unei subsecvențe folosind algoritmul lui Kadane
int max_subarray_sum(int v[N], int n) {
    int max_so_far = v[0], max_ending_here = v[0];
    for (int i = 1; i < n; i++) {
        // Dacă suma curentă este negativă, începem o nouă subsecvență
        if (max_ending_here < 0) {
            max_ending_here = v[i];
        } else {
            // Altfel, adăugăm elementul curent la suma curentă
            max_ending_here += v[i];
        }
        // Actualizăm suma maximă dacă suma curentă este mai mare
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
        }
    }
    return max_so_far;
}

int main(void) {
    int v[N], n;
    
    // Citim dimensiunea vectorului de la tastatură
    printf("Introduceti dimensiunea vectorului: \n");
    scanf("%d", &n);
    
    // Citim elementele vectorului de la tastatură
    printf("Introduceti elementele vectorului: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    
    // Calculăm suma maximă a unei subsecvențe
    int max_sum = max_subarray_sum(v, n);
    // Afișăm rezultatul
    printf("Suma maxima a unei subsecvente este: %d\n", max_sum);
    
    return 0;
}