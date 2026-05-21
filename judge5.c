//Ana Beatriz Gualti Scalabrini 168706

#include <stdio.h>
#include <stdlib.h>

// estrutura do no da arvore
typedef struct no_arvore {
    int valor;
    int peso;
    struct no_arvore *esq;
    struct no_arvore *dir;
} no;

// prototipos das funcoes
int pega_peso(no *n);
void atualiza_peso(no *n);
no* cria_no(int valor);
no* rotacao_dir(no *raiz_atual);
no* rotacao_esq(no *raiz_atual);
no* balanceia(no *n);
no* insere(no *raiz, int valor);
no* busca_maior(no *raiz);
no* remove_no(no *raiz, int valor);
void imprime_raiz(no *raiz);
void busca_intervalo(no *raiz, int x, int y, int *primeiro);

// retorna o peso do no ou zero se for nulo
int pega_peso(no *n) {
    if (n == NULL) return 0;
    return n->peso;
}

// atualiza o peso somando os filhos
void atualiza_peso(no *n) {
    if (n != NULL) {
        n->peso = 1 + pega_peso(n->esq) + pega_peso(n->dir);
    }
}

no* cria_no(int valor) {
    no *novo = (no*)malloc(sizeof(no));
    novo->valor = valor;
    novo->peso = 1; // folha sempre comeca com peso 1
    novo->esq = novo->dir = NULL;
    return novo;
}

// rotacao simples a direita ll
no* rotacao_dir(no *raiz_atual) {
    no *nova_raiz = raiz_atual->esq;
    no *aux = nova_raiz->dir;

    nova_raiz->dir = raiz_atual;
    raiz_atual->esq = aux;

    atualiza_peso(raiz_atual);
    atualiza_peso(nova_raiz);

    return nova_raiz;
}

// rotacao simples a esquerda rr
no* rotacao_esq(no *raiz_atual) {
    no *nova_raiz = raiz_atual->dir;
    no *aux = nova_raiz->esq;

    nova_raiz->esq = raiz_atual;
    raiz_atual->dir = aux;

    atualiza_peso(raiz_atual);
    atualiza_peso(nova_raiz);

    return nova_raiz;
}

// funcao para balancear seguindo a regra do dobro
no* balanceia(no *n) {
    if (n == NULL) return n;

    atualiza_peso(n);

    int peso_e = pega_peso(n->esq);
    int peso_d = pega_peso(n->dir);

    // checa se desbalanceou para a esquerda
    if ((peso_e + 1) > 2 * (peso_d + 1)) {
        if (pega_peso(n->esq->dir) > pega_peso(n->esq->esq)) {
            // rotacao dupla lr
            n->esq = rotacao_esq(n->esq);
        }
        return rotacao_dir(n);
    } 
    // checa se desbalanceou para a direita
    else if ((peso_d + 1) > 2 * (peso_e + 1)) {
        if (pega_peso(n->dir->esq) > pega_peso(n->dir->dir)) {
            // rotacao dupla rl
            n->dir = rotacao_dir(n->dir);
        }
        return rotacao_esq(n);
    }

    return n;
}

no* insere(no *raiz, int valor) {
    if (raiz == NULL) return cria_no(valor);

    if (valor < raiz->valor)
        raiz->esq = insere(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = insere(raiz->dir, valor);
    else
        return raiz; // ignora valores repetidos

    return balanceia(raiz);
}

no* busca_maior(no *raiz) {
    no *atual = raiz;
    while (atual->dir != NULL)
        atual = atual->dir;
    return atual;
}

no* remove_no(no *raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor) {
        raiz->esq = remove_no(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remove_no(raiz->dir, valor);
    } else {
        // achou o no para remover
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            no *aux = raiz->esq ? raiz->esq : raiz->dir;
            if (aux == NULL) {
                aux = raiz;
                raiz = NULL;
            } else {
                *raiz = *aux;
            }
            free(aux);
        } else {
            // tem dois filhos entao pega o maior da esquerda
            no *aux = busca_maior(raiz->esq);
            raiz->valor = aux->valor;
            raiz->esq = remove_no(raiz->esq, aux->valor);
        }
    }

    if (raiz == NULL) return raiz;

    return balanceia(raiz);
}

void imprime_raiz(no *raiz) {
    if (raiz == NULL) {
        printf("ARVORE VAZIA\n");
    } else {
        printf("%d,%d,%d\n", pega_peso(raiz), pega_peso(raiz->esq), pega_peso(raiz->dir));
    }
}

// busca no intervalo
void busca_intervalo(no *raiz, int inicio, int fim, int *primeiro) {
    if (raiz == NULL) return;

    if (raiz->valor > inicio) busca_intervalo(raiz->esq, inicio, fim, primeiro);

    if (raiz->valor >= inicio && raiz->valor <= fim) {
        if (!(*primeiro)) printf(", ");
        printf("%d", raiz->valor);
        *primeiro = 0;
    }

    if (raiz->valor < fim) busca_intervalo(raiz->dir, inicio, fim, primeiro);
}

int main() {
    no *raiz = NULL;
    int valor, inicio, fim;

    // lendo e inserindo valores
    while (scanf("%d", &valor) && valor != -1) {
        raiz = insere(raiz, valor);
    }
    imprime_raiz(raiz);

    // lendo e removendo valores
    while (scanf("%d", &valor) && valor != -1) {
        raiz = remove_no(raiz, valor);
    }
    imprime_raiz(raiz);

    // lendo intervalo de busca
    if (scanf("%d %d", &inicio, &fim) == 2) {
        int primeiro = 1;
        busca_intervalo(raiz, inicio, fim, &primeiro);
        if (primeiro) printf("NADA A EXIBIR");
        printf("\n");
    }

    return 0;
}