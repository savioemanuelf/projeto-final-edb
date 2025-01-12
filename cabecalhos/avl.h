#ifndef AVL_H
#define AVL_H
typedef struct ArvAVL {
    char palavra[50];
    int altura;
    struct ArvAVL *esquerdo, *direito;
} ArvAVL;

ArvAVL* criarArvAVL(const char* palavra); // Cria arvore avl
ArvAVL* inserirAVL(ArvAVL* raiz, const char* palavra); // Insere na arvore avl uma palavra
void imprimirArvOrdem(ArvAVL* raiz); // Imprime a arvore em ordem
void liberarArvore(ArvAVL* raiz); // Libera memória da arvore'

#endif // AVL_H