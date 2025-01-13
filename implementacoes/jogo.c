#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cabecalhos/jogo.h"
#include "../cabecalhos/avl.h"
#include "../cabecalhos/trie.h"

char tabuleiro[MAX][MAX];
int numeroLinhas, numeroColunas;

void lerTabuleiro(const char *arquivoParametro) {
    FILE *arquivo = fopen(arquivoParametro, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o tabuleiro\n");
        return;
    } 
  
    char linha[MAX];
    fscanf(arquivo, "%d %d", &numeroLinhas, &numeroColunas);
    for (int i = 0; i < numeroLinhas; i++) {
        if(fgets(linha, sizeof(linha), arquivo)) {
            for (int j = 0; j < numeroColunas; j++) { // substituir por numeroColunas para permitir tabuleiros nao quadrados
                // linha[j] = tabuleiro[i][j];
                tabuleiro[i][j] = linha[j];
            }
        }
    }

    fclose(arquivo);
}

void buscarDirecao(Trie *trie, ArvAVL **avl, int dx, int dy) {
    char palavra[30];
    for (int i = 0; i < numeroLinhas; i++) {
        for (int j = 0; j < numeroColunas; j++) { // substituir por numeroColunas para permitir tabuleiros nao quadrados
            int x = i, y = j;
            int len = 0;
            while (x >= 0 && x < numeroLinhas && y >= 0 && y < numeroColunas) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
                x += dx;
                y += dy;
            }
        }
    }
}

void buscarPalavras(Trie *trie, ArvAVL **avl) {
 
    // horizontal
    buscarDirecao(trie, avl, 0, 1);  // esquerda->direita
    buscarDirecao(trie, avl, 0, -1); // direita->esquerda

    // vertical
    buscarDirecao(trie, avl, 1, 0);  // cima->baixo
    buscarDirecao(trie, avl, -1, 0); // baixo->cima

    // diagonal
    buscarDirecao(trie, avl, 1, 1);   // esquerdaCima->direitaBaixo
    buscarDirecao(trie, avl, 1, -1);  // direitaCima->esquerdaBaixo
    buscarDirecao(trie, avl, -1, 1);  // esquerdaBaixo->direitaCima
    buscarDirecao(trie, avl, -1, -1); // direitaBaixo0>esquerdaCima

}

void imprimirResultados(ArvAVL *avl) {
    printf("Palavras encontradas:\n");
    imprimirArvOrdem(avl);
}
