#include <stdio.h>
#include <stdlib.h>

// estrutura para armazenar os dados do paciente
typedef struct {
    int id;
    int gravidade;
} Paciente;

// contador para armazenar o total de trocas efetivas
long long total_trocas = 0;

// funcao que define a prioridade: maior gravidade ou menor id em caso de empate
int tem_prioridade(Paciente a, Paciente b) {
    if (a.gravidade > b.gravidade) return 1;
    if (a.gravidade < b.gravidade) return 0;
    if (a.id < b.id) return 1;
    return 0;
}

// funcao de troca que respeita as travas de seguranca do sistema
void trocar(Paciente *a, Paciente *b, int idx_a, int idx_b) {
    // trava 1: nao troca se os indices forem iguais
    if (idx_a == idx_b) return;
    
    // trava 2: nao troca se o conteudo (id e gravidade) for identico
    if (a->id == b->id && a->gravidade == b->gravidade) return;

    Paciente temporario = *a;
    *a = *b;
    *b = temporario;
    
    // incrementa o contador apenas se a troca for realizada
    total_trocas++;
}

// escolhe o pivo usando a tecnica da mediana de tres
void mediana_de_tres(Paciente arr[], int p, int r) {
    int meio = p + (r - p) / 2;

    if (tem_prioridade(arr[meio], arr[p])) {
        trocar(&arr[meio], &arr[p], meio, p);
    }
    if (tem_prioridade(arr[r], arr[p])) {
        trocar(&arr[r], &arr[p], r, p);
    }
    if (tem_prioridade(arr[r], arr[meio])) {
        trocar(&arr[r], &arr[meio], r, meio);
    }

    // posiciona a mediana no final para servir de pivo
    trocar(&arr[meio], &arr[r], meio, r);
}

// organiza os elementos em torno do pivo
int particao(Paciente arr[], int p, int r) {
    mediana_de_tres(arr, p, r);
    
    Paciente pivo = arr[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (tem_prioridade(arr[j], pivo)) {
            i++;
            trocar(&arr[i], &arr[j], i, j);
        }
    }
    
    trocar(&arr[i + 1], &arr[r], i + 1, r);
    return i + 1;
}

// funcao principal do quicksort
void quicksort(Paciente arr[], int p, int r) {
    if (p < r) {
        int q = particao(arr, p, r);
        quicksort(arr, p, q - 1);
        quicksort(arr, q + 1, r);
    }
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) return 0;

    Paciente *pacientes = (Paciente *)malloc(n * sizeof(Paciente));
    if (pacientes == NULL) return 1;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &pacientes[i].id, &pacientes[i].gravidade);
    }

    quicksort(pacientes, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d\n", pacientes[i].id);
    }

    printf("Swaps: %lld\n", total_trocas);

    free(pacientes);
    return 0;
}