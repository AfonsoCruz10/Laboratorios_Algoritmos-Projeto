#include "interface.h"
#include "logica.h"
#include "dados.h"
#include <assert.h>
#define BUF_SIZE 1024


// Função que deve ser colocada no ficheiro main.c
int main() {
    ESTADO *e = inicializar_estado();
    interpretador(e);
    return 0;
}
void testes (int expected, int actual, const char* nome){
    if (expected==actual)
        printf("\nteste da funcao %s verificou-se com sucesso\n", nome);
    else printf("\na funcao %s falhou no teste\n", nome);
}

int principal() {
    int z;
    ESTADO *v1 = inicializar_estado();
    v1->ultima_jogada.linha = 7;
    v1->ultima_jogada.coluna = 0;
    v1->jogador_atual = 1;
    COORDENADA x;
    x.linha = 4;
    x.coluna = 3;
    ESTADO *e = inicializar_estado();
    z=vitoria(v1);
    testes(1,z,"vitoria");
    z=validar(e,x);
    testes(1,z,"validar");
    z=lista_esta_vazia(NULL);
    testes(1,z,"lista_esta_vazia");
}