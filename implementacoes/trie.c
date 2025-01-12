#include "../cabecalhos/trie.h"
#include <stdio.h>
#include <stdlib.h>
#define ALFABETO 26

Trie* criarTrie() {
    Trie* novaTrie = (Trie*)malloc(sizeof(Trie)); // aloca dinamicamente de acordo com o tamanho

    if (novaTrie) { 
        novaTrie->final_palavra = false;
        for (int i = 0; i < ALFABETO; i++) {
            novaTrie->letras[i] = NULL;
        }
    }

    return novaTrie;
}

void inserirTrie(Trie* raiz, const char* palavra) {
    if(raiz == NULL || palavra == NULL) {
        printf("Trie ou palavra sem valor\n");
        return;
    }

    // lógica implementada a partir do tries.c do sigaa
    Trie* atual = raiz;

    for(int i = 0; palavra[i] != '\0'; i++){
        int indice = palavra[i] - 'a';

        if(atual->letras[indice] == NULL)
        atual->letras[indice] = criarTrie();

        atual = atual->letras[indice];
  }
  
    atual->final_palavra = true;
}

bool buscarPalavra(Trie* raiz, const char* palavra) {
    Trie* atual = raiz;

    for(int i = 0; palavra[i] != '\0'; i++){
     int indice = palavra[i] - 'a';
        if(atual->letras[indice] == NULL)
            return false;

        atual = atual->letras[indice];
  }

    return atual->final_palavra;
}

void imprimirTrie(Trie* raiz) {
    for (int i = 0; i < ALFABETO; i++) {
        if (raiz->letras[i]) {
            printf("%c ", i + 'a');
            imprimirTrie(raiz->letras[i]);
        }
    }
}

void liberarTrie(Trie* raiz) {
    if (raiz == NULL) {
        return;
    }
    for (int i = 0; i < ALFABETO; i++) {
        liberarTrie(raiz->letras[i]);
    }
    free(raiz);
}

