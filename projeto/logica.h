//
// Created by luisf on 3/11/2020.
//

/**
@file logica.h
Funções que alteram o Estado conforme as jogadas
*/

#include "dados.h"


#ifndef PROJETO_LOGICA_H
#define PROJETO_LOGICA_H

/**
 * funçao que valida jogadas
 * @param e apontador para o estado
 * @param c coordenada por validar
 * @return 1 ou 0 dependendo se a jogada é valida
 */
int validar(ESTADO *e, COORDENADA c);
/**
 * funçao que indica se o jogo acabou e o jogador vencedor
 * @param e apontador para o estado
 * @return jogador vencedor
 */
int vitoria(ESTADO *e);
/**
 * coloca a casa anterior no Estado de Casa Preta
 * @param e apontador para o estado atual
 * @return estado atualizado
 */
ESTADO preta(ESTADO *e);
/**
 * Move a peça Branca para a coordenada dada pelo jogador atual
 * @param e apontador para o estado
 * @param c coordenada dada pelo jogador
 * @return Estado atualiazado com o jogada
 */
ESTADO branca (ESTADO *e, COORDENADA c);
/**
 * altera o estado conforme a jogada
 * @param e apontador para o estado
 * @param c Coordenada
 * @return estado alterado
 */
void jogar(ESTADO *e, COORDENADA c);

#endif //PROJETO_LOGICA_H
