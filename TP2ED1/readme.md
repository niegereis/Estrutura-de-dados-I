# Ajudando o rato a sair do labirinto

Este trabalho foi desenvolvido para aprofundar no conhecimento
das estruturas de dados pilha e fila, e também para aprofundar
no conhecimento de recursividade.


## Dependências
Esse programa foi desenvolvido em C e utiliza a biblioteca Allegro 5.2.

```bash
sudo add-apt-repository ppa:allegro/5.2
sudo apt update
sudo apt-get install liballegro\*5.2 liballegro\*5-dev
```

## Como compilar

Para compilar o programa, basta executar o comando `make` no terminal. Então será gerado um arquivo executável `./exe` caso queira ver a execução com a UI utilize `./exe ui`.


Para executar o programa, basta executar o comando no terminal.
```bash
./exe X Y
*******
*M* * *
* * * *
*      
*******
```
Sendo X e Y a quantidade de linhas e colunas respectivamente do labirinto.