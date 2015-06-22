//incluindo arquivo cm as funções de printf e com as structs
#include "Batalha_Naval_Imprime.c"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//declaração das funções usadas no jogo
void posicao_navio(char mapa[][MAX]);
void inicia_mapa(MapaJogo* mapa);
void novo_jogo();
void posicao_bomba();
void deletar_todos_jogos();
Jogo *carrega_jogos(FILE* jogos_salvos, intizinho *quantidade_de_jogos);  
void visualizar_jogos_salvos(Jogo *jogos);
void jogos_salvos();
intizinho menu_partida();
intizinho menu_principal();
intizinho salvar_jogo(Jogo *jogo);
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
Jogo cria_jogo(char* nome, intizinho turno, MapaJogo* mapa){
    //receb o nome, o turno e os mapas e retorna a struct jogo
    intizinho i=0,j=0;
	Jogo jogo;
	if(nome == NULL){
		nome = (char *) calloc(TAMANHO_NOME_JOGO, sizeof(char));
		strcpy(nome, "<VAZIO>");
	}else{
		//nothing
	}
	if(mapa == NULL){
		mapa = (MapaJogo *) malloc(sizeof(MapaJogo));
		inicia_mapa(mapa);
	}else{
		//nothing
	}
	
	strcpy(jogo.nome, nome);
	jogo.turno = turno;
	jogo.mapa = *mapa;
	
	return jogo;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
char caracter_embarcacao(const intizinho tipo_embarcacao){
    //recebe o tipo da embarcação como int e retorna o tipo da embarcação como char
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
intizinho menu_principal(){
    //imprime o menu e escaneia a opção que vai ser retornda para main
	intizinho opcao=0;
	imprime_menu_principal();
	scanf("%hi", &opcao);
	fflush(stdin);
	return opcao;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
intizinho menu_partida(){
    //imprime o menu da partida e escaneia a opção que vai ser retornda
	intizinho opcao=0;
	imprime_menu_partida();
	scanf("%hi", &opcao);
	fflush(stdin);
	return opcao;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void deletar_todos_jogos(){
    //deleta todos os jogos salvos
	FILE* jogos_salvos = fopen("jogos_salvos.DAT", "w+");
	fclose(jogos_salvos);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void jogos_salvos(){
    //CRUD de salvar,delear e alterar os jogos
    system("clear || cls");
    intizinho quantidade_de_jogos = 0, opcao = 0;
    FILE* jogos_salvos = fopen("jogos_salvos.DAT", "r+b");
    Jogo *jogos = carrega_jogos(jogos_salvos, &quantidade_de_jogos);
    
    do{
		imprime_menu_jogos_salvos();
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				//carregar_jogo();
				break;
			case 2:
				visualizar_jogos_salvos(jogos);
    			break;
			case 3:
				deletar_todos_jogos();
				break;
			case STOP:
				//voltar ao menu principal
				break;
			default:
				printf("Op%c%co Inv%clida", CHAR_CEDILHA, CHAR_ATIO, CHAR_AAGUDO);
				pause();
				break;
			}	
	}while(opcao != STOP);
    //salvar_jogo();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int posicao_vazia(char mapa[][MAX],const Coordenada coordenada){
    /*função para validar se o lugar onde o jogador está colocando 
    o navio é um lugar 'vazio' (igual a '~') */
    if (mapa[coordenada.y][(int)(coordenada.x - CHAR_A_UPPER)] == CHAR_TIO){
        return TRUE;    
    }else{
        return FALSE;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int posicao_valida(const Coordenada coordenada){
    /*função para validar se a coordenada que o navio está sendo 
    colocado não é uma coordenada fora do intervalo do mapa(0-9)*/
    if (!((coordenada.x-CHAR_A_UPPER)>(MAX-1)||(coordenada.x-CHAR_A_UPPER)< 0 ||coordenada.y<0||coordenada.y>(MAX-1))){
        return TRUE;
    }else{
        return FALSE;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void corrige_string(char* string){
	intizinho i=0, f=0;
	for (i= 0; i< TAMANHO_NOME_JOGO; i++){
		if(string[i] == (char) CHAR_ENTER || string[i] == '\0'){
			for(f=i; f < TAMANHO_NOME_JOGO; f++){
				string[f]= '\0';
			}
			break;
		}else{
			//nothing
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int coordenada_valida(char mapa[][MAX], Embarcacao embarcacao){
    /*função para validar se todas as regras para o posicionamento dos 
    embarcacoes estão sendo cumpridas*/
    intizinho i=0, j=0, *ponteiro_direcao;
    Coordenada coordenada, coordenada_embarcacao;
    intizinho distancia_x=0, distancia_y=0;
    double distancia=0;
    distancia_x = abs((int)(embarcacao.popa.x - embarcacao.proa.x));
    distancia_y = abs((int)(embarcacao.popa.y - embarcacao.proa.y));
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
        //Tamanho da embarcação correto. não fazer nada.
    }else{
        //Tamanho da embarcação não esta de acordo com a especificação.
        return FALSE;
    }
    if(embarcacao.popa.x == embarcacao.proa.x){
        ponteiro_direcao = &j;
        if(embarcacao.popa.y < embarcacao.proa.y){
            coordenada = embarcacao.popa;
        }else{
            coordenada = embarcacao.proa;
        }
    }else if(embarcacao.popa.y == embarcacao.proa.y){
        ponteiro_direcao = &i;
        if(embarcacao.popa.x < embarcacao.proa.x){
            coordenada = embarcacao.popa;
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
Embarcacao cria_embarcacao(char mapa[][MAX],const intizinho tipo, intizinho quantidade){
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
                    //printf("%d ", quantidade);
                    imprime_comando_popa(tipo);
                    do{
                        fflush(stdin);
                        scanf ("%c", &embarcacao.popa.x);
        				if (embarcacao.popa.x == CHAR_ESPACO){
                            printf("Insira as Coordenadas.");
                            pause();
                        }else if (embarcacao.popa.x == CHAR_ENTER){
                            printf("Insira as Coordenadas sem Espa%co.", CHAR_CEDILHA);
                            pause();
                        }
                    }while(embarcacao.popa.x == CHAR_ENTER ||embarcacao.popa.x == CHAR_ESPACO);
                    scanf ("%d",&embarcacao.popa.y);
                    if((intizinho)embarcacao.popa.x >= CHAR_A_LOWER){
                       embarcacao.popa.x = (embarcacao.popa.x - (CHAR_A_LOWER - CHAR_A_UPPER));
                    }
                    valida=posicao_valida(embarcacao.popa);
                    vazia=posicao_vazia(mapa, embarcacao.popa);
                    if (valida==0 || vazia==0){
                        printf("Coordenadas Inv%clidas.", CHAR_AAGUDO);
                        pause();
                    }
                }while(!(vazia==1 && valida==1));
                do{
                    system("cls || clear");
                    imprimir_mapa(mapa);
                    printf("%d ", quantidade);
                    imprime_comando_proa(tipo);
                    do{
                        fflush(stdin);
                        scanf ("%c", &embarcacao.proa.x);
                        if (embarcacao.proa.x == CHAR_ESPACO){
                            printf("Insira as Coordenadas.");
                            pause();
                        }else if (embarcacao.proa.x == CHAR_ENTER){
                            printf("Insira as Coordenadas sem Espa%co.", CHAR_CEDILHA);
                            pause();
                        }                    
                    }while(embarcacao.proa.x == CHAR_ENTER || embarcacao.proa.x == CHAR_ESPACO);
                    scanf ("%d", &embarcacao.proa.y);
                    if((intizinho)embarcacao.proa.x >= CHAR_A_LOWER){
                       embarcacao.proa.x = (embarcacao.proa.x - (CHAR_A_LOWER - CHAR_A_UPPER));
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
                    imprime_comando_popa(tipo);
                    do{
                        fflush(stdin);
                        scanf ("%c", &embarcacao.popa.x);
                        if (embarcacao.popa.x == CHAR_ESPACO){
                            printf("Insira as Coordenadas.");
                            pause();
                        }else if (embarcacao.popa.x == CHAR_ENTER){
                            printf("Insira as Coordenadas sem Espa%co.", CHAR_CEDILHA);
                            pause();
                        }
                    }while(embarcacao.popa.x == CHAR_ENTER ||embarcacao.popa.x == CHAR_ESPACO);
                    scanf ("%d",&embarcacao.popa.y);
                    if((intizinho)embarcacao.popa.x >= CHAR_A_LOWER){
                       embarcacao.popa.x = (embarcacao.popa.x - (CHAR_A_LOWER - CHAR_A_UPPER));
                    }
                    valida=posicao_valida(embarcacao.popa);
                    vazia=posicao_vazia(mapa, embarcacao.popa);
                    if (valida==0 || vazia==0){
                        printf("Coordenadas Inv%clidas.", CHAR_AAGUDO);
                        pause();
                    }
                }while(!(vazia==1 && valida==1));
                embarcacao.proa = embarcacao.popa;
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
    if(embarcacao.popa.x == embarcacao.proa.x){
        ponteiro_direcao = &j;
        if(embarcacao.popa.y < embarcacao.proa.y){
            coordenada = embarcacao.popa;
        }else{
            coordenada = embarcacao.proa;
        }
    }else if(embarcacao.popa.y == embarcacao.proa.y){
        ponteiro_direcao = &i;
        if(embarcacao.popa.x < embarcacao.proa.x){
            coordenada = embarcacao.popa;
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
        mapa[coordenada.y][(int)(coordenada.x - CHAR_A_UPPER)]= caracter_embarcacao(embarcacao.tipo);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void posicionar_embarcacoes(MapaJogo *mapa){
    /*função para posicionar os embarcacoes,essa função ira imprimir o mapa
    atualizado a cada vez que o usuario colocar uma coordenada valida*/
    intizinho i=0;
    intizinho contador=0;
    Embarcacao embarcacao;
    imprimir_mapa(mapa->player);
    for(i=0; i<QUANTIDADE_PORTA_AVIAO; i++, contador++){
		embarcacao = cria_embarcacao(mapa->player, PORTA_AVIAO, contador);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    for(i=0; i<QUANTIDADE_ENCOURACADO; i++, contador++){
        embarcacao = cria_embarcacao(mapa->player, ENCOURACADO, contador);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    for(i=0; i<QUANTIDADE_CRUZADOR; i++, contador++){
        embarcacao = cria_embarcacao(mapa->player, CRUZADOR, contador);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    for(i=0; i<QUANTIDADE_SUBMARINO; i++, contador++){
        embarcacao = cria_embarcacao(mapa->player, SUBMARINO, contador);
        coloca_embarcacao(mapa->player, embarcacao);
        imprimir_mapa(mapa->player);
    }
    pause();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
Jogo *carrega_jogos(FILE* jogos_salvos, intizinho *quantidade_de_jogos){
	intizinho quantidade_de_jogos_lida = 0;
	register intizinho i = 0;
	fseek(jogos_salvos, sizeof(Jogo), SEEK_END);
	quantidade_de_jogos_lida = (ftell(jogos_salvos)/(sizeof(Jogo)))-1;
	rewind(jogos_salvos);
	Jogo *jogos = (Jogo*)calloc(MAX_JOGOS, sizeof(Jogo));
	for(i = 0; i < MAX_JOGOS; i++){
		jogos[i] = cria_jogo(NULL, START, NULL);
	}
	if(fread(jogos, (sizeof(Jogo)), MAX_JOGOS, jogos_salvos) != quantidade_de_jogos_lida){
		erro("carrega_jogos()", "Nao foi possivel carregar jogo!");
	}else{
		//ok
	}
	*quantidade_de_jogos = quantidade_de_jogos_lida;
	return jogos;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
intizinho valida_salvar(intizinho posicao_salvar){
    if (posicao_salvar >= 0 && posicao_salvar < MAX_JOGOS){
        return TRUE;
    }else{
        return FALSE;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void visualizar_jogos_salvos(Jogo *jogos){
    intizinho i=0;
    for(i = 0; i < MAX_JOGOS; i++){
			printf(" %d-%s\n", i+1, jogos[i].nome);
	}
}
intizinho salvar_jogo(Jogo *jogo){
	FILE* jogos_salvos = fopen("jogos_salvos.DAT", "r+b");	
	if(jogos_salvos == NULL){
		jogos_salvos = fopen("jogos_salvos.DAT", "w+b");	
	}else{
		//nothing
	}
	if(jogos_salvos != NULL || jogo != NULL){
		intizinho i = 0;
		intizinho quantidade_de_jogos = 0;
		intizinho posicao_salvar=0;
		char nome_jogo[TAMANHO_NOME_JOGO];
		Jogo *jogos = carrega_jogos(jogos_salvos, &quantidade_de_jogos);
        do{
			system("cls || clear");
			printf("Escolha em qual pos%c%co deseja Salvar:\n", CHAR_CEDILHA, CHAR_ATIO);
			visualizar_jogos_salvos(jogos);
			//printf()
            fflush(stdin);
    		scanf ("%d", &posicao_salvar);
    		if (valida_salvar(posicao_salvar)== FALSE){
                printf("Posi%c%co Inv%clida", CHAR_CEDILHA, CHAR_ATIO, CHAR_AAGUDO);
            }
        }while(valida_salvar(posicao_salvar) == FALSE);
		
		printf("Digite o nome do jogo:\n");
		fflush(stdin);
		fgets (nome_jogo, TAMANHO_NOME_JOGO, stdin);
		corrige_string(nome_jogo);
        strcpy(jogo->nome, nome_jogo);
        jogos[posicao_salvar-1] = *jogo;
        rewind (jogos_salvos);
		if((fwrite(jogos, (sizeof(Jogo)), MAX_JOGOS, jogos_salvos)) == FALSE){
			erro("salvar_jogo()", "Nao foi possivel salvar o jogo!");
			return FALSE;
		}else{
			printf("passou!");
		}	
	}else{
		erro("salvar_jogo()", "Nao foi possivel abrir o arquivo!");
		return FALSE;
	}
	fclose(jogos_salvos);
	return TRUE;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void novo_jogo(){
	intizinho opcao = 0;
	Jogo jogo;
	MapaJogo mapa;
	system("cls");
	inicia_mapa(&(jogo.mapa));
	jogo = cria_jogo("<SEM NOME>", START, &(jogo.mapa));
	//pause();
	//dicas_de_jogo();
	//posicionar_embarcacoes(&(jogo.mapa));
	do{
        opcao = menu_partida();
		switch(opcao){
			case 1:
				//jogo();
				imprimir_mapa_partida((jogo.mapa).player, (jogo.mapa).partida_inimigo);
				pause();
				break;
			case 2:
				if(salvar_jogo(&jogo)==TRUE){
					//nothing
				}else{
					printf("N%co foi poss%cvel salvar jogo.\n", CHAR_ATIO, CHAR_IACENTO);
					pause();
				}
				break;
			case 3:
				if(salvar_jogo(&jogo)==TRUE){
					//nothing
				}else{
					printf("N%co foi poss%cvel salvar jogo.\n", CHAR_ATIO, CHAR_IACENTO);
					pause();
				}
				opcao=STOP;
				break;
			case 4:
				opcao=STOP;
				break;
			default:
				printf("Op%c%co inv%clida.", CHAR_CEDILHA, CHAR_ATIO, CHAR_AAGUDO);
				pause();
				continue;
		}
	}while(opcao!=STOP);
	
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
	intizinho opcao=0;
	//batalha_naval_inicio();
	//pause();
	do{
        opcao = menu_principal();
		switch(opcao){
			case 1:
				novo_jogo();
			 	break;
			case 2:
				jogos_salvos();
				break;
			case 3:
                //ranking();
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
