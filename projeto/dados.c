//
// Created by luisf on 3/11/2020.
//
#include <stdio.h>
#include "interface.h"
#include "logica.h"
#include "dados.h"
#include <stdlib.h>

#define BUF_SIZE 1024

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    int i, j;
    e->jogador_atual = 1;
    e->num_jogadas = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            e->tab[i][j] = VAZIO;
        }
    }
    e->tab[0][7] = DOIS;
    e->tab[7][0] = UM;
    e->tab[3][4] = BRANCA;
    e->ultima_jogada.linha=3;
    e->ultima_jogada.coluna=4;
    return e;
}


int obter_jogador_atual(ESTADO *e){
    if (e->jogador_atual==1) e->jogador_atual=2;
    else e->jogador_atual=1;
    return 0;
}


CASA obter_estado_casa(ESTADO *e, COORDENADA c) {
    int a, b;
    a=c.linha;
    b=c.coluna;
    CASA casa;
    casa = e->tab [a] [b];
    return casa;
}


int obter_numero_de_jogadas(ESTADO *e){
    if (e->jogador_atual==2) {
        e->num_jogadas++;

    }
    return 0;
}


LL criar_lista(){
    LL *listaligada=NULL;
    return *listaligada;
}


LL insere_cabeca (COORDENADA v, LL t){
    LL new = (LL) malloc (sizeof (struct lligada));
    if (new!=NULL) {
        new-> x = v;
        new-> prox  = t;
    }
    return new;
}


COORDENADA devolve_cabeca(LL t){
    return t->x;
}


LL proximo(LL t){
    return t->prox;
}


LL remove_cabeca(LL t){
    LL x=t;
    t=t->prox;
    free(x);
    return t;
}


int lista_esta_vazia (LL t){
    if (t==NULL) return 1;
    return 0;
}


int validar_bot(ESTADO *e, int a , int b) {
    if ((e->tab[a][b] == VAZIO || e->tab[a][b] == UM || e->tab[a][b] == DOIS) && a<8 && a>=0 && b<8 && b>=0) return 1;
    return 0;
}


int inception(ESTADO *e) {
    int d, x, m, n;
    x = 0;
    d = e->jogador_atual;
    m = e->ultima_jogada.linha;
    n = e->ultima_jogada.coluna;
    if (m == 0 && n == 7) {
        x = d;
    } else if (m == 7 && n == 0) {
        x = d;
    } else if (!(e->tab[m][n - 1] == VAZIO || e->tab[m + 1][n - 1] == VAZIO || e->tab[m - 1][n - 1] == VAZIO ||
                 e->tab[m + 1][n] == VAZIO || e->tab[m - 1][n] == VAZIO || e->tab[m + 1][n + 1] == VAZIO ||
                 e->tab[m][n + 1] == VAZIO || e->tab[m - 1][n + 1] == VAZIO) && (d == 1)) {
        x = 2;
    } else if (!(e->tab[m][n - 1] == VAZIO || e->tab[m + 1][n - 1] == VAZIO || e->tab[m - 1][n - 1] == VAZIO ||
                 e->tab[m + 1][n] == VAZIO || e->tab[m - 1][n] == VAZIO || e->tab[m + 1][n + 1] == VAZIO ||
                 e->tab[m][n + 1] == VAZIO || e->tab[m - 1][n + 1] == VAZIO) && (d == 2)) {
        x = 1;
    }
    return x;
}


int inception2(ESTADO *e) {
    int n=0;
    while(!inception(e) ){
        n++;
        bot_fraco(e,JP(e));
    }
    if(inception(e)!=e->jogador_atual) return 1;
    else if(inception(e)==e->jogador_atual) return 2;
    return n;
}

LL copiaL(LL t){
    LL d=(LL) malloc (sizeof (struct lligada));
    d->x=t->x;
    d->prox=t->prox;
    return d;
}


ESTADO *copia(ESTADO *e){
    ESTADO *d=inicializar_estado();
    d->jogador_atual=e->jogador_atual;
    d->ultima_jogada=e->ultima_jogada;
    d->num_jogadas=e->num_jogadas;
    for (int i =0; i < 8 ; ++i) {
        for (int j = 0; j < 8; ++j) {
            d->tab[i][j]=e->tab[i][j];
        }
    }
    return d;
}


void bot_fraco(ESTADO *e,LL t) {
    ESTADO *d;
    LL h = t;
    while (!lista_esta_vazia(h)) {
        d = copia(e);
        jogar(d, h->x);
        if (inception(d) != 0 && inception(d) == e->jogador_atual) {
            jogar(e, h->x);
            return;
        }
        h = h->prox;
    }
    if (e->jogador_atual == 1) {
        while (t->prox != NULL) {
            t = t->prox;
        }
    }
    jogar(e, t->x);
}

void bot_medio(ESTADO *e,LL t) {
    ESTADO *d;
    COORDENADA c;
    c.linha=8;
    c.coluna=8;
    LL h = copiaL(t);
    while (h != NULL) {
        d = copia(e);
        jogar(d, h->x);
        if (inception2(d) % 2 == 0) {
            jogar(e, h->x);
            return;
        }
        else h->x = c;
        h = h->prox;
    }
    while(t->x.linha==c.linha) t=t->prox;
    jogar(e, t->x);
}

