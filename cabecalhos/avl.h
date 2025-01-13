#ifndef AVL_H
#define AVL_H
typedef struct ArvAVL {
    char palavra[50]; // dado da arvore
    int altura;
    struct ArvAVL* esquerdo;
    struct ArvAVL* direito;
}ArvAVL;

ArvAVL* criarArvAVL(const char* palavra); // Cria arvore avl
ArvAVL* inserirPalavraAVL(ArvAVL* raiz, const char* palavra); // Insere na arvore avl uma palavra
ArvAVL* removerPalavraAVL(ArvAVL* raiz, const char* palavra); // Remove palavra na arvore
int obterAltura(ArvAVL *no); // obter altura da arvore
ArvAVL *rotacaoDireita(ArvAVL *no); // rotacionar a direita
ArvAVL *rotacaoEsquerda(ArvAVL *no); // rotacionar a esquerda
int calcularFatorBalanceamento(ArvAVL *no); // calcula fator de balanceamento
ArvAVL *balancear(ArvAVL *no); // função para balancear a arvore
void imprimirArvOrdem(ArvAVL* raiz); // Imprime a arvore em ordem
void liberarArvore(ArvAVL* raiz); // Libera memória da arvore

#endif // AVL_H