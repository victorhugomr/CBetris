/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Computacao Basica – 1/2015
Aluno(a): Victor Hugo Magalhaes Rodrigues
Matricula: 140087711
Turma: C
Versão do compilador: Code::Blocks 13.12
Descricao: CBetris*/

#ifdef _WIN64
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LeSequencia(FILE *fp, char MAT[100][8]){
int nseq;

    nseq=0;
    while(fscanf(fp,"%s",MAT[nseq]) > 0){
        nseq++;
    }
}/*le o arquivo e armazena cada string na matriz MAT*/

int InsereSequencia(char JOGO[15][20], char MAT[100][8], int cont_l){
int i, c,l;
char PECA[8];

    for(l=0;l<6;l++){
        for(c=0;c<20;c++){
            JOGO[l][c]=' ';
        }
    }
    strcpy(PECA,MAT[cont_l]);
    for(i=0;i<strlen(PECA);i++){
        JOGO[i][10]=PECA[i];
    }
    cont_l+=1;
    return cont_l;
}/*insere a sequencia na matriz JOGO*/

void MostraTela(){
int i;

    system(CLEAR);
    printf("  +-------CBetris------+\n\n\n");
    printf("  +--------------------+\n");
    for(i=0;i<=5;i++){
        printf("  |                    |\n");
    }
    printf("=>+                    +<=\n");
    for(i=0;i<=7;i++){
        printf("  |                    |\n");
    }
    printf("  +--------------------+\n");
    printf("Tecle <enter> para iniciar o jogo");
    getchar();
}/*mostra a tela inicial*/

void Tela(char a[15][20], int b){
int i,j;

    system(CLEAR);
    printf("  +-------CBetris------+\n\n\n");
    printf("  +--------------------+     PONTUACAO: %d\n", b);
    for(i=0;i<15; i++){
        if(i==6){
            printf("=>+");
        }
        else{
            printf("  |");
        }
        for(j=0;j<20;j++){
            printf("%c",a[i][j]);
        }
        if(i==6){
            printf("+<=\n");
        }
        else{
            printf("|\n");
        }
    }
    printf("  +--------------------+\n");
    printf("R-rotar D-direita E-esquerda C-cair\n");
    printf("ACAO: ");
}/*mostra a tela com a matriz JOGO*/

void Tela2(char a[15][20], int b){
int i,j;

    system(CLEAR);
    printf("  +-------CBetris------+\n\n\n");
    printf("  +--------------------+     PONTUACAO: %d\n", b);
    for(i=0;i<15; i++){
        if(i==6){
            printf("=>+");
        }
        else{
            printf("  |");
        }
        for(j=0;j<20;j++){
            printf("%c",a[i][j]);
        }
        if(i==6){
            printf("+<=\n");
        }
        else{
            printf("|\n");
        }
    }
    printf("  +--------------------+\n");
}

void GameOver(char JOGO[15][20],int *flag,int *tot_pontos,int *cont_l){
int l,c,i;

    for(i=0;i<20;i++){
        if(JOGO[6][i]!=' '){
            *flag=0;
            for(l=0;l<15;l++){
                for(c=0;c<20;c++){
                    JOGO[l][c]='X';

                }
            }
        }
    }
    if(*flag==0){
    Tela2(JOGO,*tot_pontos);
    printf("YOU LOSE!\n");
    printf("Tecle <enter> para sair");
    getchar();
    }
}/*verifica as condicoes para o jogo terminar*/

void Verifica(char JOGO[15][20],int *tot_pontos){
int i,j, c,l, cheio;

    for(l=6;l<15;l++){
            cheio=0;
        for(c=0;c<20;c++){
            if(JOGO[l][c]!=' '){
                cheio=cheio+1;
            }
        }
        if(cheio==20){
            *tot_pontos+=100;
            for(i=0;i<20;i++){
                JOGO[l][i]='X';
            }
            for(j=l;j>6;j--){
                for(i=0;i<20;i++){
                    JOGO[j+1][i]=JOGO[j][i];
                }
            }
        }
    }
}/*verifica se a linha esta cheia e limpa*/

