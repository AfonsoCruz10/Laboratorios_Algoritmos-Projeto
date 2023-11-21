Projeto_LA1

Implementação do jogo de tabuleiro rastros em c.

LCC PL3
GRUPO 6 
a91651 André Luis Ramos Pereira; 
a91639 Afonso Brandao Cruz; 
a91655 Luis Filipe Vieira Rodrigues; 

Enunciado do Projeto

Laboratório de Algoritmia I
Ano letivo 2019/20

Constituição dos grupos

Os grupos deverão ser de 3 elementos, pertencendo todos ao mesmo turno prático.
A constituição dos grupos deverá ser comunicada ao docente nas aulas da semana de 2 e 6 de Março através de uma folha com os números dos alunos e os nomes completos.
O projeto será avaliado nas aulas da semana de 4 a 8 de Maio.

Descrição

Pretende-se implementar o jogo Rastros. Para descobrir as regras do jogo, clique aqui. O seu programa deverá permitir que dois jogadores, partilhando o mesmo teclado, o possam jogar. Os comandos deverão ser introduzidos através de um interpretador de comandos.

Interpretador de comandos

O seu programa deverá funcionar como um interpretador de comandos. Esta estratégia costuma ser chamada REPL (Read, Evaluate, Print, Loop). O seu interpretador deverá responder aos seguintes comandos:

coordenada: 
Tal como nas coordenadas de um tabuleiro de Xadrez: uma letra (a coluna) seguida de um algarismo (a linha). Neste caso, o programa deverá efetuar essa jogada desde que ela seja válida.
gr nome_do_ficheiro: 
O programa deverá gravar o estado do tabuleiro num ficheiro
ler nome_do_ficheiro: 
O programa deverá ler o estado do tabuleiro a partir do ficheiro
movs: 
O programa deverá imprimir a lista dos movimentos do jogo
jog: 
O seu programa deverá escolher a melhor jogada para o jogador atual
pos numero_da_jogada: 
O seu programa deverá permitir visualizar uma posição anterior através do seu número.
Q: 
O programa deverá acabar

Formato do ficheiro

O formato do ficheiro deve ser o seguinte:

O estado do tabuleiro
Uma linha em branco
A lista de movimentos
Formato do estado do tabuleiro
O estado do tabuleiro deverá ser de oito linhas. Cada casa vazia contém um ponto, uma casa de uma jogada antiga um cardinal e a casa atual um asterisco. Para ajudar a reconhecer as posições vencedoras, o canto inferior esquerdo contém um 1 (posição vencedora para o jogador 1) enquanto que o canto superior direito contém um 2. Assim, a configuração inicial deve ser a seguinte:

.......2
........
........
....*...
........
........
........
1.......
Se o jogador 1 jogar d4, a posição passaria a ser:

.......2
........
........
....#...
...*....
........
........
1.......
Lista de movimentos
A lista de movimentos deverá ser dada por tantas linhas como jogadas. Cada linha começa com o número da jogada (sempre com dois algarismos) seguida dos movimentos de cada jogador. Assim se os jogadores fizeram os seguintes movimentos: d4, e4, e3, a lista de movimentos seria a seguinte:

01: d4 e4
02: e3
Exemplo completo
Segue um exemplo completo do estado do ficheiro onde foram executados os seguintes comandos:

d4
e4
e3
f4
f3
gravar pos
A seguir a estes comandos, este deveria ser o conteúdo do ficheiro pos:

.......2
........
........
....#...
...###..
....#*..
........
1.......

01: d4 e4
02: e3 f4
03: f3
Visualização de posições anteriores
A visualização de posições anteriores será feita conforme o número da jogada, sendo 0 a posição inicial. Usando o exemplo completo da secção anterior, o comando pos 2 deveria mostrar o seguinte tabuleiro:

.......2
........
........
....#...
...##*..
....#...
........
1.......
Bot
A título de bonificação, os grupos que quiserem deverão submeter o seu programa para um torneios. Cada programa deverá:

Ler o estado do jogo a partir de um ficheiro. O nome desse ficheiro deverá ser passado como parâmetro ao programa;
Efetuar a melhor jogada no menor tempo possível;
Gravar o estado do jogo num ficheiro. O nome desse ficheiro deverá ser passado como parâmetro ao programa.
Assim, se o programa for invocado da seguinte forma:

./bot jog01 jog02
Então ele deverá ler o estado do ficheiro jog01, jogar e gravar o estado no ficheiro jog02.

Torneio
O torneio funcionará com as seguintes regras:

Para participar no torneio, será necessário:
Criar o bot
O bot deverá respeitar o formato do ficheiro
Caso um bot não faça uma jogada válida, ele perde automáticamente o jogo
Caso um bot não faça uma jogada em 1 segundo de CPU, ele perde automáticamente o jogo
Serão sorteados aleatóriamente jogos entre dois jogadores
Cada jogo sera eliminatório, isto é, só o vencedor passará à fase seguinte
A avaliação do torneiro é feita da seguinte forma:
