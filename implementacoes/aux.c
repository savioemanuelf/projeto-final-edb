#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include "../cabecalhos/aux.h"

void limparTerminal() {
    #ifdef WIN_32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirMenu() {
    limparTerminal();
    printf ("******************************************");
    printf ("\n**                 MENU                 **");
    printf ("\n******************************************\n");
    printf("1. Resolver caça palavras\n");
    printf("2. Inserir palavra a ser buscada\n");
    printf("3. Exibir tabuleiro\n");
    printf("4. Exibir lista de palavras\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

void opcaoSelecionada(int opcao) {
    limparTerminal();
    printf ("******************************************\n");
    printf ("**          OPCAO SELECIONADA: %d        **\n", opcao);
    printf ("******************************************\n");   
}

void exibirPalavras() {
    FILE *arquivo = fopen("palavras.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de palavras\n");
        return;
    }

    char linha[1024];
    
    printf("\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

void adicionarPalavra() {
    char palavra[30];

    printf("Digite a palavra que deseja adicionar na busca: ");

    scanf(" %s", palavra);

    FILE *arquivo = fopen("palavras.txt", "a");
    
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo de palavras\n");
    }

    fprintf(arquivo, " %s", palavra);
    fclose(arquivo);
    printf("Palavra %s inserida com sucesso!", palavra);
    sleep(1.5);
}

void exibirTabuleiro() {
    FILE *arquivo = fopen("tabuleiro.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[1024];
    
    printf("\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}