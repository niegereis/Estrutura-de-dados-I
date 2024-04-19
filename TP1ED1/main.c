#include "labirinto.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    int menorCaminho = INT_MAX;
    srand(time(NULL));

    Labirinto *labirinto = alocarLabirinto();

    if (argc == 2 && strcmp(argv[1], "random") == 0) {
        int linhas, colunas;
        char opcao;
        scanf("%d %d", &linhas, &colunas);
        scanf(" %c", &opcao);
        // time_t inicioGerarLabirinto = time(NULL);
        gerarLabirintoAleatorio(labirinto, linhas, colunas, opcao);
        imprimeLabirinto(labirinto);
        // time_t fimGerarLabirinto = time(NULL);
        // printf("%ld\n", fimGerarLabirinto - inicioGerarLabirinto);
    } else {
        leLabirinto(labirinto);
    }
    Posicao *posicaoRato = encontrarPosicaoDoRato(labirinto);
    Percurso *percursoAtual = alocarPercurso(labirinto);
    Percurso *jaInicouEm = alocarPercurso(labirinto);
    Percurso *menorPercurso = alocarPercurso(labirinto);

    time_t inicioAcharSaida = time(NULL);
    acharSaida(labirinto, posicaoRato, -1, &menorCaminho, menorPercurso, percursoAtual);
    time_t fimAcharSaida = time(NULL);
    printf("%ld\n", fimAcharSaida - inicioAcharSaida);

    if (menorCaminho != INT_MAX) {
        system("\n");
        imprimeSaida(labirinto, menorPercurso);
    } else {
        printf("EPIC FAIL!\n");
    }

    desalocarPosicao(&posicaoRato);

    desalocarPercurso(&percursoAtual);
    desalocarPercurso(&menorPercurso);
    desalocarPercurso(&jaInicouEm);

    desalocarLabirinto(&labirinto);

    return 0;
}
