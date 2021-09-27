#include <stdio.h>//Biblioteca padrão.
#include <stdlib.h>//Biblioteca possue funções para a alocação dinâmica de memória.
#include <time.h>//Biblioteca para auxiliar a gerar números aleatórios.
#include <string.h>//Biblioteca para strings.
#include <ctype.h>//Biblioteca para algumas peculiaridades da entrada de dados a partir do teclado.

#define LINHAS 8//Dimensões do tabuleiro: 8 x 8.
#define COLUNAS 8

#define PRETO 1//Peça Preta.
#define BRANCO -1//Peça Branca.
#define VAZIO 0//Vazio no tabuleiro.
#define JOGADA 2//Jogada possível no tabuleiro.

typedef struct dados{//Armazena as informações de cada jogador.

    char nome[20], sexo[10];
    int idade, pontuacao, cor;
}CADASTRO;

void sortearCor(CADASTRO *jogador, int *turno){//Inicialmente o jogo deve sortear de forma aleatória qual a cor da peça para cada um dos jogadores.

    srand(time(NULL));

    printf("\n> Sorteando a cor da peca para cada um dos jogadores...\n");

    *turno = 1 + rand() % 2;//Gera aleatoriamente 1 ou 2.

    if(*turno == 1){//Resultado 1: J1 jogará com a cor preta e J2 com a cor branca.
        printf("\njogador 1: Pecas Preta\njogador 2: Pecas Branca\n");
        jogador[0].cor = PRETO;
        jogador[1].cor = BRANCO;
    }

    else{//Resultado 2: J1 jogará com a cor branca e J2 com a cor preta.
        printf("\njogador 1: Pecas Branca\njogador 2: Pecas Preta\n");
        jogador[0].cor = BRANCO;
        jogador[1].cor = PRETO;
    }

    *turno -= 1;
}

void cadastrarjogador(CADASTRO *jogador){//Armazenar os dados de cada jogador: nome, idade, sexo, cor da peça e pontuação.

    printf("\n> Cadastrar dados de cada jogador...\n");

    for(int i = 0; i < 2; i++){

        printf("\n> jogador %d\n", i + 1);

        printf("Insira o nome: ");
        setbuf(stdin, NULL);
        gets(jogador[i].nome);

        printf("Insira a idade: ");
        scanf("%d", &jogador[i].idade);
        while(jogador[i].idade < 1){
            printf("Idade invalida! Insira a idade novamente: ");
            scanf("%d", &jogador[i].idade);
        }

        printf("Insira o sexo (M/F): ");
        setbuf(stdin, NULL);
        gets(jogador[i].sexo);
        strupr(jogador[i].sexo);
        while(jogador[i].sexo[0] != 'F' && jogador[i].sexo[0] != 'M'){
            printf("Caracter invalido! Insira novamente o sexo do %do. jogador (M/F): ", i + 1);
            setbuf(stdin, NULL);
            gets(jogador[i].sexo);
            strupr(jogador[i].sexo);
        }

        if(jogador[i].sexo[0] == 'F'){
            strcpy(jogador[i].sexo, "Feminino");
        }
        else{
            strcpy(jogador[i].sexo, "Masculino");
        }

        jogador[i].pontuacao = 0;//Inicia a pontuação com 0.
    }
}

void imprimirjogador(CADASTRO *jogador, int pos){//Exibe os dados do jogador.

    printf("\n> jogador %d", pos + 1);

    printf("\nNome: %s", jogador[pos].nome);
    printf("\nIdade: %d", jogador[pos].idade);
    printf("\nSexo: %s ",jogador[pos].sexo);
    printf("\nCor das Pecas: ");
    if(jogador[pos].cor == PRETO){
            printf("Preta");
    }
    else{
            printf("Branca");
    }
    printf("\nPontuacao: %d\n", jogador[pos].pontuacao);
}

void inicializarTabuleiro(int c[][COLUNAS]){//Inicia o tabuleiro de modo que são colocadas 4 peças ao centro do tabuleiro, duas de cada cor, em diagonais.

    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            if((i == 3 && j == 4) || (i == 4 && j == 3)){
                c[i][j] = PRETO;//Peça Preta.
            }
            else if((i == 3 && j == 3) || (i == 4 && j ==4)){
                c[i][j] = BRANCO;//Peça Branca.
            }
            else{
                c[i][j] = VAZIO;//Vazio.
            }
        }
    }
}

