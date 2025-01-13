#include "../cabecalhos/trie.h"
#include <stdio.h>
#include <stdlib.h>
#define ALFABETO 26

Trie* criarTrie() {
    Trie* novaTrie = (Trie*)malloc(sizeof(Trie));

    if (novaTrie) { 
        novaTrie->final_palavra = false;
        for (int i = 0; i < ALFABETO; i++) {
            novaTrie->letras[i] = NULL;
        }
    } else {
        printf("Erro ao alocar memória para a Trie\n");
        return NULL; 
    }

    return novaTrie;
}

void carregarPalavrasTrie(const char *arquivoParametro, Trie *raiz) {
    FILE *arquivo = fopen(arquivoParametro, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir lista de palavras\n");
        return;
    }
     
    char palavra[30];
    while (fgets(palavra, sizeof(palavra), arquivo)) {
        palavra[strcspn(palavra, "\n")] = '\0'; 
        inserirPalavraTrie(raiz, palavra);
    }

    fclose(arquivo);
}



// void inserirPalavraTrie(Trie* raiz, const char* palavra) {
//     if(raiz == NULL || palavra == NULL) {
//         printf("Trie ou palavra sem valor\n");
//         return;
//     }

//     // lógica implementada a partir do tries.c do sigaa
//     Trie* atual = raiz;

//     for(int i = 0; palavra[i] != '\0'; i++){
//         int indice = palavra[i] - 'a';
//         if (indice < 0 || indice >= ALFABETO) {
//             printf("Caractere inválido na palavra: %c\n", palavra[i]);
//             return;
//         }
//         if(atual->letras[indice] == NULL)
//         atual->letras[indice] = criarTrie();

//         atual = atual->letras[indice];
//   }
  
//     atual->final_palavra = true;
// }

void inserirPalavraTrie(Trie* raiz, const char* palavra) {
    Trie* atual = raiz;

    while (*palavra) {
        int indice = *palavra - 'a';
        if (atual->letras[indice] == NULL) {
            atual->letras[indice] = criarTrie();
        }

        atual = atual->letras[indice];
        palavra++;
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

void liberarTrie(Trie* raiz) {
    if (raiz == NULL) return;
    for (int i = 0; i < ALFABETO; i++) {
        liberarTrie(raiz->letras[i]);
    }
    free(raiz);
}
