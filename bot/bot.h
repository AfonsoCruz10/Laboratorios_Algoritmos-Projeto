//
// Created by andre on 03-05-2020.
//


#include <stdio.h>
#include <stdlib.h>

#ifndef TENTATIVADOBOT_BOT_H
#define TENTATIVADOBOT_BOT_H



/**
\brief Tipo de dados para a casa
*/
typedef enum {
    UM = '1',
    DOIS = '2',
    VAZIO = '.',
    BRANCA = '*',
    PRETA = '#'
} CASA;

/**
\brief Tipo de dados para as coordenadas
*/
typedef struct {
    int coluna;
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;
/**
\brief Tipo de dados para as jogadas
*/
typedef JOGADA JOGADAS[32];
/**
\brief Tipo de dados para o estado
*/
typedef struct {
    /** O tabuleiro */
    CASA tab[8][8];
    /** A coordenada da última jogada */
    COORDENADA ultima_jogada;
    /** As jogadas */
    JOGADAS jogadas;
    /** O número das jogadas, usado no prompt */
    int num_jogadas;
    /** O jogador atual */
    int jogador_atual;

} ESTADO;
/**
 \brief Tipo de dados para o comando jog
 */
typedef struct lligada {
    /** Coordendas */
    COORDENADA x;
    /** struct listas ligadas*/
    struct lligada *prox;
} *LL;


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
 * guarda todas as jogadas possiveis
 * @param e ponteiro para o estado
 * @return lista ligadas com todas as jogadas
 */
LL JP(ESTADO *e);

/**
 * Indica o jogador atual
 * @param e apontador para o estado em que se vai buscar o jogador atual antes de atualizado
 * @return o jogador atual para ser usado no prompt
 */
int obter_jogador_atual(ESTADO *e);

/**
 * Indica o numero de jogadas de cada jogador
 * @param estado o numero de jogadas antes da jogada atual
 * @return numero de jogadas ao fim da jogada atual
 */
int obter_numero_de_jogadas(ESTADO *estado);

/**
 * diz se a lista está vazia ou nao
 * @param t lista ligada
 * @return 1 ou 0 dependendo se é verdade ou nao
 */
int lista_esta_vazia (LL t);
/**
 * valida se as jogadas do bot são validas
 * @param e ponteiro para o estado
 * @param a linha da jogada
 * @param b coluna da jogada
 * @return 1 ou 0 dependendo se é valida ou não
 */
int validar_bot(ESTADO *e, int a , int b);
/**
 * verifica se uma jogada dá vitoria quando o comando jog é usado
 * @param e ponteiro para o estado
 * @return falso se não for vitoria ou entao o jogador vencedor
 */
int inception(ESTADO *e);
/**
 * verifica se uma jogada cria um espaço fechado no tabuleiro
 * @param e  ponteiro para o estado
 * @return numero de espaços fechados
 */
int inception2(ESTADO *e);
/**
 * copia os dados de uma lista para outra lista
 * @param t lista ligada
 * @return lista ligada com o mesmo conteudo da lista inserida
 */
LL copiaL(LL t);
/**
 * copia os dados de um estado para outro
 * @param e ponteiro para um estaado
 * @return estado clone
 */
ESTADO *copia(ESTADO *e);
/**
 * comando jog com a heuristica da menor distancia
 * @param e ponteiro para o estado
 */
void bot_fraco(ESTADO * e,LL t);
/**
 * realiza 9 jogadas do bo_fraco para determinar a melhor jogada
 */
void bot_medio(ESTADO *e,LL t);

/**
 * insere uma cabeça na lista
 * @param v coordenada que insere na lista
 * @param t lista em que é inserida
 * @return lista com a cabeça
 */
LL insere_cabeca (COORDENADA v, LL t);

/**
\brief Inicializa o valor do estado
Esta função inicializa o valor do estado. Isso implica o tabuleiro ser colocado na posição inicial e todos os campos do estado estarem com o valor por omissão.
@returns O novo estado
*/
ESTADO *inicializar_estado();

#endif //TENTATIVADOBOT_BOT_H