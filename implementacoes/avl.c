#include "../cabecalhos/avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maior(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int altura(ArvAVL *no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

int fatorBalanceamento(ArvAVL *no) {
    if (no == NULL) {
        return 0;
    } else {
        return altura(no->esquerdo) - altura(no->direito);
    }

}

ArvAVL *criarArvAVL(const char *palavra) {
    ArvAVL *novo = (ArvAVL *)malloc(sizeof(ArvAVL));
    strcpy(novo->palavra, palavra);
    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->altura = 0;
    
    return novo;
}

ArvAVL *rotacaoDireita(ArvAVL *no) {
    ArvAVL *aux = no->esquerdo;
    ArvAVL *aux2 = aux->direito;

    aux->direito = no;
    no->esquerdo = aux2;

    no->altura = 1 + maior(altura(no->esquerdo), altura(no->direito));
    aux->altura = 1 + maior(altura(aux->esquerdo), altura(aux->direito));
    return aux;
}

ArvAVL *rotacaoEsquerda(ArvAVL *no) {
    ArvAVL *aux1 = no->direito;
    ArvAVL *aux2 = aux1->esquerdo;

    aux1->esquerdo = no;
    no->direito = aux2;

    no->altura = 1 + maior(altura(no->esquerdo), altura(no->direito));
    aux1->altura = 1 + maior(altura(aux1->esquerdo), altura(aux1->direito));
    return aux1;
}

ArvAVL *balancearNo(ArvAVL *no) {
    int balanceamento = fatorBalanceamento(no);

    // rotação simples direito
    if (balanceamento > 1 && fatorBalanceamento(no->esquerdo) >= 0) {
        return rotacaoDireita(no);
    }
    // rotação dupla direito
    if (balanceamento > 1 && fatorBalanceamento(no->esquerdo) < 0) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo);

        return rotacaoDireita(no);
    }

    // rotação simples esquerdo
    if (balanceamento < -1 && fatorBalanceamento(no->direito) <= 0) {
        return rotacaoEsquerda(no);
    }

    // rotação dupla esquerdo
    if (balanceamento < -1 && fatorBalanceamento(no->direito) > 0) {
        no->direito = rotacaoDireita(no->direito);

        return rotacaoEsquerda(no);
    }

    return no;
}

ArvAVL *inserirAVL(ArvAVL *raiz, const char *palavra) {
    if (raiz == NULL) {
        return criarArvAVL(palavra);
    }
    if (strcmp(palavra, raiz->palavra) < 0) {
        raiz->esquerdo = inserirAVL(raiz->esquerdo, palavra);
    } else if (strcmp(palavra, raiz->palavra) > 0) {
        raiz->direito = inserirAVL(raiz->direito, palavra);
    } else {
        return raiz;
    }
    raiz->altura = 1 + maior(altura(raiz->esquerdo), altura(raiz->direito));
    return balancearNo(raiz);
}

void imprimirArvOrdem(ArvAVL *raiz) {
    if (raiz != NULL) {
        imprimirArvOrdem(raiz->esquerdo);
        printf("%s\n", raiz->palavra);
        imprimirArvOrdem(raiz->direito);
    }
}

void liberarArvore(ArvAVL *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerdo);
        liberarArvore(raiz->direito);
        free(raiz);
    }
}