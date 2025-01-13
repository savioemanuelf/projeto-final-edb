#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../cabecalhos/jogo.h"
#include "../cabecalhos/avl.h"
#include "../cabecalhos/trie.h"

char tabuleiro[MAX][MAX];
int numeroLinhas, numeroColunas;

void lerTabuleiro(const char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    } else {
        fscanf(file, "%d %d", &numeroLinhas, &numeroColunas);
        printf("Dimensões do tabuleiro: %d x %d\n", numeroLinhas, numeroColunas);
        for (int i = 0; i < numeroLinhas; i++) {
            for (int j = 0; j < numeroColunas; j++) {
                fscanf(file, " %c", &tabuleiro[i][j]);
                tabuleiro[i][j] = tolower(tabuleiro[i][j]);
            }
        }
    }

    fclose(file);
}

// void lerPalavras(const char *arquivoParametro, Trie *raiz) {
//     FILE *arquivo = fopen(arquivoParametro, "r");
//     if (arquivo == NULL) {
//         printf("Erro ao abrir lista de palavras\n");
//         return;
//     }
     
//     char palavra[30];
//     while (fgets(palavra, sizeof(palavra), arquivo)) {
//         palavra[strcspn(palavra, "\n")] = '\0'; 
//         inserirTrie(raiz, palavra);
//     }

//     fclose(arquivo);
// }

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

// void buscarPalavras(Trie *trie, ArvAVL **avl) {
 
//     // horizontal
//     buscarDirecao(trie, avl, 0, 1);  // esquerda->direita
//     buscarDirecao(trie, avl, 0, -1); // direita->esquerda

//     // vertical
//     buscarDirecao(trie, avl, 1, 0);  // cima->baixo
//     buscarDirecao(trie, avl, -1, 0); // baixo->cima

//     // diagonal
//     buscarDirecao(trie, avl, 1, 1);   // esquerdaCima->direitaBaixo
//     buscarDirecao(trie, avl, 1, -1);  // direitaCima->esquerdaBaixo
//     buscarDirecao(trie, avl, -1, 1);  // esquerdaBaixo->direitaCima
//     buscarDirecao(trie, avl, -1, -1); // direitaBaixo0>esquerdaCima

// }

void buscarPalavras(Trie *trie, ArvAVL **avl) {
    char palavra[50];

    // horizontal esquerda direita
    for (int i = 0; i < numeroLinhas; i++) {
        for (int j = 0; j < numeroColunas; j++) {
            for (int k = j; k < numeroLinhas; k++) {
                strncpy(palavra, &tabuleiro[i][j], k - j + 1);
                palavra[k - j + 1] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
            }
        }
    }

    // horizontal direita esquerda

    for (int i = 0; i < numeroLinhas; i++) {
        for (int j = numeroColunas - 1; j >= 0; j--) {
            int len = 0;
            for (int k = j; k >= 0; k--) {
                palavra[len++] = tabuleiro[i][k];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
            }
        }
    }

    // vertical cima baixo

    for (int i = 0; i < numeroLinhas; i++) {
        for (int j = 0; j < numeroColunas; j++) {
            for (int k = j; k < numeroColunas; k++) {
                int len = k - j + 1;
                for (int n = 0; n < len; n++) {
                    palavra[n] = tabuleiro[j + n][i];
                }
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
            }
        }
    }

    // vertical baixo cima

    for (int i = 0; i < numeroLinhas; i++) {
        for (int j = numeroColunas - 1; j >= 0; j--) {
            int len = 0;
            for (int k = j; k >= 0; k--) {
                palavra[len++] = tabuleiro[k][i];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
            }
        }
    }

    // diagonal superior esquerda inferior direita

    for (int i = 0; i < numeroLinhas; i++) {
        for (int j = 0; j < numeroColunas; j++) {
            int x = i, y = j, len = 0;
            while (x < numeroLinhas && y < numeroColunas) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
                x++;
                y++;
            }
        }
    }

    // diagonal superior direita inferior esquerda

    for (int i = 0; i < numeroLinhas; i++) {
        for (int j = 0; j < numeroColunas; j++) {
            int x = i, y = j, len = 0;
            while (x < numeroLinhas && y >= 0) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
                x++;
                y--;
            }
        }
    }

    // diagonal inferior esquerda superior direita

    for (int i = numeroLinhas; i >= 0; i--) {
        for (int j = 0; j < numeroColunas; j++) {
            int x = i, y = j, len = 0;
            while (x >= 0 && y < numeroColunas) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
                x--;
                y++;
            }
        }
    }

    // diagonal inferior direita superior esquerda

    for (int i = numeroLinhas - 1; i >= 0; i--) {
        for (int j = numeroColunas - 1; j >= 0; j--) {
            int x = i, y = j, len = 0;
            while (x >= 0 && y >= 0) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirPalavraAVL(*avl, palavra);
                }
                x--;
                y--;
            }
        }
    }
}

void imprimirResultados(ArvAVL *avl) {
    printf("Palavras encontradas:\n");
    imprimirArvOrdem(avl);
}
