#include "labirinto.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEBUG_CRIAR_LABIRINTO true
#define DEBUG_CRIAR_BIFURCACOES false

struct labirinto {
    char **tabuleiro;
    int qtdLinhas;
    int qtdColunas;
    char opcao;
};

struct posicao {
    int x;
    int y;
};

struct percurso {
    Posicao *posicoes;
    int passos;
};

typedef enum { CIMA, BAIXO, ESQUERDA, DIREITA } Direcao;

typedef struct direcoesDisponiveis {
    Direcao *direcoes;
    int qtdDirecoes;
} DirecoesDisponiveis;

Labirinto *alocarLabirinto() {
    Labirinto *labirinto = (Labirinto *)malloc((sizeof(Labirinto)));
    return labirinto;
}

void leLabirinto(Labirinto *labirinto) {
    scanf("%d%d", &labirinto->qtdLinhas, &labirinto->qtdColunas);
    scanf(" %c ", &labirinto->opcao);

    labirinto->tabuleiro = (char **)malloc(labirinto->qtdLinhas * (sizeof(char *)));
    for (int i = 0; i < labirinto->qtdLinhas; i++) {
        labirinto->tabuleiro[i] = (char *)malloc(labirinto->qtdColunas * (sizeof(char)));
    }
    for (int i = 0; i < labirinto->qtdLinhas; i++) {
        for (int j = 0; j < labirinto->qtdColunas; j++) {
            scanf("%c", &labirinto->tabuleiro[i][j]);
        }
        char aux;
        scanf("%c", &aux);
    }
}

Posicao *criarPosicao(int x, int y) {
    Posicao *posicao = (Posicao *)malloc(sizeof(Posicao));
    posicao->x = x;
    posicao->y = y;
    return posicao;
}

Posicao *copiarPosicao(Posicao *posicao) { return criarPosicao(posicao->x, posicao->y); }

Posicao *somarXYposicao(Posicao posicao, int x, int y) {
    Posicao *novaPosicao = criarPosicao(posicao.x + x, posicao.y + y);
    return novaPosicao;
}

void moverPosicaoPelaDirecao(Posicao *posicao, Direcao direcao) {
    switch (direcao) {
    case CIMA:
        posicao->x--;
        break;
    case BAIXO:
        posicao->x++;
        break;
    case DIREITA:
        posicao->y++;
        break;
    case ESQUERDA:
        posicao->y--;
        break;
    }
}

void moverPosicaoParaPosicao(Posicao *posicao, Posicao *novaPosicao) {
    posicao->x = novaPosicao->x;
    posicao->y = novaPosicao->y;
}

void imprimirDirecao(Direcao direcao) {
    switch (direcao) {
    case CIMA:
        printf("CIMA ");
        break;
    case BAIXO:
        printf("BAIXO ");
        break;
    case DIREITA:
        printf("DIREITA ");
        break;
    case ESQUERDA:
        printf("ESQUERDA ");
        break;
    }
}

void desalocarLabirinto(Labirinto **labirinto) {
    for (int i = 0; i < (*labirinto)->qtdLinhas; i++) {
        free((*labirinto)->tabuleiro[i]);
    }
    free((*labirinto)->tabuleiro);
    free(*labirinto);
}

void desalocarDirecoesDisponiveis(DirecoesDisponiveis **direcoesDisponiveis) {
    free((*direcoesDisponiveis)->direcoes);
    free(*direcoesDisponiveis);
}

void desalocarPosicao(Posicao **posicao) { free(*posicao); }

void desalocarPercurso(Percurso **percurso) {
    free((*percurso)->posicoes);
    free(*percurso);
}

void imprimeLabirinto(Labirinto *labirinto) {
    for (int i = 0; i < labirinto->qtdLinhas; i++) {
        for (int j = 0; j < labirinto->qtdColunas; j++) {
            printf("%c", labirinto->tabuleiro[i][j]);
        }
        printf("\n");
    }
}

