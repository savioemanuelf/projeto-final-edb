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


void inserirPalavraTrie(Trie* raiz, const char* palavra) {
    Trie* atual = raiz;

    while (*palavra) {
        if (*palavra < 'a' || *palavra > 'z') {
            printf("Caractere inválido na palavra: %c\n", *palavra);
            return;
        }

        int indice = *palavra - 'a';
        if (atual->letras[indice] == NULL) {
            atual->letras[indice] = criarTrie();
        }

        atual = atual->letras[indice];
        palavra++;
    }

    atual->final_palavra = true;
}

void carregarPalavrasTrie(const char *arquivoParametro, Trie *raiz) {
    FILE *arquivo = fopen(arquivoParametro, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir lista de palavras\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        char *palavra = strtok(linha, " ");
        while (palavra != NULL) {

            // inserir palavra individualmente na Trie
            inserirPalavraTrie(raiz, palavra);

            // próxima palavra, 
            // strtok pesquisado na internet pois enfrentei problemas nessa função
            palavra = strtok(NULL, " ");
        }
    }

    fclose(arquivo);
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
