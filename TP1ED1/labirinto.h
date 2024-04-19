#ifndef LABIRINTO_H
#define LABIRINTO_H
#include <stdbool.h>

typedef struct labirinto Labirinto;
typedef struct posicao Posicao;
typedef struct percurso Percurso;

Labirinto *alocarLabirinto();
Percurso *alocarPercurso(Labirinto *labirinto);

void leLabirinto(Labirinto *labirinto);
Labirinto *gerarLabirintoAleatorio(Labirinto *labirinto, int l, int c, char opcao);
Posicao *encontrarPosicaoDoRato(Labirinto *labirinto);

void acharSaida(Labirinto *labirinto, Posicao *posicaoRato, int direcaoOrigem, int *menorCaminho,
                Percurso *menorPercurso, Percurso *percursoAtual);

void imprimeSaida(Labirinto *labirinto, Percurso *menorPercurso);

void imprimeLabirinto(Labirinto *labirinto);

void desalocarLabirinto(Labirinto **labirinto);
void desalocarPosicao(Posicao **posicao);
void desalocarPercurso(Percurso **percurso);

#endif // LABIRINTO_H