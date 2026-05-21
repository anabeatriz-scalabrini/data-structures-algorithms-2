/*
descricao: insertion sort em lista duplamente encadeada com contagem de comparacoes (nep)
disciplina: algoritmos e estruturas de dados 2 - unifesp
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//lista duplamente encadeada e criar nó 
typedef struct No {
    int id;
    struct No *ant;
    struct No *prox;
} No;

No* criarNo(int id) {
    No* novo = (No*)malloc(sizeof(No));
    novo->id = id;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

//main
int main() {
    int N, id_novo;
    if (scanf("%d", &N) != 1) return 0;

    No *head = NULL;
    No *tail = NULL;
    int nep = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &id_novo);
        No* novo = criarNo(id_novo);

        // vazio
        if (head == NULL) {
            head = tail = novo;
            continue;
        }

        // inserir no inicio
        if (id_novo <= head->id) {
            novo->prox = head;
            head->ant = novo;
            head = novo;
        }
        // inserir no final
        else if (id_novo >= tail->id) {
            novo->ant = tail;
            tail->prox = novo;
            tail = novo;
        }
        // inserir no meio, conta quantas comparaçoes
        else {
            int d_cabeca = abs(id_novo - head->id);
            int d_final = abs(id_novo - tail->id);
            int nep_atual = 0;

            // conta a partit do começo
            if (d_cabeca <= d_final) {
                No* atual = head;
                // vai para o proximo enquanto o comparado for menor
                while (atual->prox != NULL && atual->prox->id < id_novo) {
                    atual = atual->prox;
                    nep_atual++;
                }
                nep_atual++; 
                
                // insere no lugar encontrado
                novo->prox = atual->prox;
                novo->ant = atual;
                if (atual->prox != NULL) atual->prox->ant = novo;
                atual->prox = novo;
            }
            // conta a partir do final
            else {
                No* atual = tail;
                // vai para o anterior enquanto o comparado for maior
                while (atual->ant != NULL && atual->ant->id > id_novo) {
                    atual = atual->ant;
                    nep_atual++;
                }
                nep_atual++;

                // insere no lugar encontrado
                novo->ant = atual->ant;
                novo->prox = atual;
                if (atual->ant != NULL) atual->ant->prox = novo;
                atual->ant = novo;
            }
            nep += nep_atual;
        }
    }

    // lista final
    No* temp = head;
    while (temp != NULL) {
        printf("%d%c", temp->id, (temp->prox ? ' ' : '\n'));
        No* aux = temp;
        temp = temp->prox;
        free(aux); // Libera memoria
    }

    // NEP
    printf("%d\n", nep);

    return 0;
}
