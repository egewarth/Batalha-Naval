//declaração de bibliotecas pré definidas pela linguagem
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
//declaração de tamanhos padrões
#define TEMPO_SLEEP 750
#define TEMPO_SLEEP_DICA 1000
#define MAX 10
//declaração  
#define CHAR_A_UPPER 65
#define CHAR_A_LOWER 97
#define CHAR_ESPACO 10
#define CHAR_ENTER 32
#define CHAR_CEDILHA 135
#define CHAR_ATIO 198
#define CHAR_TIO 126
#define CHAR_AAGUDO 160
#define CHAR_IACENTO 161
#define CHAR_ESC 27
//---------------------------------------------------------------------------------------------------------------------------------------------------
#define START 0
#define STOP 4
#define WIN 1
#define TRUE 1
#define FALSE 0
#define MAX_SIZE_OF_STRING 50
//Definicoes de mapa
#define PRIMEIRA_LINHA 1
#define LINHA_MEIO 2
#define ULTIMA_LINHA 3
#define MENU 4
//---------------------------------------------------------------------------------------------------------------------------------------------------
#define PORTA_AVIAO 5
#define QUANTIDADE_PORTA_AVIAO 1
#define ENCOURACADO 3
#define QUANTIDADE_ENCOURACADO 1
#define CRUZADOR 2
#define QUANTIDADE_CRUZADOR 1
#define SUBMARINO 1
#define QUANTIDADE_SUBMARINO 1
#define QUANTIDADE_JOGOS_SALVOS 5
#define TAMANHO_NOME_JOGO 10
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef unsigned short int intizinho; 
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct mapas{
    /*declaração da estrutura de mapas, contendo o mapa do jogador(mapa_player), 
    o mapa do inimigo que será mostrado e alterado(mapa_partida_inimigo) 
    e o mapa do inimigo que não será mostrado, contendo seus embarcacoes*/
	char player[MAX][MAX];
	char inimigo[MAX][MAX];
	char partida_inimigo[MAX][MAX];
}MapaJogo;
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct mapa{
    char partida_inimigo[MAX][MAX];
}Mapa;
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct coordenada{
    unsigned char x;
    intizinho y;
}Coordenada;
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct embarcacao{
    intizinho tipo;
    Coordenada popa;
    Coordenada proa;
}Embarcacao;
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct jogo{
    char nome[TAMANHO_NOME_JOGO];
    intizinho turno;
    MapaJogo mapa;
}Jogo;
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_coordenadas_x(intizinho tamanho);
void imprime_estrutura_linha_mapa(intizinho tipo_linha, intizinho tamanho);
void imprime_linha_mapa(intizinho linha, char *linha_mapa, intizinho tamanho);
void imprimir_mapa(char mapa[][MAX]);
void imprimir_mapa_partida(char mapa1[][MAX], char mapa2[][MAX]);
void imprime_menu_principal();
void imprime_menu_partida();
//---------------------------------------------------------------------------------------------------------------------------------------------------
void pause(){
    fflush(stdin);
    getchar();
}
void erro(char funcao[MAX_SIZE_OF_STRING], char tipo_erro[MAX_SIZE_OF_STRING]){
	printf("ERRO INESPERADO!");
	printf("Fun%c%co: %s\n", funcao);
	printf("Tipo de erro: %s\n", tipo_erro);
	pause();
	exit(0);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
char* completa_string(char *string, intizinho tamanho){
	intizinho i = 0, espacos = ((tamanho*2) - strlen(string))/2;
	free(string);
	string = (char*)calloc((espacos+1),sizeof(char));
	string[0] = '\0';
	for(i=0; i < espacos; i++){
		strcat(string, " ");
	}
	return string;
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
	printf("\n\tCARREGANDO\r");
	Sleep(TEMPO_SLEEP);
	printf("\tCARREGANDO.\r");
	Sleep(TEMPO_SLEEP);
	printf("\tCARREGANDO..\r");
	Sleep(TEMPO_SLEEP);
	printf("\tCARREGANDO...\r");
	Sleep(TEMPO_SLEEP);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_comando_popa(const intizinho tipo){
    /*função para imprimir mensagem do que o jogador estara inserindo no mapa(popa e submarino)*/
    printf("\n");
	switch(tipo){
        case PORTA_AVIAO:
            printf ("Indique as Coordenadas(Ex:A2) da popa do seu Porta-Avi%co - %d casas:\n", CHAR_ATIO, tipo);
            break;
        case ENCOURACADO:
            printf ("Indique as Coordenadas(Ex:D9) da popa do seu Encoura%cado - %d casas:\n", CHAR_CEDILHA, tipo);
            break;
        case CRUZADOR:
            printf ("Indique as Coordenadas(Ex:J7) da popa do seu Cruzador - %d casas:\n", tipo);
            break;
        case SUBMARINO:
            printf ("Indique as Coordenadas(Ex:H3) do seu Submarino - %d casa:\n", tipo);
            break;
        default:
			erro("imprime_comando_popa()", "Tipo da Embarcacao nao existe!");
            break;
   }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_comando_proa(const intizinho tipo){
    /*função para imprimir mensagem do que o jogador estara inserindo no mapa(proa)*/
    printf("\n");
	switch(tipo){
        case PORTA_AVIAO:
            printf ("Indique as Coordenadas(Ex:A6) da proa do seu Porta-Avi%co - %d casas:\n", CHAR_ATIO, tipo);
            break;
        case ENCOURACADO:
            printf ("Indique as Coordenadas(Ex:D7) da proa do seu Encoura%cado - %d casas:\n", CHAR_CEDILHA, tipo);
            break;
        case CRUZADOR:
            printf ("Indique as Coordenadas(Ex:J8) da proa do seu Cruzador - %d casas:\n", tipo);
            break;
        case SUBMARINO:
            erro("imprime_comando_proa()", "Opcao invalida para Submarinos!");
            break;
        default:
            erro("imprime_comando_proa()", "Tipo da Embarcacao nao existe!");
            break;
   }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_menu_principal(){
	system("clear || cls");
	intizinho tamanho = MAX;
	char *espacos_vazios=NULL;
	putchar('\n');
	imprime_estrutura_linha_mapa(PRIMEIRA_LINHA+MENU, tamanho);
	putchar('\n');
	espacos_vazios = completa_string("Batalha Naval", tamanho);
	printf("  %c%sBatalha Naval%s%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[1] Novo Jogo", tamanho);
	printf("  %c[1] Novo Jogo%s%s%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[2] Jogos Salvos", tamanho);
	printf("  %c[2] Jogos Salvos\b%s%s%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[3] Ranking", tamanho);
	printf("  %c[3] Ranking%s%s%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[%d] Sair", tamanho);
	printf("  %c[%d] Sair%s%s %c\n", 186, STOP, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(ULTIMA_LINHA+MENU, tamanho);
	putchar('\n');
	return;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_coordenadas_x(intizinho tamanho){
    char coordenadas[MAX_SIZE_OF_STRING], parte_coordenada[3], letra = '\0';
    strcpy(coordenadas,"  ");
    strcpy(parte_coordenada, " ");
    parte_coordenada[2] = '\0';
    for (letra = CHAR_A_UPPER;letra < (tamanho+CHAR_A_UPPER); letra++){
        parte_coordenada[1] = letra;
        strcat(coordenadas, parte_coordenada);
	}
	strcat(coordenadas, "  ");
	printf("%s", coordenadas);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_linha_mapa(intizinho linha, char *linha_mapa, intizinho tamanho){
    intizinho j=0;
    printf(" %d%c",linha, 186);
	for (j=0;j<(tamanho);j++){
		printf("%c%c",linha_mapa[j],186);
	}
	printf("%d", linha);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_estrutura_linha_mapa(intizinho tipo_linha, intizinho tamanho){
	char inicio = '\0', meio = '\0', fim = '\0';
	register intizinho j=0;
	switch(tipo_linha){
		case PRIMEIRA_LINHA:
			inicio = 201;
			meio = 203;
			fim = 187;
			break;
		case LINHA_MEIO:
			inicio = 204;
			meio = 206;
			fim = 185;
			break;
		case ULTIMA_LINHA:
			inicio = 200;
			meio = 202;
			fim = 188;			
			break;
		case (PRIMEIRA_LINHA+MENU):
			inicio = 201;
			meio = 205;
			fim = 187;
			break;
		case (LINHA_MEIO+MENU):
			inicio = 204;
			meio = 205;
			fim = 185;
			break;
		case (ULTIMA_LINHA+MENU):
			inicio = 200;
			meio = 205;
			fim = 188;			
			break;
		default:
			printf("ERRO INESPERADO!");
            pause();
            exit(0);		
	}
	
	printf("  %c", inicio);
	for (j=0;j<(tamanho-1);j++){
		printf("%c%c",205, meio);
	}
	printf("%c%c",205, fim);
	
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprimir_mapa (char mapa[][MAX]){
    /*imprime o mapa na tela, pode ser chamada tanto pra imprimir 
    o mapa do jogador quanto o mapa do inimigo*/
	register intizinho i=0,j=0;
	unsigned char letra=CHAR_A_UPPER;
	system("cls || clear");
	printf ("\n");
    imprime_coordenadas_x(MAX);
	printf ("\n");
	imprime_estrutura_linha_mapa(PRIMEIRA_LINHA, MAX);
	printf("\n");
		
	for(i=0;i<(MAX-1);i++){
		imprime_linha_mapa(i,mapa[i],MAX);
		printf("\n");
		imprime_estrutura_linha_mapa(LINHA_MEIO, MAX);
		printf("\n");
	}
	imprime_linha_mapa(i,mapa[i],MAX);
	
	printf("\n");
	imprime_estrutura_linha_mapa(ULTIMA_LINHA, MAX);
	printf("\n");
	imprime_coordenadas_x(MAX);
    printf("\n");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprimir_mapa_partida(char mapa1[][MAX], char mapa2[][MAX]){
    /*imprime o mapa na tela, pode ser chamada tanto pra imprimir 
    o mapa do jogador quanto o mapa do inimigo*/
	register intizinho i=0,j=0;
	unsigned char letra=CHAR_A_UPPER;
	system("cls || clear");
	printf ("\n\tSeu Mapa\t\t");
    printf ("       Mapa Inimigo\n\n");
    imprime_coordenadas_x(MAX);
    printf ("\t");
	imprime_coordenadas_x(MAX);
	printf ("\n");
	imprime_estrutura_linha_mapa(PRIMEIRA_LINHA, MAX);
	printf ("\t\t");
	imprime_estrutura_linha_mapa(PRIMEIRA_LINHA, MAX);
	printf("\n");
		
	for(i=0;i<(MAX-1);i++){
		imprime_linha_mapa(i,mapa1[i],MAX);
		printf ("\t");
        imprime_linha_mapa(i,mapa2[i],MAX);
		printf("\n");
		imprime_estrutura_linha_mapa(LINHA_MEIO, MAX);
        printf ("\t\t");
        imprime_estrutura_linha_mapa(LINHA_MEIO, MAX);
		printf("\n");
	}
	imprime_linha_mapa(i,mapa1[i],MAX);
	printf ("\t");
	imprime_linha_mapa(i,mapa2[i],MAX);
    printf("\n");
	imprime_estrutura_linha_mapa(ULTIMA_LINHA, MAX);
	printf ("\t\t");
	imprime_estrutura_linha_mapa(ULTIMA_LINHA, MAX);
	printf("\n");
	imprime_coordenadas_x(MAX);
    printf ("\t");
	imprime_coordenadas_x(MAX);
    printf("\n");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_menu_partida(){
	system("clear || cls");
	intizinho tamanho = MAX;
	char *espacos_vazios=NULL;
	putchar('\n');
	imprime_estrutura_linha_mapa(PRIMEIRA_LINHA+MENU, tamanho);
	putchar('\n');
	espacos_vazios = completa_string("Batalha Naval", tamanho);
	printf("  %c%sBatalha Naval%s%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[1] Iniciar Partida", tamanho);
	printf("  %c[1] Iniciar Partida%s%s%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[2] Salvar", tamanho);
	printf("  %c[2] Salvar%s%s\b%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[3] Salvar e Sair", tamanho);
	printf("  %c[3] Salvar e Sair%s%s%c\n", 186, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(LINHA_MEIO+MENU, tamanho);
	putchar('\n');
	free(espacos_vazios);
	espacos_vazios = completa_string("[%d] Sair da Partida", tamanho);
	printf("  %c[%d] Sair da Partida%s%s%c\n", 186, STOP, espacos_vazios, espacos_vazios, 186);
	imprime_estrutura_linha_mapa(ULTIMA_LINHA+MENU, tamanho);
	putchar('\n');
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
