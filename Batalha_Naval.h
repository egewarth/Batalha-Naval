#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//declaração de tamanhos padrões
#define MAX 10
#define CHAR_UPPER 65
#define CHAR_LOWER 97
#define STOP 3
#define CHAR_ESPACO 10
#define CHAR_ENTER 32
#define CHAR_CEDILHA 135
#define CHAR_ATIO 198
#define CHAR_TIO 126
#define CHAR_AAGUDO 160
#define STOP 3
#define WIN 1
#define TRUE 1
#define FALSE 0
#define MAX_SIZE_OF_STRING 50

//Definicoes de mapa
#define PRIMEIRA_LINHA 1
#define LINHA_MEIO 2
#define ULTIMA_LINHA 3


#define PORTA_AVIAO 5
#define QUANTIDADE_PORTA_AVIAO 1
#define ENCOURACADO 3
#define QUANTIDADE_ENCOURACADO 2
#define CRUZADOR 2
#define QUANTIDADE_CRUZADOR 2
#define SUBMARINO 1
#define QUANTIDADE_SUBMARINO 10
#define QUANTIDADE_JOGOS_SALVOS 5
#define TAMANHO_NOME_JOGO 10
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef unsigned short int intizinho;
 
typedef struct mapas{
    /*declaração da estrutura de mapas, contendo o mapa do jogador(mapa_player), 
    o mapa do inimigo que será mostrado e alterado(mapa_partida_inimigo) 
    e o mapa do inimigo que não será mostrado, contendo seus embarcacoes*/
	char player[MAX][MAX];
	char inimigo[MAX][MAX];
	char partida_inimigo[MAX][MAX];
}MapaJogo;

typedef struct coordenada{
    unsigned char x;
    intizinho y;
}Coordenada;

typedef struct embarcacao{
    intizinho tipo;
    Coordenada polpa;
    Coordenada proa;
}Embarcacao;

typedef struct jogo{
    char nome[TAMANHO_NOME_JOGO];
    intizinho turno;
    MapaJogo mapa;
}Jogo;
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//declaração das funções usadas no jogo
void imprime_coordenadas_x(intizinho tamanho);
void posicao_navio (char mapa[][MAX]);
void imprimir_mapa (char mapa[][MAX]);
void inicia_mapa(MapaJogo* mapa);
void jogos_salvos();
void novo_jogo();
void posicao_bomba();
void imprime_menu_principal();
intizinho menu_principal();
//---------------------------------------------------------------------------------------------------------------------------------------------------
void pause(){
    fflush(stdin);
    getchar();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void inicia_mapa(MapaJogo *mapa){
    //função para iniciar o mapa com todos os espaços iguais a '~' (agua)
	intizinho i=0,j=0;
	for(i=0;i<MAX;i++){
		for (j=0;j<MAX;j++){
			mapa->player[i][j] = '~';
			mapa->inimigo[i][j] = '~';
			mapa->partida_inimigo[i][j] = ' '; 
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void batalha_naval_inicio(){
    char inicio[MAX][MAX];
    intizinho i=0,j=0;
    for(i=0;i<MAX;i++){
		for (j=0;j<MAX;j++){
			inicio[i][j] = '~';
		}
	}
	inicio[2][1] = '\0';
	strcat(inicio[2], "BATALHA");
	inicio[2][8] = '~';
	inicio[3][2] = '\0';
	strcat(inicio[3], "NAVAL");
	inicio[3][7] = '~';
	inicio[6][2] = 220;
	inicio[6][3] = 219;
	inicio[6][4] = 220;
	for (i=7,j=1;j<9;j++){
		inicio[i][j] = 219;
	}
	for (i=8,j=2;j<8;j++){
		inicio[i][j] = 223;
	}
	imprimir_mapa(inicio);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_comando_polpa(const intizinho tipo){
    /*função para imprimir mensagem do que o jogador estara inserindo no mapa(polpa e submarino)*/
    switch(tipo){
        case PORTA_AVIAO:
            printf ("Indique as Coordenadas da polpa do seu Porta-Avi%co:\n", CHAR_ATIO);
            break;
        case ENCOURACADO:
            printf ("Indique as Coordenadas da polpa do seu Encoura%cado:\n", CHAR_CEDILHA);
            break;
        case CRUZADOR:
            printf ("Indique as Coordenadas da polpa do seu Cruzador:\n");
            break;
        case SUBMARINO:
            printf ("Indique as Coordenadas do seu Submarino:\n");
            break;
        default:
            //nothing
            break;
   }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_comando_proa(const unsigned short int tipo){
    /*função para imprimir mensagem do que o jogador estara inserindo no mapa(proa)*/
    switch(tipo){
        case PORTA_AVIAO:
            printf ("Indique as Coordenadas da proa do seu Porta-Avi%co:\n", CHAR_ATIO);
            break;
        case ENCOURACADO:
            printf ("Indique as Coordenadas da proa do seu Encoura%cado:\n", CHAR_CEDILHA);
            break;
        case CRUZADOR:
            printf ("Indique as Coordenadas da proa do seu Cruzador:\n");
            break;
        default:
            //nothing
            break;
   }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
char caracter_embarcacao(const intizinho tipo_embarcacao){
    char tipo;
    switch(tipo_embarcacao){
        case PORTA_AVIAO:
            tipo='P';
            break;
        case ENCOURACADO:
            tipo='E';
            break;
        case CRUZADOR:
            tipo='C';
            break;
        case SUBMARINO:
            tipo='S';
            break;
        default:
            printf("ERRO INESPERADO!");
            pause();
            exit(0);
    }
    return tipo;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_menu_principal(){
	system("clear || cls");
	printf("\tBatalha Naval\n\n");
	printf("[1] Novo Jogo\n");
	printf("[2] Carregar Jogo\n");
	printf("[3] Sair\n\n");
	return;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
intizinho menu_principal(){
	intizinho opcao=0;
	imprime_menu_principal();
	scanf("%hi", &opcao);
	fflush(stdin);
	return opcao;
}
