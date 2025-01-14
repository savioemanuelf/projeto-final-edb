# PROJETO FINAL EDB2 - CAÇA-PALAVRAS

## Sobre

O projeto é baseado na implementação de um caça-palavras utilizando os conceitos de estrutura de dados árvore avl e árvores digitais.

## Configuração e execução

### Linux:
**Tendo gcc e makefile configurados, abra o terminal na pasta em que está o repositório e rode o comando:**
```bash
 make
``` 
**dessa forma, todos os arquivos necessários serão compilados automaticamente pelo Makefile.**

### Windows:
**abra o terminal na pasta em que está o repositório e rode o seguintes comandos:**
```bash
    gcc -o programa -Wall -Wextra ./cabecalhos/avl.h ./cabecalhos/jogo.h ./cabecalhos/trie.h ./cabecalhos/aux.h ./implementacoes/aux.c ./implementacoes/avl.c ./implementacoes/jogo.c ./implementacoes/trie.c main.c
```
```bash
    ./programa
```
