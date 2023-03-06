//
// Created by andre on 03-05-2020.
//

#include "bot.h"
#include <stdio.h>
#include <stdlib.h>


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



void gr_jogada(ESTADO *e, COORDENADA c) {
    int b;
    b = e->num_jogadas;
    if (e->jogador_atual == 1) {
        e->jogadas[b-1].jogador2 = c;
    } else {
        e->jogadas[b-1].jogador1 = c;
    }
}


void aux(FILE *mov,ESTADO *e) {
    int i,b;
    char a;
    for (i = 0; i < e->num_jogadas; i++) {
        if(i<9) fprintf(mov,"0");
        a = 97 + e->jogadas[i].jogador1.coluna;
        b = 8 - e->jogadas[i].jogador1.linha;
        fprintf(mov,"%d: %c%d ", i+1,a,b);
        if(e->jogador_atual==2 && i==e->num_jogadas-1)
            return;
        a = 97 + e->jogadas[i].jogador2.coluna;
        b = 8 - e->jogadas[i].jogador2.linha;
        fprintf(mov,"%c%d\n", a,b);
    }
}

void ler(ESTADO *e,char nome[]){
    FILE *arq;
    char x[100][100];
    int i,j,k=0;
    arq = fopen(nome ,"r");
    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    i = 0;
    while (!feof(arq)){
        fgets(x[i], 100, arq);
        i++;
    }
    for(i=0;i<8;i++) {
        for (j = 2,k = 0; j < 17; j+=2,k++) {
            if (x[i][j] == '*') e->tab[i][k] = PRETA;
            else if (x[i][j] == '#') {
                e->tab[i][k] = BRANCA;
                e->ultima_jogada.linha=i;
                e->ultima_jogada.coluna=k;
            }
            else if (x[i][j] == '1') e->tab[i][k] = UM;
            else if (x[i][j] == '2') e->tab[i][k] = DOIS;
            else if (x[i][j] == '.') e->tab[i][k] = VAZIO;
        }
    }
    i=i+2;
    COORDENADA c;
    for(;x[i][0];i++){
        e->jogador_atual = 2;
        e->num_jogadas = (x[i][0]-48)*10 + (x[i][1]-48);
        c.linha = 8-(x[i][5]-48);
        c.coluna = x[i][4]-97;
        gr_jogada(e,c);
        if (x[i][7]){
            e->jogador_atual = 1;
            c.linha = 8-(x[i][8]-48);
            c.coluna = x[i][7]-97;
            gr_jogada(e,c);
        }
    }
    fclose(arq);
}


void gravar(ESTADO *e, char *nome) {
    FILE *tab;
    tab=fopen(nome, "w");
    fseek(tab,0,SEEK_SET);
    if (tab==NULL) {
        printf("Ficheiro nao gravou!");
        return;
    }
    int i,j,k=8;
    for (i=0; i<8; i++) {
        fprintf(tab,"%d", k);
        for (j=0; j<8; j++) {
            if (e->tab [i] [j] == VAZIO) {
                fprintf(tab," .");
            }
            else if (e->tab [i] [j] == BRANCA) {
                fprintf(tab," #");
            }
            else if (e->tab [i] [j] == PRETA) {
                fprintf (tab," *");
            }
            else if (e->tab[i][j] == UM) {
                fprintf(tab," 1");
            }
            else fprintf(tab," 2");
        }
        fprintf(tab,"\n");
        k--;
    }
    fprintf(tab,"  a b c d e f g h\n\n");
    aux(tab,e);
    fflush(tab);
    fclose(tab);
}

LL JP(ESTADO *e) {
    LL t = NULL;
    COORDENADA c = e->ultima_jogada;
    COORDENADA d = c;
    if (validar_bot(e, c.linha + 1, c.coluna - 1)) {
        d.linha += 1;
        d.coluna -= 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    if (validar_bot(e, c.linha + 1, c.coluna)) {
        d.linha += 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    if (validar_bot(e, c.linha, c.coluna - 1)) {
        d.coluna -= 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    if (validar_bot(e, c.linha - 1, c.coluna - 1)) {
        d.linha -= 1;
        d.coluna -= 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    if (validar_bot(e, c.linha + 1, c.coluna + 1)) {
        d.linha += 1;
        d.coluna += 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    if (validar_bot(e, c.linha - 1, c.coluna)) {
        d.linha -= 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    if (validar_bot(e, c.linha, c.coluna + 1)) {
        d.coluna += 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    if (validar_bot(e, c.linha - 1, c.coluna + 1)) {
        d.linha -= 1;
        d.coluna += 1;
        t = insere_cabeca(d, t);
        d = c;
    }
    return t;
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

int obter_jogador_atual(ESTADO *e){
    if (e->jogador_atual==1) e->jogador_atual=2;
    else e->jogador_atual=1;
    return 0;
}


int obter_numero_de_jogadas(ESTADO *e){
    if (e->jogador_atual==2) {
        e->num_jogadas++;

    }
    return 0;
}

LL insere_cabeca (COORDENADA v, LL t){
    LL new = (LL) malloc (sizeof (struct lligada));
    if (new!=NULL) {
        new-> x = v;
        new-> prox  = t;
    }
    return new;
}

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