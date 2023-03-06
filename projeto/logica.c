#include <stdio.h>
#include "interface.h"
#include "logica.h"
#include "dados.h"

#define BUF_SIZE 1024

int validar(ESTADO *e, COORDENADA c) {
    int a,b,m,n;
    COORDENADA x;
    x=e->ultima_jogada;
    m=x.linha;
    n=x.coluna;
    a=c.linha;
    b=c.coluna;
    if ((e->tab[a][b] == VAZIO || e->tab[a][b] == UM || e->tab[a][b] == DOIS) &&
        ((a == m + 1 && b == n + 1) || (a == m && b == n + 1) || (a == m - 1 && b == n + 1) || (a == m + 1 && b == n) ||
         (a == m && b == n) || (a == m - 1 && b == n) || (a == m + 1 && b == n - 1) || (a == m && b == n - 1) ||
         (a == m - 1 && b == n - 1))) {
        return 1;
    }
    else {
        printf("\n Tente novamente! \n");
        return 0;
    }
}



int vitoria(ESTADO *e) {
    int d, x, m, n;
    x = 0;
    d = e->jogador_atual;
    m = e->ultima_jogada.linha;
    n = e->ultima_jogada.coluna;
    if (m == 0 && n == 7) {
        (x = d);
        printf("\n O VENCEDOR E O JOGADOR 2");
    } else if (m == 7 && n == 0) {
        (x = d);
        printf("\n O VENCEDOR E O JOGADOR  1");
    } else if (!(e->tab[m][n - 1] == VAZIO || e->tab[m + 1][n - 1] == VAZIO || e->tab[m - 1][n - 1] == VAZIO ||
                 e->tab[m + 1][n] == VAZIO || e->tab[m - 1][n] == VAZIO || e->tab[m + 1][n + 1] == VAZIO ||
                 e->tab[m][n + 1] == VAZIO || e->tab[m - 1][n + 1] == VAZIO) && (d == 1)) {
        (x = 2);
        printf("\n O VENCEDOR E O JOGADOR 2");
    } else if (!(e->tab[m][n - 1] == VAZIO || e->tab[m + 1][n - 1] == VAZIO || e->tab[m - 1][n - 1] == VAZIO ||
                 e->tab[m + 1][n] == VAZIO || e->tab[m - 1][n] == VAZIO || e->tab[m + 1][n + 1] == VAZIO ||
                 e->tab[m][n + 1] == VAZIO || e->tab[m - 1][n + 1] == VAZIO) && (d == 2)) {
        (x = 1);
        printf(" \n O VENCEDOR E O JOGADOR 1");
    }
    return x;
}


ESTADO branca (ESTADO *e, COORDENADA c) {
    int a,b;
    a=c.linha;
    b=c.coluna;
    e-> tab[a][b] = BRANCA;
    return *e;
}


ESTADO preta(ESTADO *e) {
    int a,b;
    COORDENADA c;
    c = e->ultima_jogada;
    a = c.linha;
    b = c.coluna;
    e -> tab[a][b] = PRETA;
    return *e;
}


void jogar(ESTADO *e, COORDENADA c) {
    branca(e,c);
    preta(e);
    e->ultima_jogada = c;
    obter_jogador_atual(e);
    obter_numero_de_jogadas(e);
    gr_jogada(e,c);
}


