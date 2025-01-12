#ifndef JOGO_H
#define JOGO_H
#define MAX 150
#include "avl.h"
#include "trie.h"

void lerTabuleiro(const char *arquivo); // Lê o tabuleiro a partir de um arquivvo informado
void lerPalavras(const char *arquivo, Trie *raiz); // Lê palavras de um arquivo e insere na arvore trie
void buscarDirecao(Trie *trie, ArvAVL **avl, int dx, int dy); // Função generalista que busca de acordo uma direção informada
void buscarPalavras(Trie *trie, ArvAVL **avl); // Função que busca todas as palavras da arvore trie na arvore avl (arvore com o tabuleiro)
// utilizandio a função generalista
void imprimirResultados(ArvAVL *avl); // imprime as palavras encontradas
#endif // JOGO_H