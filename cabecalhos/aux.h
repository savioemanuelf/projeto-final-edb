#ifndef AUX_H
#define AUX_H

void exibirMenu();
void limparTerminal(); // Limpa terminal com base no sistema operacional
void opcaoSelecionada(int opcao); // Exibe a opcao selecionada após limpar o terminal
void adicionarPalavra(); // Adiciona palavra a ser buscada em palavras.txt
void exibirPalavras(); // Exibe as palavras de palavras.txt
void exibirTabuleiro(); // Exibe o tabuleir de tabuleiro.txt
int max(int x, int y); // função auxiliar para calcular altura da arvore
#endif // AUX_H