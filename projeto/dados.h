//
// Created by luisf on 3/11/2020.
//

/**
@file dados.h
Definição do estado e das funções que o manipulam
*/

#ifndef PROJETO_DADOS_H
#define PROJETO_DADOS_H
/**
\brief Tipo de dados para os erros
*/
typedef enum {
    OK,
    COORDENADA_INVALIDA,
    JOGADA_INVALIDA,
    ERRO_LER_TAB,
    ERRO_ABRIR_FICHEIRO,
} ERROS;

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

/**
\brief Inicializa o valor do estado
Esta função inicializa o valor do estado. Isso implica o tabuleiro ser colocado na posição inicial e todos os campos do estado estarem com o valor por omissão.
@returns O novo estado
*/
ESTADO *inicializar_estado();
/**
 * Indica o jogador atual
 * @param e apontador para o estado em que se vai buscar o jogador atual antes de atualizado
 * @return o jogador atual para ser usado no prompt
 */
int obter_jogador_atual(ESTADO *e);
/**
 *Indica o estado da casa
 * @param e Apontador para o estado
 * @param c Coordenada
 * @return estado da casa
 */
CASA obter_estado_casa(ESTADO *e, COORDENADA c);
/**
 * Indica o numero de jogadas de cada jogador
 * @param estado o numero de jogadas antes da jogada atual
 * @return numero de jogadas ao fim da jogada atual
 */
int obter_numero_de_jogadas(ESTADO *estado);
/**
 * cria uma lista ligada
 * @return de uma lista ligada
 */
LL criar_lista();
/**
 * insere uma cabeça na lista
 * @param v coordenada que insere na lista
 * @param t lista em que é inserida
 * @return lista com a cabeça
 */
LL insere_cabeca (COORDENADA v, LL t);
/**
 * vai buscar uma cabeça a uma lista ligada
 * @param t lista onde vai buscar a cabeça
 * @return coordenada
 */
COORDENADA devolve_cabeca(LL t);
/**
 * vai buscar o proxime elemento da lista
 * @param t lista a que vai buscar o elemento
 * @return o proximo elemento
 */
LL proximo(LL t);
/**
 * remove a cabeça de uma lista
 * @param t lista ligada
 * @return lista sem a cabeça
 */
LL remove_cabeca(LL t);
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

#endif //PROJETO_DADOS_H


