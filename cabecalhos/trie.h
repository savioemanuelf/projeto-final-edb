#ifndef TRIE_H
#include <stdbool.h>
#include <string.h>
#define TRIE_H
#define ALFABETO 26

typedef struct Trie {
    struct Trie* letras[ALFABETO];
    bool final_palavra;
} Trie;

Trie* criarTrie(); // cria trie
void inserirPalavraTrie(Trie* raiz, const char* palavra); // insere palavra na trie
void carregarPalavrasTrie(const char *arquivo, Trie *raiz); // Carrega palavras de um arquivo e insere na arvore trie utilizando
// a função inserirPalavraTrie
bool buscarPalavra(Trie* raiz, const char* palavra); // busca palavra na trie
void liberarTrie(Trie *);
void testarBusca(Trie* raiz, const char* palavra);
#endif // TRIE_H