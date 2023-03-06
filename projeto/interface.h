//
// Created by luisf on 3/11/2020.
//
/**
@file interface.h
Funções que alteram a interface do jogo
*/

#include "dados.h"
#include <stdio.h>

#ifndef PROJETO_INTERFACE_H
#define PROJETO_INTERFACE_H

/**
 * funçao que imprime o tabuleiro
 * @param e apontador para o estado
 */
void mostrar_tabuleiro(ESTADO *e);
/**
 * funçao que desenvolve o jogo
 * @param e apontador para o estado
 * @return do jogo desenvolvido jogada após jogada
 */
int interpretador(ESTADO *e);
/**
 * funçao que indica o numero de jogadas e o numero atual de jogadas
 * @param e apontador para o estado
 * @return do turno do jogador e da ronda atual
 */
int prompt(ESTADO *e);
/**
 * lê um ficheiro com o estado do tabuleiro e os movimetos
 * @param e ponteiro para o estado
 * @param nome nome do ficheiro
 */
void ler(ESTADO *e,char nome[]);
/**
 * grava num ficheiro o estado do tabuleiro e os moviemtos que levaram a dito estado
 * @param e ponteiro para o estado
 * @param nome nome do ficheiro
 */
void gravar(ESTADO *e, char *nome);
/**
 * cria um ficheiro para utilizar a aux
 * @param e ponteiro para estado
 * @param nome nome do ficheiro
 */
void movs(ESTADO *e, char nome[]);
/**
 * grava a coordenada que acabou de ser jogada
 * @param e ponteiro para o estado
 * @param c coordenada
 */
void gr_jogada(ESTADO*e, COORDENADA c);
/**
 * guarda num ficheiro os movimentos até o comando ser executado
 * @param mov ponteiro para o file
 * @param e ponteiro para o estado
 */
void aux(FILE *mov,ESTADO *e);
/**
 * deixa jogar apartir de uma jogada anterior
 * @param e ponteiro para o estado
 * @param n numero de jogada que se quer reverter o tabuleiro
 * @return tabuleiro com a posiçao da jogada inserida
 */
ESTADO* pos(ESTADO *e, int n);
/**
 * guarda todas as jogadas possiveis
 * @param e ponteiro para o estado
 * @return lista ligadas com todas as jogadas
 */
LL JP(ESTADO *e);
/**
 *chama o bot com a euristica de prever jogadas segundo um padrão
 * @param e ponteiro para o estado
 */
void jog2(ESTADO *e);
/**
 * chama o bot com a euristica de menor distancia euclidiana
 * @param e ponteiro para o estado
 */
void jog1(ESTADO *e);

#endif //PROJETO_INTERFACE_H



