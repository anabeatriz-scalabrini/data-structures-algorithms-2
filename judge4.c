//Ana Beatriz Gualti Scalabrini 168706

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char texto[21];
    int peso;
} palavra;


int maior_que(palavra a, palavra b) {
    if (a.peso != b.peso) {
        return a.peso > b.peso;
    }
    return strcmp(a.texto, b.texto) > 0;
}

//funcao para manter a propriedade do max-heap
void heapify(palavra *vetor, int n, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && maior_que(vetor[esquerda], vetor[maior])) {
        maior = esquerda;
    }

    if (direita < n && maior_que(vetor[direita], vetor[maior])) {
        maior = direita;
    }

    if (maior != i) {
        palavra temporaria = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temporaria;
        heapify(vetor, n, maior);
    }
}

//max-heap inicial in place
void build_heap(palavra *vetor, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vetor, n, i);
    }
}

// funcao principal do algoritmo heapsort adaptado
void heapsort(palavra *vetor, int n) {
    build_heap(vetor, n);

    // imprimir o estado do heap imediatamente apos a sua construcao inicial
    printf("build_heap:");
    for (int i = 0; i < n; i++) {
        printf(" %s", vetor[i].texto);
    }
    printf("\n");

    // extracao elemento por elemento do heap
    for (int i = n - 1; i >= 1; i--) {
        palavra temporaria = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temporaria;
        heapify(vetor, i, 0);
    }
}

int main() {
    int total_palavras, freq_minima;
    
    if (scanf("%d %d", &total_palavras, &freq_minima) != 2) return 0;

    palavra *vetor = (palavra *)malloc(total_palavras * sizeof(palavra));
    if (!vetor) return 1;

    int freq_global[26] = {0};

    //contagem global de o(n)
    for (int i = 0; i < total_palavras; i++) {
        scanf("%s", vetor[i].texto);
        for (int j = 0; vetor[i].texto[j] != '\0'; j++) {
            freq_global[vetor[i].texto[j] - 'a']++;
        }
    }

    // filtragem realizada in-place
    int qtd_validas = 0; 
    for (int i = 0; i < total_palavras; i++) {
        int eh_valida = 1;
        for (int j = 0; vetor[i].texto[j] != '\0'; j++) {
            if (freq_global[vetor[i].texto[j] - 'a'] < freq_minima) {
                eh_valida = 0;
                break;
            }
        }

        if (!eh_valida) {
            printf("A palavra %s eh invalida (K=%d)\n", vetor[i].texto, freq_minima);
        } else {
            // se valida, calcula a chave de ordenacao (peso)
            int peso_total = 0;
            for (int j = 0; vetor[i].texto[j] != '\0'; j++) {
                peso_total += freq_global[vetor[i].texto[j] - 'a'];
            }
            // reposiciona as palavras validas nas posicoes iniciais do vetor
            vetor[qtd_validas] = vetor[i];
            vetor[qtd_validas].peso = peso_total;
            qtd_validas++;
        }
    }

    if (qtd_validas == 0) {
        printf("Erro: Sem palavras validas para ordenacao.\n");
    } else {
        heapsort(vetor, qtd_validas);

        printf("palavras:");
        for (int i = 0; i < qtd_validas; i++) {
            printf(" %s", vetor[i].texto);
        }
        printf("\n");
    }

    free(vetor);
    
    return 0;
}