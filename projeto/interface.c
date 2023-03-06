//
// Created by luisf on 3/11/2020.
//
#include <stdio.h>
#include "interface.h"
#include "logica.h"
#include "dados.h"
#include <string.h>
#include <math.h>

#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e) {
    int i,j,k=8;
    for (i=0; i<8; i++) {
        printf("%d", k);
        for (j=0; j<8; j++) {
            if (e->tab [i] [j] == VAZIO) {
                printf(" .");
            }
            else if (e->tab [i] [j] == BRANCA) {
                printf(" #");
            }
            else if (e->tab [i] [j] == PRETA) {
                printf (" *");
            }
            else if (e->tab[i][j] == UM) {
                printf(" 1");
            }
            else printf(" 2");
        }
        printf("\n");
        k--;
    }
    printf("  a b c d e f g h");
}


int prompt(ESTADO *e) {
    int a,b;
    a=e->jogador_atual;
    b=e->num_jogadas;
    printf(" \nJOGADOR : %d | NUMERO DE JOGADAS : %d \n", a , b );
    return 0;
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

void movs(ESTADO *e, char nome[]){
    FILE *mov;
    mov = fopen(nome, "w");
    if (mov == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    aux(mov,e);
    fclose(mov);
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
        printf("nao da");
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


ESTADO* pos(ESTADO *e, int n) {
  ESTADO *f;
  f=inicializar_estado();
  for(int i=0; i<n;i++) {
      if(i>=e->num_jogadas) return f;
      jogar(f,e->jogadas[i].jogador1);
      jogar(f,e->jogadas[i].jogador2);
  }
  return f;
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

void jog1(ESTADO *e) {
    bot_fraco(e,JP(e));
}


void jog2(ESTADO *e) {
    bot_medio(e,JP(e));
}


int interpretador(ESTADO *e) {
    int x = 0;
    char s[100],nome[100];
    COORDENADA c;
    while (x == 0) {
        prompt(e);
        mostrar_tabuleiro(e);
        do {
            scanf("%s", s);
            if (s[0]=='p'&& s[1]=='o' && s[2]=='s'){
                int n;
                if ((s[4]<48 || s[4]>57) && s[4]!=0)  n = (s[3]-48)*10+s[4]-48;
                else n=s[3]-48;
                if(e->num_jogadas<n) return n;
                ESTADO *f;
                n+=1;
                while(n>0) {
                    f = pos(e, n-1);
                    n = interpretador(f);
                }
                return 0;
            }
            if (s[0] == 'q') return 0;
            if (s[0] == 'l' && s[1] == 'e' && s[2] == 'r') {
                for (int i = 4,j=0; s[i] != 0; ++i, ++j) {
                    nome[j]=s[i];
                }
                ler(e,nome);
                interpretador(e);
                return 0;
            }
            if (s[0]=='g' && s[1]=='r') {
                for (int i = 4,j=0; s[i] != 0; ++i, ++j) {
                    nome[j]=s[i];
                }
                gravar(e,nome);
                return 0;
            }
            if (s[0] == 'm' && s[1] == 'o' && s[2] == 'v') {
                for (int i = 4,j=0; s[i] != 0; ++i, ++j) {
                    nome[j]=s[i];
                }
                movs(e, nome);
                return 0;
            }
            if (s[0] == 'j' && s[1] == 'o' && s[2] == 'g' && s[3] =='1') {
                jog1(e);
                if (vitoria(e)) return 0;
                interpretador(e);
                return 0;
            }
             if (s[0] == 'j' && s[1] == 'o' && s[2] == 'g' && s[3] =='2') {
                jog2(e);
                if (vitoria(e)) return 0;
                interpretador(e);
                return 0;
            }
            c.coluna = (s[0] - 97);
            c.linha = 8 - (s[1] - 48);
        } while (!validar(e,c));
        jogar(e, c);
        e->ultima_jogada = c;
        x = vitoria(e);
    }
}