#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cabecalhos/aux.h"
#include "cabecalhos/jogo.h"

int main() {
    Trie* trie = criarTrie();
    ArvAVL* avl = NULL;

    int opcao = 0;

    while (opcao != 7){
        printf("\n\nPressione enter para limpar o terminal e ver o menu: \n");
        getchar();
        exibirMenu();
        scanf(" %d", &opcao);
    
    
        switch (opcao) {
            case 1:
                opcaoSelecionada(1);
                lerTabuleiro("tabuleiro.txt");
                carregarPalavrasTrie("palavras.txt", trie); 
                buscarPalavras(trie, &avl);
                imprimirResultados(avl);
                getchar();
                
                break;
            case 2:
                opcaoSelecionada(2);
                adicionarPalavra();
                break;
            case 3:
                opcaoSelecionada(3);
                exibirTabuleiro();
                getchar();
                break;
            case 4:
                opcaoSelecionada(4);
                exibirPalavras();
                getchar();
                break;
            case 5:
                opcaoSelecionada(5);
                char palavra[30];
                printf("\nDigite a palavra que deseja remover da AVL: ");
                scanf(" %s", palavra);
                
                avl = removerPalavraAVL(avl, palavra);
                
                imprimirArvOrdem(avl);  

                getchar();
                break;
            case 6:
                opcaoSelecionada(6);
                imprimirArvOrdem(avl);
                getchar();
                break;
            case 7:
                liberarArvore(avl);
                liberarTrie(trie);
                
                printf("Saindo do programa...");
                sleep(1.5);
                break;
            default:
                printf("Opcao invalida. Tente novamente");
                getchar();
                break;
        }
    }
    
    return 0;
}