bool posicaoDisponivel(Labirinto *labirinto, Posicao *posicao) {
    return (labirinto->tabuleiro[posicao->x][posicao->y] == ' ') &&
           (posicao->x >= 0 && posicao->x <= labirinto->qtdLinhas - 1) &&
           (posicao->y >= 0 && posicao->y <= labirinto->qtdColunas - 1);
}

bool verificaPosicaoNoPercurso(Percurso *percurso, int x, int y) {
    for (int i = 0; i < percurso->passos; i++) {
        if (percurso->posicoes[i].x == x && percurso->posicoes[i].y == y) {
            return true;
        }
    }
    return false;
}

bool verificacaoParaPegarDirecoesPossiveis(Labirinto *labirinto, Posicao *posicao, Direcao origem, Direcao destino,
                                           Percurso *percurso) {
    bool novaPosicaoDisponivel = posicaoDisponivel(labirinto, posicao);
    bool naoEstaVoltando = origem != destino;
    bool posicaoNaoEstaNoPercurso = !verificaPosicaoNoPercurso(percurso, posicao->x, posicao->y);
    return novaPosicaoDisponivel && naoEstaVoltando && posicaoNaoEstaNoPercurso;
}

DirecoesDisponiveis *pegarDirecoesPossiveis(Labirinto *labirinto, Posicao posicaoRato, Direcao direcaoOrigem,
                                            Percurso *percurso) {
    DirecoesDisponiveis *direcoesDisponiveis = (DirecoesDisponiveis *)malloc(sizeof(DirecoesDisponiveis));
    bool podeAndarDireita = false, podeAndarEsquerda = false, podeAndarCima = false, podeAndarBaixo = false;

    Posicao *posicaoADireita = somarXYposicao(posicaoRato, 0, 1);
    if (verificacaoParaPegarDirecoesPossiveis(labirinto, posicaoADireita, direcaoOrigem, ESQUERDA, percurso))
        podeAndarDireita = true;
    desalocarPosicao(&posicaoADireita);

    Posicao *posicaoAEsquerda = somarXYposicao(posicaoRato, 0, -1);
    if (verificacaoParaPegarDirecoesPossiveis(labirinto, posicaoAEsquerda, direcaoOrigem, DIREITA, percurso))
        podeAndarEsquerda = true;
    desalocarPosicao(&posicaoAEsquerda);

    Posicao *posicaoACima = somarXYposicao(posicaoRato, -1, 0);
    if (verificacaoParaPegarDirecoesPossiveis(labirinto, posicaoACima, direcaoOrigem, BAIXO, percurso))
        podeAndarCima = true;
    desalocarPosicao(&posicaoACima);

    Posicao *posicaoABaixo = somarXYposicao(posicaoRato, 1, 0);
    if (verificacaoParaPegarDirecoesPossiveis(labirinto, posicaoABaixo, direcaoOrigem, CIMA, percurso))
        podeAndarBaixo = true;
    desalocarPosicao(&posicaoABaixo);

    direcoesDisponiveis->qtdDirecoes = podeAndarDireita + podeAndarEsquerda + podeAndarCima + podeAndarBaixo;
    direcoesDisponiveis->direcoes = (Direcao *)malloc((direcoesDisponiveis->qtdDirecoes) * sizeof(Direcao));

    int contadorIndiceAtual = 0;
    if (podeAndarBaixo)
        direcoesDisponiveis->direcoes[contadorIndiceAtual++] = BAIXO;
    if (podeAndarDireita)
        direcoesDisponiveis->direcoes[contadorIndiceAtual++] = DIREITA;
    if (podeAndarCima)
        direcoesDisponiveis->direcoes[contadorIndiceAtual++] = CIMA;
    if (podeAndarEsquerda)
        direcoesDisponiveis->direcoes[contadorIndiceAtual++] = ESQUERDA;

    return direcoesDisponiveis;
}

