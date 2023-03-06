#include <stdio.h>
#include "bot.h"

int main(){
    ESTADO *e;
    char s[100] = "",nomeler[100],nomegr[100];
    if(s[10]=='1') {
        nomeler[0] = 'j';
        nomeler[1] = 'o';
        nomeler[2] = 'g';
        nomeler[3] = '0';
        nomeler[4] = '2';
        nomegr[0] = 'j';
        nomegr[1] = 'o';
        nomegr[2] = 'g';
        nomegr[3] = '0';
        nomegr[4] = '1';
        ler(e,nomeler);
        bot_medio(e,JP(e));
        gravar(e,nomegr);
    }
    else if(s[10]=='2') {
        nomeler[0] = 'j';
        nomeler[1] = 'o';
        nomeler[2] = 'g';
        nomeler[3] = '0';
        nomeler[4] = '1';
        nomegr[0] = 'j';
        nomegr[1] = 'o';
        nomegr[2] = 'g';
        nomegr[3] = '0';
        nomegr[4] = '2';
        ler(e,nomeler);
        bot_medio(e,JP(e));
        gravar(e,nomegr);
    }
    return 0;
}
