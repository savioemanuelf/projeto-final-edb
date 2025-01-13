#include "../cabecalhos/avl.h"
#include "../cabecalhos/aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArvAVL *criarArvAVL(const char *palavra) {
    ArvAVL *novo = (ArvAVL *)malloc(sizeof(ArvAVL));
    strcpy(novo->palavra, palavra);
    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->altura = 0;
    
    return novo;
}

int obterAltura(ArvAVL *no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

int calcularFatorBalanceamento(ArvAVL *no) {
    if (no == NULL) {
        return 0;
    } else {
        return obterAltura(no->esquerdo) - obterAltura(no->direito);
    }

}

ArvAVL* rotacaoDireita(ArvAVL* y) {
  ArvAVL* x = y->esquerdo;
  ArvAVL* z = x->direito;

  x->direito = y;
  y->esquerdo = z;

  if(obterAltura(y->esquerdo) > obterAltura(y->direito))
    y->altura = 1 + obterAltura(y->esquerdo);
  else
    y->altura = 1 + obterAltura(y->direito);

  if(obterAltura(x->esquerdo) > obterAltura(x->direito))
    x->altura = 1 + obterAltura(x->esquerdo);
  else
    x->altura = 1 + obterAltura(x->direito);

  return x;
}

ArvAVL* rotacaoEsquerda(ArvAVL* x) {
  ArvAVL* y = x->direito;
  ArvAVL* z = y->esquerdo;

  y->esquerdo = x;
  x->direito = z;

  if(obterAltura(x->esquerdo) > obterAltura(x->direito))
    x->altura = 1 + obterAltura(x->esquerdo);
  else
    x->altura = 1 + obterAltura(x->direito);

  if (obterAltura(y->esquerdo) > obterAltura(y->direito))
    y->altura = 1 + obterAltura(y->esquerdo);
  else
    y->altura = 1 + obterAltura(y->direito);

  return y;
}

ArvAVL *balancear(ArvAVL* no) {
    int balanceamento = calcularFatorBalanceamento(no);

    // rotacao simples direito
    if (balanceamento > 1 && calcularFatorBalanceamento(no->esquerdo) >= 0) {
        return rotacaoDireita(no);
    }
    // rotacao dupla direito
    if (balanceamento > 1 && calcularFatorBalanceamento(no->esquerdo) < 0) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo);

        return rotacaoDireita(no);
    }

    // rotacao simples esquerdo
    if (balanceamento < -1 && calcularFatorBalanceamento(no->direito) <= 0) {
        return rotacaoEsquerda(no);
    }

    // rotacao dupla esquerdo
    if (balanceamento < -1 && calcularFatorBalanceamento(no->direito) > 0) {
        no->direito = rotacaoDireita(no->direito);

        return rotacaoEsquerda(no);
    }

    return no;
}

ArvAVL *inserirPalavraAVL(ArvAVL *raiz, const char *palavra) {
    if (raiz == NULL) {
        return criarArvAVL(palavra);
    }

    if (strcmp(palavra, raiz->palavra) < 0) {
        raiz->esquerdo = inserirPalavraAVL(raiz->esquerdo, palavra);
    } else if (strcmp(palavra, raiz->palavra) > 0) {
        raiz->direito = inserirPalavraAVL(raiz->direito, palavra);
    }

    raiz->altura = 1 + max(obterAltura(raiz->esquerdo), obterAltura(raiz->direito));
    return balancear(raiz);
}

// implementação feita com auxilio do codigo avl.c do sigaa
ArvAVL *removerPalavraAVL(ArvAVL *raiz, const char *palavra) {
    if (raiz == NULL) {
        return raiz;
    }

    // descendo a arvore para encontrar o no de remocao
    if (strcmp(palavra, raiz->palavra) < 0) {
        raiz->esquerdo = removerPalavraAVL(raiz->esquerdo, palavra);
    } else if (strcmp(palavra, raiz->palavra) > 0) {
        raiz->direito = removerPalavraAVL(raiz->direito, palavra);
    } else {
        // Nó com apenas um filho ou nenhum.
        if (raiz->esquerdo == NULL || raiz->direito == NULL) {
            ArvAVL *temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

            // Caso de nenhum filho
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                // Caso de um filho
                *raiz = *temp;
            }
            free(temp);
        } else {
            // Caso de dois filhos: obtém o sucessor
            ArvAVL *temp = raiz->direito;
            while (temp->esquerdo != NULL) {
                temp = temp->esquerdo;
            }

            // Copia o sucessor para o nó a ser removido
            strcpy(raiz->palavra, temp->palavra);

            // Remove o sucessor
            raiz->direito = removerPalavraAVL(raiz->direito, temp->palavra);
        }
    }

    // Se a árvore tinha apenas um nó
    if (raiz == NULL) {
        return raiz;
    }

    // Atualiza a altura do nó atual
    raiz->altura = 1 + max(obterAltura(raiz->esquerdo), obterAltura(raiz->direito));

    // Balanceia a árvore, se necessário
    int balanceamento = calcularFatorBalanceamento(raiz);

    // Caso 1: Desbalanceamento a esquerda (rotacao a direita)
    if (balanceamento > 1 && calcularFatorBalanceamento(raiz->esquerdo) >= 0) {
        return rotacaoDireita(raiz);
    }

    // Caso 2: Desbalanceamento esquerda-direita (rotacao dupla esquerda-direita)
    if (balanceamento > 1 && calcularFatorBalanceamento(raiz->esquerdo) < 0) {
        raiz->esquerdo = rotacaoEsquerda(raiz->esquerdo);
        return rotacaoDireita(raiz);
    }

    // Caso 3: Desbalanceamento a direita (rotacao a esquerda)
    if (balanceamento < -1 && calcularFatorBalanceamento(raiz->direito) <= 0) {
        return rotacaoEsquerda(raiz);
    }

    // Caso 4: Desbalanceamento direita-esquerda (rotacao dupla direita-esquerda)
    if (balanceamento < -1 && calcularFatorBalanceamento(raiz->direito) > 0) {
        raiz->direito = rotacaoDireita(raiz->direito);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
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