void copiarPercurso(Percurso *destino, Percurso *origem) {
    destino->passos = origem->passos;
    for (int i = 0; i < origem->passos; i++) {
        destino->posicoes[i].x = origem->posicoes[i].x;
        destino->posicoes[i].y = origem->posicoes[i].y;
    }
}

void imprimePercurso(Percurso *percurso) {
    for (int i = 0; i < percurso->passos; i++) {
        printf("(%d, %d)\n", percurso->posicoes[i].y, percurso->posicoes[i].x);
    }
}

void imprimeLabirintoEpercurso(Labirinto *labirinto, Percurso *percurso) {
    for (int i = 0; i < labirinto->qtdLinhas; i++) {
        for (int j = 0; j < labirinto->qtdColunas; j++) {
            if (verificaPosicaoNoPercurso(percurso, i, j))
                printf(".");
            else
                printf("%c", labirinto->tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void imprimeSaida(Labirinto *labirinto, Percurso *menorPercurso) {
    printf("%d\n", menorPercurso->passos);
    if (labirinto->opcao == 'c') {
        imprimePercurso(menorPercurso);
    } else {
        imprimeLabirintoEpercurso(labirinto, menorPercurso);
    }
}

void acharSaida(Labirinto *labirinto, Posicao *posicaoRato, int direcaoOrigem, int *menorCaminho,
                Percurso *menorPercurso, Percurso *percursoAtual) {
    Percurso *novoPercursoAtual = alocarPercurso(labirinto);
    copiarPercurso(novoPercursoAtual, percursoAtual);

    if (posicaoRato->y + 1 == labirinto->qtdColunas) {
        if (percursoAtual->passos < *menorCaminho) {
            *menorCaminho = percursoAtual->passos;
            copiarPercurso(menorPercurso, percursoAtual);
        }
        desalocarPercurso(&novoPercursoAtual);
        return;
    }

    DirecoesDisponiveis *direcoesPossiveis =
        pegarDirecoesPossiveis(labirinto, *posicaoRato, direcaoOrigem, percursoAtual);

    novoPercursoAtual->passos++;
    Posicao *novaPosicao = copiarPosicao(posicaoRato);
    Posicao *posicaoAtualInicial = copiarPosicao(posicaoRato);

    for (int i = 0; i < direcoesPossiveis->qtdDirecoes; i++) {
        Direcao direcao = direcoesPossiveis->direcoes[i];
        moverPosicaoPelaDirecao(novaPosicao, direcao);
        novoPercursoAtual->posicoes[novoPercursoAtual->passos - 1] = *novaPosicao;

        if (direcao == BAIXO)
            acharSaida(labirinto, novaPosicao, BAIXO, menorCaminho, menorPercurso, novoPercursoAtual);
        if (direcao == DIREITA)
            acharSaida(labirinto, novaPosicao, DIREITA, menorCaminho, menorPercurso, novoPercursoAtual);
        if (direcao == ESQUERDA)
            acharSaida(labirinto, novaPosicao, ESQUERDA, menorCaminho, menorPercurso, novoPercursoAtual);
        if (direcao == CIMA)
            acharSaida(labirinto, novaPosicao, CIMA, menorCaminho, menorPercurso, novoPercursoAtual);

        moverPosicaoParaPosicao(novaPosicao, posicaoAtualInicial);
    }

    desalocarPosicao(&posicaoAtualInicial);
    desalocarPosicao(&novaPosicao);
    desalocarPercurso(&novoPercursoAtual);
    desalocarDirecoesDisponiveis(&direcoesPossiveis);
}

Posicao *encontrarPosicaoDoRato(Labirinto *labirinto) {
    Posicao *posicao = (Posicao *)malloc(sizeof(Posicao));
    for (int i = 0; i < labirinto->qtdLinhas; i++) {
        for (int j = 0; j < labirinto->qtdColunas; j++) {
            if (labirinto->tabuleiro[i][j] == 'M') {
                posicao->x = i;
                posicao->y = j;
                return posicao;
            }
        }
    }
    posicao->x = -1;
    posicao->y = -1;
    return posicao;
}

Percurso *alocarPercurso(Labirinto *labirinto) {
    Percurso *percurso = (Percurso *)malloc(sizeof(Percurso));
    percurso->posicoes = (Posicao *)malloc((labirinto->qtdLinhas * labirinto->qtdColunas * 10) * sizeof(Posicao));
    percurso->passos = 0;
    return percurso;
}

bool posicaoEstaNoPercurso(Posicao posicao, Direcao direcao, Percurso *percurso) {
    moverPosicaoPelaDirecao(&posicao, direcao);
    for (int i = 0; i < percurso->passos; i++) {
        Posicao posicaoAtual = percurso->posicoes[i];
        if (posicaoAtual.x == posicao.x && posicaoAtual.y == posicao.y)
            return true;
    }
    return false;
}

DirecoesDisponiveis *alocarDirecoesDisponiveis() {
    DirecoesDisponiveis *direcoesDisponiveis = (DirecoesDisponiveis *)malloc(sizeof(DirecoesDisponiveis));
    direcoesDisponiveis->direcoes = (Direcao *)malloc(sizeof(Direcao) * 4);
    direcoesDisponiveis->qtdDirecoes = 0;
    return direcoesDisponiveis;
}

void incializaTabuleiro(Labirinto *labirinto) {
    for (int i = 0; i < labirinto->qtdLinhas; i++) {
        for (int j = 0; j < labirinto->qtdColunas; j++) {
            labirinto->tabuleiro[i][j] = '*';
        }
    }
}

bool estaNaBordaPelaDirecao(Labirinto *labirinto, Direcao direcao, Posicao posicao, int desvioX, int desvioY) {
    moverPosicaoPelaDirecao(&posicao, direcao);
    bool bordaEmX = posicao.x == 0 + desvioX || posicao.x >= labirinto->qtdLinhas - 1 - desvioX;
    bool bordaEmY = posicao.y == 0 + desvioY || posicao.y >= labirinto->qtdColunas - 1 - desvioY;
    return bordaEmX || bordaEmY;
}

bool podeRemoverPara(Labirinto *labirinto, Direcao direcao, Posicao posicao) {
    bool cimaDireita = true, baixoEsquerda = true, cimaEsquerda = true, baixoDireita = true;

    if (posicao.x - 1 >= 0 && posicao.y - 1 >= 0)
        cimaEsquerda = labirinto->tabuleiro[posicao.x - 1][posicao.y - 1] == '*';
    if (posicao.x - 1 >= 0 && posicao.y + 1 <= labirinto->qtdColunas)
        cimaDireita = labirinto->tabuleiro[posicao.x - 1][posicao.y + 1] == '*';
    if (posicao.x + 1 <= labirinto->qtdLinhas && posicao.y - 1 >= 0)
        baixoEsquerda = labirinto->tabuleiro[posicao.x + 1][posicao.y - 1] == '*';
    if (posicao.x + 1 <= labirinto->qtdLinhas && posicao.y + 1 <= labirinto->qtdColunas)
        baixoDireita = labirinto->tabuleiro[posicao.x + 1][posicao.y + 1] == '*';

    bool aEsquerda = true, aDireita = true, aCima = true, aBaixo = true;
    if (posicao.y - 1 >= 0)
        aEsquerda = labirinto->tabuleiro[posicao.x][posicao.y - 1] == ' ';
    if (posicao.y + 1 <= labirinto->qtdColunas)
        aDireita = labirinto->tabuleiro[posicao.x][posicao.y + 1] == ' ';
    if (posicao.x - 1 >= 0)
        aCima = labirinto->tabuleiro[posicao.x - 1][posicao.y] == ' ';
    if (posicao.x - 1 <= labirinto->qtdLinhas)
        aBaixo = labirinto->tabuleiro[posicao.x + 1][posicao.y] == ' ';
    return (cimaDireita + cimaEsquerda + baixoEsquerda + baixoDireita >= 3) &&
           (aEsquerda + aDireita + aCima + aBaixo <= 1);
}

bool podeMoverParaCaminhoVazio(Labirinto *labirinto, Direcao direcao, Posicao posicao) {
    moverPosicaoPelaDirecao(&posicao, direcao);

    if (posicao.x >= 0 && posicao.x <= labirinto->qtdColunas && posicao.y >= 0 && posicao.y <= labirinto->qtdLinhas)
        return labirinto->tabuleiro[posicao.x][posicao.y] == ' ';

    return false;
}

bool contemValorNoVetor(Direcao *vetor, int tamVetor, int item) {
    for (int i = 0; i < tamVetor; i++) {
        if (vetor[i] == item)
            return true;
    }
    return false;
}

Direcao *gerarDirecoesAleatorias() {
    Direcao *direcoes = (Direcao *)malloc(sizeof(Direcao) * 4);
    for (int i = 0; i < 4; i++)
        direcoes[i] = -1;
    int i = 0;

    while (i < 4) {
        int direcaoAleatoria = rand() % 4;
        if (contemValorNoVetor(direcoes, 4, direcaoAleatoria))
            continue;
        direcoes[i++] = direcaoAleatoria;
    }
    return direcoes;
}

DirecoesDisponiveis *direcoesQuePodeCriarBifurcacao(Labirinto *labirinto, Posicao *posicao) {
    bool podeEmCima = labirinto->tabuleiro[posicao->x - 1][posicao->y - 1] == '*' &&
                      labirinto->tabuleiro[posicao->x - 1][posicao->y] == '*' &&
                      labirinto->tabuleiro[posicao->x - 1][posicao->y + 1] == '*' && posicao->x - 1 > 0;
    bool podeEmBaixo = labirinto->tabuleiro[posicao->x + 1][posicao->y - 1] == '*' &&
                       labirinto->tabuleiro[posicao->x + 1][posicao->y] == '*' &&
                       labirinto->tabuleiro[posicao->x + 1][posicao->y + 1] == '*' &&
                       posicao->x + 2 < labirinto->qtdLinhas;
    bool podeNaDireita = labirinto->tabuleiro[posicao->x + 1][posicao->y + 1] == '*' &&
                         labirinto->tabuleiro[posicao->x][posicao->y + 1] == '*' &&
                         labirinto->tabuleiro[posicao->x - 1][posicao->y + 1] == '*' &&
                         posicao->y + 1 < labirinto->qtdColunas;
    bool podeNaEsquerda = labirinto->tabuleiro[posicao->x + 1][posicao->y - 1] == '*' &&
                          labirinto->tabuleiro[posicao->x][posicao->y - 1] == '*' &&
                          labirinto->tabuleiro[posicao->x - 1][posicao->y - 1] == '*' && posicao->y - 1 > 0;

    DirecoesDisponiveis *direcoesDisponiveis = alocarDirecoesDisponiveis();
    if (podeEmCima)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = CIMA;
    if (podeEmBaixo)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = BAIXO;
    if (podeNaDireita)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = DIREITA;
    if (podeNaEsquerda)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = ESQUERDA;
    return direcoesDisponiveis;
}

bool podeRemoverParaBifurcacao(Labirinto *labirinto, Direcao direcao, Posicao posicao) {
    moverPosicaoPelaDirecao(&posicao, direcao);
    int yMainUm = posicao.y + 1;
    int yMenosUm = posicao.y - 1;
    int xMaisUm = posicao.x + 1;
    int xMinusOne = posicao.x - 1;

    bool cimaEsquerda = false, cimaDireita = false, baixoEsquerda = false, baixoDireita = false;
    bool aEsquerda = false, aDireita = false, aCima = false, aBaixo = false;

    if (yMenosUm >= 0 && xMinusOne >= 0)
        cimaEsquerda = labirinto->tabuleiro[xMinusOne][yMenosUm] == '*';
    if (yMainUm < labirinto->qtdColunas && xMinusOne >= 0)
        cimaDireita = labirinto->tabuleiro[xMinusOne][yMainUm] == '*';
    if (yMenosUm >= 0 && xMaisUm < labirinto->qtdLinhas)
        baixoEsquerda = labirinto->tabuleiro[xMaisUm][yMenosUm] == '*';
    if (yMainUm < labirinto->qtdColunas && xMaisUm < labirinto->qtdLinhas)
        baixoDireita = labirinto->tabuleiro[xMaisUm][yMainUm] == '*';

    if (yMenosUm >= 0)
        aEsquerda = labirinto->tabuleiro[posicao.x][yMenosUm] == '*';
    if (yMainUm < labirinto->qtdColunas)
        aDireita = labirinto->tabuleiro[posicao.x][yMainUm] == '*';
    if (xMinusOne >= 0)
        aCima = labirinto->tabuleiro[xMinusOne][posicao.y] == '*';
    if (xMaisUm < labirinto->qtdLinhas)
        aBaixo = labirinto->tabuleiro[xMaisUm][posicao.y] == '*';

    return (cimaDireita + cimaEsquerda + baixoEsquerda + baixoDireita >= 2) &&
           (aEsquerda + aDireita + aCima + aBaixo >= 3);
}

void criarBifurcacao(Labirinto *labirinto, Posicao posicao, Direcao direcao, int chance) {
    bool estaNaBorda = estaNaBordaPelaDirecao(labirinto, direcao, posicao, 1, 1);
    bool naoPodeMoverParaDirecao = !podeRemoverParaBifurcacao(labirinto, direcao, posicao);

    moverPosicaoPelaDirecao(&posicao, direcao);
    if (estaNaBorda || naoPodeMoverParaDirecao || !((rand() % 100) + 1 <= chance))
        return;

    labirinto->tabuleiro[posicao.x][posicao.y] = ' ';

    Direcao *direcoesAleatorias = gerarDirecoesAleatorias();
    for (int i = 0; i < 4; i++) {
        Direcao direcaoAtual = direcoesAleatorias[i];
        criarBifurcacao(labirinto, posicao, direcaoAtual, chance - 5);
    }
    free(direcoesAleatorias);
}

DirecoesDisponiveis *direcoesDisponiveisParaMovimento(Labirinto *labirinto, Posicao posicao) {

    bool aEsquerda = labirinto->tabuleiro[posicao.x][posicao.y - 1] == ' ';
    bool aDireita = labirinto->tabuleiro[posicao.x][posicao.y + 1] == ' ';
    bool aCima = labirinto->tabuleiro[posicao.x - 1][posicao.y] == ' ';
    bool aBaixo = labirinto->tabuleiro[posicao.x + 1][posicao.y] == ' ';
    DirecoesDisponiveis *direcoesDisponiveis = alocarDirecoesDisponiveis();
    if (aCima)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = CIMA;
    if (aBaixo)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = BAIXO;
    if (aDireita)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = DIREITA;
    if (aEsquerda)
        direcoesDisponiveis->direcoes[direcoesDisponiveis->qtdDirecoes++] = ESQUERDA;
    return direcoesDisponiveis;
}

void percorrerCaminho(Labirinto *labirinto, Posicao posicao, Percurso *percursoAtual) {
    percursoAtual->posicoes[percursoAtual->passos++] = posicao;

    if (posicao.x == labirinto->qtdLinhas - 2 && posicao.y == labirinto->qtdColunas - 2) {
        return;
    }

    DirecoesDisponiveis *direcoesDisponiveis = direcoesDisponiveisParaMovimento(labirinto, posicao);
    Posicao posicaoInicial = posicao;
    for (int i = 0; i < direcoesDisponiveis->qtdDirecoes; i++) {
        Direcao direcaoAtual = direcoesDisponiveis->direcoes[i];
        bool podeMoverParaDirecaoAtual = podeMoverParaCaminhoVazio(labirinto, direcaoAtual, posicao);
        bool posicaoNaoEstaNoPercurso = !posicaoEstaNoPercurso(posicao, direcaoAtual, percursoAtual);

        if (podeMoverParaDirecaoAtual && posicaoNaoEstaNoPercurso)
            moverPosicaoPelaDirecao(&posicao, direcaoAtual);
        else
            continue;

        percorrerCaminho(labirinto, posicao, percursoAtual);
    }
    desalocarDirecoesDisponiveis(&direcoesDisponiveis);
    moverPosicaoParaPosicao(&posicao, &posicaoInicial);
    DirecoesDisponiveis *direcoesDisponiveisParaBifurcar = direcoesQuePodeCriarBifurcacao(labirinto, &posicao);
    if (direcoesDisponiveisParaBifurcar->qtdDirecoes == 0) {
        desalocarDirecoesDisponiveis(&direcoesDisponiveisParaBifurcar);
        return;
    }
    Direcao direcao = direcoesDisponiveisParaBifurcar->direcoes[rand() % direcoesDisponiveisParaBifurcar->qtdDirecoes];
    criarBifurcacao(labirinto, posicao, direcao, 100);
    desalocarDirecoesDisponiveis(&direcoesDisponiveisParaBifurcar);
}

void criarSaida(Labirinto *labirinto, Posicao posicao, Percurso *percursoAtual, bool *criouSaida) {
    labirinto->tabuleiro[posicao.x][posicao.y] = ' ';
    percursoAtual->posicoes[percursoAtual->passos++] = posicao;
    Direcao *direcoesAleatorias = gerarDirecoesAleatorias();

    if (posicao.x == labirinto->qtdLinhas - 2 && posicao.y == labirinto->qtdColunas - 2) {
        *criouSaida = true;
        free(direcoesAleatorias);
        return;
    }

    Posicao posicaoInicial = posicao;
    for (int i = 0; i < 4; i++) {
        Direcao direcaoAtual = direcoesAleatorias[i];

        bool estaNaBorda = estaNaBordaPelaDirecao(labirinto, direcaoAtual, posicao, 0, 0);
        bool naoPodeMoverParaDirecao = !podeRemoverPara(labirinto, direcaoAtual, posicao);
        bool jaPassouPorAqui = posicaoEstaNoPercurso(posicao, direcaoAtual, percursoAtual);
        if (estaNaBorda || naoPodeMoverParaDirecao || jaPassouPorAqui)
            continue;
        moverPosicaoPelaDirecao(&posicao, direcaoAtual);
        criarSaida(labirinto, posicao, percursoAtual, criouSaida);
        if (*criouSaida) {
            free(direcoesAleatorias);
            return;
        }
        moverPosicaoParaPosicao(&posicao, &posicaoInicial);
    }
    free(direcoesAleatorias);
    labirinto->tabuleiro[posicao.x][posicao.y] = '*';
}

Labirinto *gerarLabirintoAleatorio(Labirinto *labirinto, int l, int c, char opcao) {
    labirinto->qtdColunas = c;
    labirinto->qtdLinhas = l;

    labirinto->tabuleiro = (char **)malloc(sizeof(char *) * l);
    for (int i = 0; i < l; i++)
        labirinto->tabuleiro[i] = (char *)malloc(sizeof(char) * c);

    labirinto->opcao = opcao;

    Percurso *percursoAtual = alocarPercurso(labirinto);
    incializaTabuleiro(labirinto);
    bool criouSaida = false;
    Posicao *posicao = criarPosicao(1, 1);
    criarSaida(labirinto, *posicao, percursoAtual, &criouSaida);
    desalocarPercurso(&percursoAtual);

    Percurso *percursoPercorridoAtual = alocarPercurso(labirinto);
    percorrerCaminho(labirinto, *posicao, percursoPercorridoAtual);
    desalocarPercurso(&percursoPercorridoAtual);

    desalocarPosicao(&posicao);

    labirinto->tabuleiro[l - 2][c - 1] = ' ';
    labirinto->tabuleiro[1][1] = 'M';
    return labirinto;
}
