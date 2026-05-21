/*
descricao: algoritmo merge sort modificado para contar quedas drasticas (inversoes) no vetor
disciplina: algoritmos e estruturas de dados 2 - unifesp
*/

#include <stdio.h>
#include <stdlib.h>

long long int merge_e_cont(long long int vet[], int left, int mid, int right) {
    long long int cont = 0;
    int i, j, k;

    // contagem das quedas drasticas
    j = mid + 1;
    for (i = left; i <= mid; i++) {
        while (j <= right && vet[i] > 2LL * vet[j]) {
            j++;
        }
        // elementos na metade dir
        cont += (j - (mid + 1));
    }

    int n1 = mid - left + 1;
    int n2 = right - mid;

    // subvetores temporarios
    long long int *L = (long long int *)malloc(n1 * sizeof(long long int));
    long long int *R = (long long int *)malloc(n2 * sizeof(long long int));

    for (i = 0; i < n1; i++)
        L[i] = vet[left + i];
    for (j = 0; j < n2; j++)
        R[j] = vet[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    // de volta no vetor original em ordem crescente
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vet[k++] = L[i++];
        } else {
            vet[k++] = R[j++];
        }
    }

    // elementos restantes da metade esq
    while (i < n1) {
        vet[k++] = L[i++];
    }

    // elementos restantes da metade dir
    while (j < n2) {
        vet[k++] = R[j++];
    }

    free(L);
    free(R);

    return cont;
}

long long int mergesort_e_cont(long long int vet[], int left, int right) {
    long long int cont = 0;
    
    if (left < right) {
        int mid = left + (right - left) / 2;

        // cont na metade esq
        cont += mergesort_e_cont
    (vet, left, mid);
        
        // cont na metade dir
        cont += mergesort_e_cont
    (vet, mid + 1, right);
        
        // cont de elementos que cruzam as metades e intec
        cont += merge_e_cont(vet, left, mid, right);
    }
    
    return cont;
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) return 1;

    long long int *vet = (long long int *)malloc(n * sizeof(long long int));
    if (vet == NULL) return 1;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &vet[i]);
    }

    long long int total_drops = mergesort_e_cont(vet, 0, n - 1);

    printf("%lld\n", total_drops);

    for (int i = 0; i < n; i++) {
        printf("%lld", vet[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(vet);
    return 0;
}