void Cai(char JOGO[15][20], char MAT[100][8], int *cont_l, int *posicao, int *sentido){
int c,l,parou;

parou=0;
    if(*sentido==0){
        for(l=0;l<15;l++){
            if(JOGO[l][*posicao]==' '){
                JOGO[l][*posicao]=JOGO[l-1][*posicao];
                JOGO[l-strlen(MAT[*cont_l-1])][*posicao]=' ';
            }
        }
    }
    else{
        for(l=0;l<15;l++){
            for(c=*posicao;c<*posicao+strlen(MAT[*cont_l-1]);c++){
                if(JOGO[l+1][c]!=' '){
                    parou=1;
                }
            }
            if(parou!=1){
                for(c=*posicao;c<*posicao+strlen(MAT[*cont_l-1]);c++){
                    JOGO[l+1][c]=JOGO[l][c];
                    JOGO[l][c]=' ';
                }
            }
        }
    }
}/*funcao que faz a peca cair*/

void Rotaciona(char JOGO[15][20], char MAT[100][8], int *cont_l, int *posicao, int *sentido){
int c,l;

   if(*sentido==0){
        if(*posicao+strlen(MAT[*cont_l-1])<21){
            for(l=0;l<6;l++){
                for(c=0;c<20;c++){
                    JOGO[l][c]=' ';
                }
            }
            for(c=0;c<strlen(MAT[*cont_l-1]);c++){
                JOGO[0][c+*posicao]=MAT[*cont_l-1][c];
            }
            *sentido=1;
        }
    }
    else{
        for(l=0;l<6;l++){
            for(c=0;c<20;c++){
                JOGO[l][c]=' ';
            }
        }
        for(c=0;c<strlen(MAT[*cont_l-1]);c++){
            JOGO[c][*posicao]=MAT[*cont_l-1][c];
        }
        *sentido=0;
    }
}/*funcao que gira a peca*/

void Direita(char JOGO[15][20], int *posicao, int *sentido){
int c,l;

    if(JOGO[0][19]!=' '){
    }
    else{
        if(*posicao<19){
            *posicao=*posicao+1;
            for(l=5;l>=0;l--){
                for(c=19;c>=0;c--){
                    JOGO[l][c+*posicao]=JOGO[l][c+*posicao-1];
                    JOGO[l][c+*posicao-1]=' ';
                }
            }
        }
    }
}/*funcao que move a peca para a direita*/

void Esquerda(char JOGO[15][20], int *posicao){
int c,l;

    if(*posicao>0){
        *posicao=*posicao-1;
        for(l=0;l<6;l++){
            for(c=0;c<20;c++){
                if(c+*posicao>-1){
                    JOGO[l][c+*posicao]=JOGO[l][c+*posicao+1];
                    JOGO[l][c+*posicao+1]=' ';
                }
            }
        }
    }
}/*funcao que move a peca para a esquerda*/

int LeAcao(char JOGO[15][20], char MAT[100][8], int cont_l, int b){
int posicao, sentido;
char acao;

posicao=10;
sentido=0;

    scanf("%c",&acao);
    while((acao!='c') && (acao!='C')){
        if((acao=='d') || (acao=='D')){
            Direita(JOGO,&posicao,&sentido);
            Tela(JOGO,b);
        }
        else{
            if((acao=='e') || (acao=='E')){
                Esquerda(JOGO,&posicao);
                Tela(JOGO,b);
            }
            else{
                if((acao=='r') || (acao=='R')){
                    Rotaciona(JOGO,MAT,&cont_l,&posicao,&sentido);
                    Tela(JOGO,b);
                }
            }
        }
        Tela(JOGO,b);
        scanf("%c",&acao);
    }
    Cai(JOGO,MAT,&cont_l,&posicao,&sentido);
    return (posicao);
}/*funcao que le e executa a acao ate a peca cair*/

int main(){
int l,c, flag, cont_l, tot_pontos;
char JOGO[15][20], MAT[100][8];

    FILE *fp;
    fp = fopen("sequencias.txt","r");

    for(l=0;l<15;l++){
        for(c=0;c<20;c++){
            JOGO[l][c]=' ';
        }
    }
    LeSequencia(fp,MAT);
    fclose(fp);

    MostraTela();
    tot_pontos=0;
    cont_l=0;
    flag=1;
    while(flag){
        cont_l=InsereSequencia(JOGO,MAT,cont_l);
        Tela(JOGO,tot_pontos);
        LeAcao(JOGO,MAT,cont_l,tot_pontos);
        Verifica(JOGO,&tot_pontos);
        GameOver(JOGO,&flag,&tot_pontos,&cont_l);
        if(cont_l==70){
            flag=0;
            Tela2(JOGO,tot_pontos);
            printf("PARABENS!!! VOCE CHEGOU AO FIM DO JOGO COM %d PONTOS", tot_pontos);
            getchar();
        }
    }/*loop principal do jogo*/
    getchar();

return 0;
}
