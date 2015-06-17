//declara��o de bibliotecas pr� definidas pela linguagem
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Batalha_Naval.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_coordenadas_x(intizinho tamanho){
    char coordenadas[MAX_SIZE_OF_STRING], parte_coordenada[3], letra = '\0';
    strcpy(coordenadas," ");
    strcpy(parte_coordenada, " ");
    parte_coordenada[2] = '\0';
    for (letra = CHAR_UPPER;letra < (tamanho+CHAR_UPPER); letra++){
        parte_coordenada[1] = letra;
        strcat(coordenadas, parte_coordenada);
	}
	strcat(coordenadas, "  ");
	printf("%s", coordenadas);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void imprime_linha_mapa(intizinho linha, char *linha_mapa, intizinho tamanho){
    intizinho j=0;
    printf("%d%c",linha, 186);
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
		default:
			printf("ERRO INESPERADO!");
            pause();
            exit(0);		
	}
	
	printf(" %c", inicio);
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
	unsigned char letra=CHAR_UPPER;
	system("cls || clear");
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
	unsigned char letra=CHAR_UPPER;
	system("cls || clear");
    imprime_coordenadas_x(MAX);
    printf ("\t\t");
	imprime_coordenadas_x(MAX);
	printf ("\n");
	imprime_estrutura_linha_mapa(PRIMEIRA_LINHA, MAX);
	printf ("\t\t");
	imprime_estrutura_linha_mapa(PRIMEIRA_LINHA, MAX);
	printf("\n");
		
	for(i=0;i<(MAX-1);i++){
		imprime_linha_mapa(i,mapa1[i],MAX);
		printf ("\t\t");
        imprime_linha_mapa(i,mapa2[i],MAX);
		printf("\n");
		imprime_estrutura_linha_mapa(LINHA_MEIO, MAX);
		printf ("\t\t");
        imprime_estrutura_linha_mapa(LINHA_MEIO, MAX);
		printf("\n");
	}
	imprime_linha_mapa(i,mapa1[i],MAX);
	printf ("\t\t");
	imprime_linha_mapa(i,mapa2[i],MAX);
    printf("\n");
	imprime_estrutura_linha_mapa(ULTIMA_LINHA, MAX);
	printf ("\t\t");
	imprime_estrutura_linha_mapa(ULTIMA_LINHA, MAX);
	printf("\n");
	imprime_coordenadas_x(MAX);
    printf ("\t\t");
	imprime_coordenadas_x(MAX);
    printf("\n");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void jogos_salvos(){
    FILE* jogo_salvo;
    //salvar_jogo();
    //ler_jogos_salvos();
    //mostrar_jogos_salvos();
    //deletar_jogos_salvos();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int posicao_vazia(char mapa[][MAX],const Coordenada coordenada){
    /*fun��o para validar se o lugar onde o jogador est� colocando 
    o navio � um lugar 'vazio' (igual a '~') */
    if (mapa[coordenada.y][(int)(coordenada.x - CHAR_UPPER)] == CHAR_TIO){
        return TRUE;    
    }else{
        return FALSE;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int posicao_valida(const Coordenada coordenada){
    /*fun��o para validar se a coordenada que o navio est� sendo 
    colocado n�o � uma coordenada fora do intervalo do mapa(0-9)*/
    if (!((coordenada.x-CHAR_UPPER)>(MAX-1)||(coordenada.x-CHAR_UPPER)< 0 ||coordenada.y<0||coordenada.y>(MAX-1))){
        return TRUE;
    }else{
        return FALSE;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int coordenada_valida(char mapa[][MAX], Embarcacao embarcacao){
    /*fun��o para validar se todas as regras para o posicionamento dos 
    embarcacoes est�o sendo cumpridas*/
    intizinho i=0, j=0, *ponteiro_direcao;
    Coordenada coordenada, coordenada_embarcacao;
    intizinho distancia_x=0, distancia_y=0;
    double distancia=0;
    distancia_x = abs((int)(embarcacao.polpa.x - embarcacao.proa.x));
    distancia_y = abs((int)(embarcacao.polpa.y - embarcacao.proa.y));
    if (distancia_y==0 && distancia_x==0){
        return FALSE;
    }else if(distancia_x==0){
        distancia_y=distancia_y+1;
    }else if(distancia_y==0){
        distancia_x=distancia_x+1;
    }else{
        return FALSE;
    }
    distancia = sqrt(pow(distancia_x,2) + pow((distancia_y),2));
    if(distancia==embarcacao.tipo){
        //Tamanho da embarca��o correto. n�o fazer nada.
    }else{
        //Tamanho da embarca��o n�o esta de acordo com a especifica��o.
        return FALSE;
    }
    if(embarcacao.polpa.x == embarcacao.proa.x){
        ponteiro_direcao = &j;
        if(embarcacao.polpa.y < embarcacao.proa.y){
            coordenada = embarcacao.polpa;
        }else{
            coordenada = embarcacao.proa;
        }
    }else if(embarcacao.polpa.y == embarcacao.proa.y){
        ponteiro_direcao = &i;
        if(embarcacao.polpa.x < embarcacao.proa.x){
            coordenada = embarcacao.polpa;
        }else{
            coordenada = embarcacao.proa;
        }
    }else{
        return FALSE;
    }
        coordenada_embarcacao = coordenada;
    for(i = 0, j = 0; *ponteiro_direcao < embarcacao.tipo; *ponteiro_direcao=*ponteiro_direcao+1){
        coordenada.y = coordenada_embarcacao.y + j;
        coordenada.x = coordenada_embarcacao.x + i;
        if(posicao_vazia(mapa, coordenada)==FALSE || posicao_valida(coordenada)==FALSE){
            return FALSE;
        }else{
            //NOTHING
        }
    }
    return TRUE;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
Embarcacao cria_embarcacao(char mapa[][MAX],const unsigned short int tipo){
   Embarcacao embarcacao;
   int embarcacao_valida=0;
   embarcacao.tipo = tipo;
   int valida=-1,vazia=-1;
   do{
        switch(embarcacao.tipo){
            case PORTA_AVIAO:
            case ENCOURACADO:
            case CRUZADOR:
                do{
                    system("cls || clear");
                    imprimir_mapa(mapa);
                    imprime_comando_polpa(tipo);
                    do{
                        fflush(stdin);
                        scanf ("%c", &embarcacao.polpa.x);
                        if (embarcacao.polpa.x == CHAR_ESPACO){
                            printf("Insira as Coordenadas.");
                            pause();
                        }
                        if (embarcacao.polpa.x == CHAR_ENTER){
                            printf("Insira as Coordenadas sem Espa%co.", CHAR_CEDILHA);
                            pause();
                        }
                    }while(embarcacao.polpa.x == CHAR_ENTER ||embarcacao.polpa.x == CHAR_ESPACO);
                    scanf ("%d",&embarcacao.polpa.y);
                    if((unsigned int)embarcacao.polpa.x >= CHAR_LOWER){
                       embarcacao.polpa.x = (embarcacao.polpa.x - (CHAR_LOWER - CHAR_UPPER));
                    }
                    valida=posicao_valida(embarcacao.polpa);
                    vazia=posicao_vazia(mapa, embarcacao.polpa);
                    if (valida==0 || vazia==0){
                        printf("Coordenadas Inv%clidas.", CHAR_AAGUDO);
                        pause();
                    }
                }while(!(vazia==1 && valida==1));
                do{
                    system("cls || clear");
                    imprimir_mapa(mapa);
                    imprime_comando_proa(tipo);
                    do{
                        fflush(stdin);
                        scanf ("%c", &embarcacao.proa.x);
                        if (embarcacao.proa.x == CHAR_ESPACO){
                            printf("Insira as Coordenadas.");
                            pause();
                        }
                        if (embarcacao.proa.x == CHAR_ENTER){
                            printf("Insira as Coordenadas sem Espa%co.", CHAR_CEDILHA);
                            pause();
                        }                    
                    }while(embarcacao.proa.x == CHAR_ENTER || embarcacao.proa.x == CHAR_ESPACO);
                    scanf ("%d", &embarcacao.proa.y);
                    if((unsigned int)embarcacao.proa.x >= CHAR_LOWER){
                       embarcacao.proa.x = (embarcacao.proa.x - (CHAR_LOWER - CHAR_UPPER));
                    }
                    valida=posicao_valida(embarcacao.proa);
                    vazia=posicao_vazia(mapa, embarcacao.proa);
                    if (valida==0 || vazia==0){
                        printf("Coordenadas Inv%clidas.", CHAR_AAGUDO);
                        pause();
                    }
                }while(!(vazia==1 && valida==1));
                break;
            case SUBMARINO:
                do{
                    system("cls || clear");
                    imprimir_mapa(mapa);
                    imprime_comando_polpa(tipo);
                    do{
                        fflush(stdin);
                        scanf ("%c", &embarcacao.polpa.x);
                        if (embarcacao.polpa.x == CHAR_ESPACO){
                            printf("Insira as Coordenadas.");
                            pause();
                        }
                        if (embarcacao.polpa.x == CHAR_ENTER){
                            printf("Insira as Coordenadas sem Espa%co.", CHAR_CEDILHA);
                            pause();
                        }
                    }while(embarcacao.polpa.x == CHAR_ENTER ||embarcacao.polpa.x == CHAR_ESPACO);
                    scanf ("%d",&embarcacao.polpa.y);
                    if((unsigned int)embarcacao.polpa.x >= CHAR_LOWER){
                       embarcacao.polpa.x = (embarcacao.polpa.x - (CHAR_LOWER - CHAR_UPPER));
                    }
                    valida=posicao_valida(embarcacao.polpa);
                    vazia=posicao_vazia(mapa, embarcacao.polpa);
                    if (valida==0 || vazia==0){
                        printf("Coordenadas Inv%clidas.", CHAR_AAGUDO);
                        pause();
                    }
                }while(!(vazia==1 && valida==1));
                embarcacao.proa = embarcacao.polpa;
                break;
            default:
                //nothing
                break;
        }
        embarcacao_valida = coordenada_valida(mapa, embarcacao);
        if(embarcacao.tipo == SUBMARINO){
            embarcacao_valida = TRUE;
        }else if(!embarcacao_valida){
            printf("Coordenadas Inv%clidas.", CHAR_AAGUDO);
            pause();
        }
    }while(!embarcacao_valida);
   
   return embarcacao;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void coloca_embarcacao(char mapa[][MAX], Embarcacao embarcacao){
    int i=0, j=0;
    int *ponteiro_direcao;
    Coordenada coordenada, coordenada_embarcacao;
    if(embarcacao.polpa.x == embarcacao.proa.x){
        ponteiro_direcao = &j;
        if(embarcacao.polpa.y < embarcacao.proa.y){
            coordenada = embarcacao.polpa;
        }else{
            coordenada = embarcacao.proa;
        }
    }else if(embarcacao.polpa.y == embarcacao.proa.y){
        ponteiro_direcao = &i;
        if(embarcacao.polpa.x < embarcacao.proa.x){
            coordenada = embarcacao.polpa;
        }else{
            coordenada = embarcacao.proa;
        }
    }else{
        return;
    }
    coordenada_embarcacao = coordenada;
    for(i = 0, j = 0; *ponteiro_direcao < embarcacao.tipo; (*ponteiro_direcao)++){
        coordenada.y = coordenada_embarcacao.y + j;
        coordenada.x = coordenada_embarcacao.x + i;
        mapa[coordenada.y][(int)(coordenada.x - CHAR_UPPER)]= caracter_embarcacao(embarcacao.tipo);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void posicionar_embarcacoes(MapaJogo *mapa){
    /*fun��o para posicionar os embarcacoes,essa fun��o ira imprimir o mapa
    atualizado a cada vez que o usuario colocar uma coordenada valida*/
    int coordenada_polpa_x=0,coordenada_polpa_y=0;
    int coordenada_proa_x=0,coordenada_proa_y=0;
    int i=0;
    int validado;
    Embarcacao embarcacao;
    imprimir_mapa(mapa->player);
    for(i=0; i<QUANTIDADE_PORTA_AVIAO; i++){
        embarcacao = cria_embarcacao(mapa->player, PORTA_AVIAO);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    for(i=0; i<QUANTIDADE_ENCOURACADO; i++){
        embarcacao = cria_embarcacao(mapa->player, ENCOURACADO);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    for(i=0; i<QUANTIDADE_CRUZADOR; i++){
        embarcacao = cria_embarcacao(mapa->player, CRUZADOR);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    for(i=0; i<QUANTIDADE_SUBMARINO; i++){
        embarcacao = cria_embarcacao(mapa->player, SUBMARINO);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    pause();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void novo_jogo(){
	MapaJogo mapa;
	system("cls");
	inicia_mapa(&mapa);
	posicionar_embarcacoes(&mapa);
	imprimir_mapa_partida(mapa.player,mapa.partida_inimigo);
	pause();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
	intizinho opcao=0;
	batalha_naval_inicio();
	printf("\nCARREGANDO\r");
	Sleep(TEMPO_SLEEP);
	printf("CARREGANDO.\r");
	Sleep(TEMPO_SLEEP);
	printf("CARREGANDO..\r");
	Sleep(TEMPO_SLEEP);
	printf("CARREGANDO...\r");
	Sleep(TEMPO_SLEEP);
	do{
        opcao = menu_principal();
		switch(opcao){
			case 1:
				novo_jogo();
				break;
			case 2:
				jogos_salvos();
				break;
			case STOP:
				break;
			default:
				printf("Op%c%co inv%clida.", CHAR_CEDILHA, CHAR_ATIO, CHAR_AAGUDO);
				pause();
				continue;
		}
	}while(opcao!=STOP);
	
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
