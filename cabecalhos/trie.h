#ifndef TRIE_H
#include <stdbool.h>
#define TRIE_H
#define ALFABETO 26

typedef struct Trie {
    struct Trie* letras[ALFABETO];
    bool final_palavra;
} Trie;

Trie* criarTrie(); // cria trie
void inserirTrie(Trie* raiz, const char* palavra); // insere palavra na trie
bool buscarPalavra(Trie* raiz, const char* palavra); // busca palavra na trie
void liberarTrie(Trie* raiz); // libera trie
void imprimirTrie(Trie* raiz); // imprime trie 

#endif 