void imprimirTabuleiro(int c[][COLUNAS]){//Imprime o tabuleiro.

    printf("\n");

    for(int i = 0; i < LINHAS; i++){

        if(i == 0){
            for(int j = 0; j < COLUNAS; j++){
                if(j == 0){
                    printf("      ");
                }
                printf(" %d  ", j + 1);
            }
            printf("\n\n");
        }

        printf(" %d   |", i + 1);

        for(int j = 0; j < COLUNAS; j++){
            if(c[i][j] == PRETO){//Peça Preta. ●
                printf(" P |", c[i][j]);
            }
            else if(c[i][j] == BRANCO){//Peça Branca. ○
                printf(" B |", c[i][j]);
            }
            else if(c[i][j] == JOGADA){
                printf(" X |", c[i][j]);
            }
            else{//Vazio no tabuleiro.
                printf("   |", c[i][j]);
            }
        }
        printf("\n");
    }
}

void verificarLinha(int c[][COLUNAS], int cor, int linha, int coluna){//Verifica se há alguma jogada possível na linha informada.

    int aux;//Auxiliar, salvar a cor da peça analisada.

    for(int i = coluna + 1, aux = cor; i < COLUNAS; i++){//Da esquerda para direita.
        if(c[linha][i] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[linha][i] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[linha][i] == cor || c[linha][i] == VAZIO || c[linha][i] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[linha][i];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = coluna - 1, aux = cor; i >= 0; i--){//Da direita para esquerda.

        if(c[linha][i] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[linha][i] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[linha][i] == cor || c[linha][i] == VAZIO || c[linha][i] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[linha][i];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }
}

void verificarColuna(int c[][COLUNAS], int cor, int linha, int coluna){//Verifica se há alguma jogada possível na coluna informada.

    int aux;//Auxiliar, salvar a cor da peça analisada.

    for(int i = linha + 1, aux = cor; i < LINHAS; i++){//De cima para baixo.
        if(c[i][coluna] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[i][coluna] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[i][coluna] == cor || c[i][coluna] == VAZIO || c[i][coluna] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[i][coluna];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha - 1, aux = cor; i >= 0; i--){//De baixo para cima.
        if(c[i][coluna] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[i][coluna] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[i][coluna] == cor || c[i][coluna] == VAZIO || c[i][coluna] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[i][coluna];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }
}

void verificarDiagonal(int c[][COLUNAS], int cor, int linha, int coluna){//Verifica se há alguma jogada possível na diagonal informada.

    int aux;//Auxiliar, salvar a cor da peça analisada.

    for(int i = linha + 1, j = coluna + 1, aux = cor; i < LINHAS && j < COLUNAS; i++, j++){//Da esquerda para direita, cima para baixo.
        if(c[i][j] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[i][j] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO || c[i][j] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha - 1, j = coluna - 1, aux = cor; i >= 0 && j >= 0; i--, j--){//Da direita para esquerda, baixo para cima.
        if(c[i][j] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[i][j] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO || c[i][j] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha + 1, j = coluna - 1, aux = cor; i < LINHAS && j >= 0; i++, j--){//Da direita para esquerda, cima para baixo.
        if(c[i][j] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[i][j] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO || c[i][j] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha - 1, j = coluna + 1, aux = cor; i >= 0 && j < COLUNAS; i--, j++){//Da esquerda para direita, baixo para baixo.
        if(c[i][j] == VAZIO && aux != cor){//Caso o espaço atual esteja vazio e a cor da peça anterior seja do outro jogador...
            c[i][j] = JOGADA;//...marca como jogada possível, o jogador pode colocar sua peça em tal lugar.
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO || c[i][j] == JOGADA){
            break;//Caso seja uma peça igual, ou o lugar do lado esteja vazio ou um lugar já determinado como jogada.
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }
}

void jogadasTabuleiro(int c[][COLUNAS], int cor){//Exibe as possibilidades de jogada do jogador.

    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            if(c[i][j] == cor){
                verificarLinha(c, cor, i, j);
                verificarColuna(c, cor, i, j);
                verificarDiagonal(c, cor, i, j);
            }
        }
    }
}

void retirarJogadas(int c[][COLUNAS]){//Retira as jogadas possíves após uma já ter sido escolhida.

    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            if(c[i][j] == JOGADA){
                c[i][j] = VAZIO;
            }
        }
    }
}

void marcarTabuleiro(int c[][COLUNAS], int cor, int linha, int coluna){//Coloca a peça do jogador no tabuleiro e substitue as peças do adversário que foram cercadas.

    c[linha][coluna] = cor;//Insere a peça no lugar determinado pelo jogador.
    retirarJogadas(c);//Retira as jogadas possíves após uma já ter sido escolhida.

    int aux;//Auxiliar, salvar a cor da peça analisada.

    //Os 8 comandos de repetições abaixo verificam e substituem as devidas peças após o jogador ter feito sua jogada.
    //Ex.: O jogador com a peça preta fez uma jogada, logo verifica quais peças brancas devem se tornar preta.

    for(int i = coluna + 1, aux = cor; i < COLUNAS; i++){//LINHA - Da esquerda para direita.
        if(c[linha][i] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int j = coluna + 1; j <= i; j++){
                c[linha][j] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[linha][i] == cor || c[linha][i] == VAZIO){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[linha][i];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = coluna - 1, aux = cor; i >= 0; i--){//LINHA - Da direita para esquerda.
        if(c[linha][i] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int j = coluna - 1; j >= i; j--){
                c[linha][j] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[linha][i] == cor || c[linha][i] == VAZIO){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[linha][i];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha + 1, aux = cor; i < LINHAS; i++){//COLUNA - De cima para baixo.
        if(c[i][coluna] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int j = linha + 1; j <= i; j++){
                c[j][coluna] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[i][coluna] == cor || c[i][coluna] == VAZIO){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[i][coluna];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha - 1, aux = cor; i >= 0; i--){//COLUNA - De baixo para cima.
        if(c[i][coluna] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int j = linha - 1; j >= i; j--){
                c[j][coluna] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[i][coluna] == cor || c[i][coluna] == VAZIO){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[i][coluna];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha + 1, j = coluna + 1, aux = cor; i < LINHAS && j < COLUNAS; i++, j++){//DIAGONAL - Da esquerda para direita, cima para baixo.
        if(c[i][j] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int k = linha + 1, l = coluna + 1; k <= i && l <= j; k++, l++){
                c[k][l] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO ){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha - 1, j = coluna - 1, aux = cor; i >= 0 && j >= 0; i--, j--){//DIAGONAL - Da direita para esquerda, baixo para cima.
        if(c[i][j] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int k = linha - 1, l = coluna - 1; k >= i && l >= j; k--, l--){
                c[k][l] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha + 1, j = coluna - 1, aux = cor; i < LINHAS && j >= 0; i++, j--){//DIAGONAL - Da esquerda para direita, baixo para cima..
        if(c[i][j] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int k = linha + 1, l = coluna - 1; k <= i && l >= j; k++, l--){
                c[k][l] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    for(int i = linha - 1, j = coluna + 1, aux = cor; i >= 0 && j < COLUNAS; i--, j++){//DIAGONAL - Da direita para esquerda, cima para baixo.
        if(c[i][j] == cor && aux != cor){//Caso o espaço atual seja uma peça do jogador e a cor da peça anterior seja do outro jogador...
            for(int k = linha - 1, l = coluna + 1; k >= i && l <= j; k--, l++){
                c[k][l] = cor;//...substitue todas as peças que foram cercadas.
            }
            break;
        }
        else if(c[i][j] == cor || c[i][j] == VAZIO){//Caso seja uma peça igual ou o lugar do lado esteja vazio.
            break;
        }
        else{
            aux += c[i][j];//Salva a cor da peça atual, para ser usado na próxima vez que rodar o comando de repetição.
        }
    }

    printf("\n> Sua jogada foi feita!\n");

}

void contarPecas(int c[][COLUNAS], CADASTRO *jogador){//Contar a quantidade de peças de cada jogador.

    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            if(c[i][j] == jogador[0].cor){
                jogador[0].pontuacao++;
            }
            else{
                jogador[1].pontuacao++;
            }
        }
    }
}

void gerarRank(int c[][COLUNAS], CADASTRO *jogador){//Gera o ranking de acordo com a pontuação de cada jogador.

    contarPecas(c, jogador);//Contar a quantidade de peças de cada jogador.

    int rank[2];//Cria um vetor para armazenar a colocação de cada jogador. A posição no vetor é relativo a posição no rank.

    if(jogador[0].pontuacao > jogador[1].pontuacao){//Caso a pontução do jogador 1 seja maior que a do jogador 2.
        rank[0] = 0;//Jogador 1 em primeiro lugar.
        rank[1] = 1;//Jogador 2 em segundo lugar.
    }
    else if(jogador[0].pontuacao < jogador[1].pontuacao){//Caso a pontução do jogador 2 seja maior que a do jogador 1.
        rank[0] = 1;//Jogador 2 em primeiro lugar.
        rank[1] = 0;//Jogador 1 em segundo lugar.
    }
    else{//Caso haja empate entre os dois jogadores.
        printf("\n> EMPATE!\n");
        return;
    }

    for(int i = 0; i < 2; i++){//Exibe a colocação.

        printf("\n> %do. Lugar\n", i + 1);
        imprimirjogador(jogador, rank[i]);
    }
}

int main(){//Funcao principal.

    CADASTRO* jogador = (CADASTRO*) malloc(2 * sizeof(CADASTRO));//Cria duas struct cadastro de relativo a cada jogador.
    int turno, tabuleiro[LINHAS][COLUNAS], espacos_vazios = 60;//Armazena o primeiro a jogar, o tabuleiro e o número de espaços vazios.

    sortearCor(jogador, &turno);//Sorteia qual a cor da peça de cada jogador e consequemente qual irá começar.
    cadastrarjogador(jogador);//Armazena os dados dos jogadores.
    inicializarTabuleiro(tabuleiro);//Inicia o tabuleiro com as peças nas posições iniciais.

    printf("\n");
    system("pause");//Ambos os 3 para melhor visualização ao executar.
    system("cls");

    printf("\nO JOGO COMECOU - BOA SORTE!\n");

    while(espacos_vazios != 0){//Enquanto existir uma espaço vazio no tabuleiro, há jogadas, logo o jogo continua.

        printf("\n> jogador %d:\n", turno + 1);

        jogadasTabuleiro(tabuleiro, jogador[turno].cor);//Exibe as possibilidades de jogada do jogador.
        imprimirTabuleiro(tabuleiro);//Imprimi o tabuleiro.
        int linha, coluna;//Relativo a posição aonde o jogador deseja colocar sua peça.

        do{
            printf("\n> Insira a posicao que deseja colocar a sua peca: ");
            scanf("%d %d", &linha, &coluna);
            linha--, coluna--;//No tabuleiro as linhas e colunas são de 1 a 8, na matriz são de 0 a 7.

        }while(tabuleiro[linha][coluna] != JOGADA);//Enquanto não é inserido uma linha e coluna válida...

        marcarTabuleiro(tabuleiro, jogador[turno].cor, linha, coluna);//Coloca a peça do jogador no tabuleiro e substitue as peças do adversário que foram cercadas.
        imprimirTabuleiro(tabuleiro);//Imprimi o tabuleiro.

        if(turno == 0){//Rodada atual é do jogador 1.
            turno = 1;//Passa a rodada para o jogador 2.
        }
        else{//Rodada atual é do jogador 2.
            turno = 0;//Passa a rodada para o jogador 1.
        }

        espacos_vazios--;//Diminue o número de espaços vazios no tabuleiro a cada rodada.

        printf("\n");
        system("pause");//Ambos os 3 para melhor visualização ao executar.
        system("cls");
    }

    printf("\n> O JOGO ACABOU!\n");

    printf("\n");
    system("pause");//Ambos os 3 para melhor visualização ao executar.
    system("cls");

    printf("\n> GERANDO RANK!\n");

    gerarRank(tabuleiro, jogador);//Retorna a quantidade de peças pretas no tabuleiro.

    printf("\n");
    free(jogador);

    return 0;
}
