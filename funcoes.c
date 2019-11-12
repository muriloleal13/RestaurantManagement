#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

#define MAX_MESA     4
#define MAX_ESPERA   10
#define MAX_CARROS   2

//FUNÇÕES AUXILIARES
bool temVaga(FilaCarros* filaCarros, int nroCarros){

	Carros *carro;
	int vagas = 0;

	if(filaCarros->ini == NULL){
		return true;
	}

	carro = filaCarros->ini;
	
	while(carro != NULL){
		vagas++;
		carro = carro->prox;
	}

	free(carro);

	return vagas < nroCarros;
}

//FILA
Fila* criaFila(){

	Fila* fila = (Fila*)malloc(sizeof(Fila));
	fila->ini = fila->fim = NULL;
	return fila;
}

FilaCarros* criaFilaCarros(){

	FilaCarros* fila = (FilaCarros*)malloc(sizeof(FilaCarros));
	fila->ini = fila->fim = NULL;
	return fila;
}

void insereFilaEspera(Fila* filaEspera, int nroPessoas){

	Lista* lista = (Lista*) malloc(sizeof(Lista));
	lista->nroPessoas = nroPessoas;
	lista->senha = 1;
	lista->prox = NULL;

	if (filaEspera->fim != NULL){
		lista->senha = filaEspera->fim->senha + 1;
		filaEspera->fim->prox = lista;
	}else{
		filaEspera->ini = lista;
	}

	printf(" com a senha %d.\n", lista->senha);

	filaEspera->fim = lista;
}

int retiraListaEspera(Fila* filaEspera){

	Lista* lista;
	int nroPessoas = 0;

	lista = filaEspera->ini;
	nroPessoas = lista->nroPessoas;
	if(nroPessoas <= MAX_MESA){
		printf("Todas as pessoas da senha %d serao inseridas na mesa\nProxima senha %d\n", lista->senha, lista->prox->senha);
		filaEspera->ini = lista->prox;
		if (filaEspera->ini == NULL){
			filaEspera->fim = NULL;
		}
	}else{
		lista->nroPessoas -= MAX_MESA;
		nroPessoas = MAX_MESA;
		printf("Apenas %d pessoas da senha %d serao inseridas na mesa\n", MAX_MESA, lista->senha);
	}

	free(lista);
	
	return nroPessoas;
}

void liberaFilaEspera(Fila* filaEspera){

	Lista* lista = filaEspera->ini;
	while (lista != NULL) {
		Lista* listaAux = lista->prox;
		free(lista);
		lista = listaAux;
	}

	free(filaEspera);
}

void imprimeFilaEspera(Fila* filaEspera){

	Lista* lista;
	int cont = 1;

	if (filaEspera->ini == NULL) { 
		printf("A Fila de Espera esta vazia.\n");
		return;
	}

	lista = filaEspera->ini;

	printf("=== FILA ESPERA ===\n");

	while(lista != NULL){
		printf("#%d\n%d pessoas\nSenha: %d\n---\n", cont++,lista->nroPessoas, lista->senha);
		lista = lista->prox;
	}

	printf("=== FIM FILA ESPERA ===\n");
}

//PILHA 
PilhaCarros* criaPilha(){

	PilhaCarros* p = (PilhaCarros*) malloc(sizeof(PilhaCarros));
	p->prim = NULL;
	return p;
}

PilhaCarros* pushPilha(PilhaCarros* pilhaCarros, Carros* novoCarro){

	Carros* carro = (Carros*) malloc(sizeof(Carros));

	strcpy(carro->placa, novoCarro->placa);
	carro->ticket = novoCarro->ticket;
	carro->prox = pilhaCarros->prim;

	pilhaCarros->prim = carro;

	return pilhaCarros;
}

PilhaCarros* popPilha(PilhaCarros* pilhaCarros){

	Carros* carro;

	carro = pilhaCarros->prim;

	pilhaCarros->prim = carro->prox;

	free(carro);

	return pilhaCarros;
}

//Mesas
void inicializaMesas(Mesas** matrizMesas, int row, int col){

	int cont = 1;

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			matrizMesas[i][j].nro = cont++;
		  	matrizMesas[i][j].lugares = MAX_MESA;
		  	matrizMesas[i][j].sentados = 0;
		  	matrizMesas[i][j].livre = true;
		}
	}
}

void imprimeMesas(Mesas** matrizMesas, int row, int col){

	int cont = 1;
	char status[10];

	if(row != 0 && col != 0){
		printf("=== MESAS ===\n");
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(matrizMesas[i][j].livre)
					strcpy(status, "Livre");	
				else
					strcpy(status, "Ocupado");
				printf("Mesa #%d\nStatus: %s\nSentados: %d\n---\n", matrizMesas[i][j].nro, status, matrizMesas[i][j].sentados);
			}
		}
		printf("=== FIM MESAS ===\n");
	}else{
		printf("Sem mesas cadastradas.\n");
	}
}

void buscaMesa(Mesas** matrizMesas, int row, int col, int nro){

	int cont = 1;

	if(row != 0 && col != 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(matrizMesas[i][j].nro == nro){
					char status[10];
					if(matrizMesas[i][j].livre)
						strcpy(status, "Livre");	
					else
						strcpy(status, "Ocupado");
					printf("Mesa #%d\nStatus: %s\nSentados: %d\n---\n", cont, matrizMesas[i][j].nro, status, matrizMesas[i][j].sentados);
					cont++;
				}
			}
		}
	}
	if(cont == 1){
		printf("Mesa %d nao encontrada.\n", nro);
	}
}

void entradaClientes(Mesas** matrizMesas, int row, int col, int nroPessoas, Fila* filaEspera){

	if(row != 0 && col != 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(matrizMesas[i][j].livre && nroPessoas > 0){
					matrizMesas[i][j].livre = false;
					if(nroPessoas > MAX_MESA){
						printf("%d pessoas sentaram na mesa %d\n", MAX_MESA, matrizMesas[i][j].nro);
						matrizMesas[i][j].sentados = MAX_MESA;
						nroPessoas -= MAX_MESA;
					}else{
						printf("%d pessoas sentaram na mesa %d\n", nroPessoas, matrizMesas[i][j].nro);
						matrizMesas[i][j].sentados = nroPessoas;
						nroPessoas = 0;
					}
				}
			}
		}
		if(nroPessoas > 0){
			printf("Nao existe mesas suficientes, inserindo as %d pessoas restantes na fila de espera", nroPessoas);
			insereFilaEspera(filaEspera, nroPessoas);
		}
	}else{
		printf("Sem mesas cadastradas, portanto nao eh possivel cadastrar a entrada clientes.\n");
	}
}

void saidaClientes(Mesas** matrizMesas, int row, int col, int nroMesa, Fila* filaEspera){

	bool encontrada = false;

	if(row != 0 && col != 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(matrizMesas[i][j].nro == nroMesa){
					encontrada = true;
					printf("%d pessoas sairam da mesa %d\nRetirando da fila de espera...\n", matrizMesas[i][j].sentados, matrizMesas[i][j].nro);
					matrizMesas[i][j].sentados = 0;
					matrizMesas[i][j].livre = true;
					if(filaEspera->ini != NULL){
						int nroPessoas = retiraListaEspera(filaEspera);
						entradaClientes(matrizMesas, row, col, nroPessoas, filaEspera);
					}
				}
			}
		}
		if(!encontrada){
			printf("Mesa nao encontrada.\n");
		}
	}else{
		printf("Sem mesas cadastradas, portanto nao eh possivel cadastrar a saida de clientes.\n");
	}
}

//ESTACIONAMENTO
FilaCarros* insereEstacionamento(FilaCarros* filaCarros, char placa[], int ticket){

	Carros* carro;
	carro = (Carros*) malloc(sizeof(Carros));

	strcpy(carro->placa, placa);
	carro->prox = NULL;
	carro->ant = NULL;

	if(filaCarros->ini == NULL){
		if(ticket == 0)
			carro->ticket = 1;
		else 
			carro->ticket = ticket;
		filaCarros->ini = carro;
		filaCarros->fim = carro;
	}else{
		if(ticket == 0)
			carro->ticket = filaCarros->fim->ticket + 1;
		else
			carro->ticket = ticket;
		filaCarros->fim->prox = carro;
		carro->ant = filaCarros->fim;
		filaCarros->fim = carro;
	}

	return filaCarros;
}

FilaCarros* removeEstacionamento(FilaCarros* filaCarros, char placa[]){

	Carros *carro;
	Carros *aux;
	PilhaCarros *pilhaCarros = criaPilha();
	char placaRet[10];

	if(filaCarros->ini == NULL){
		printf("Estacionamento vazio.\n");
		return filaCarros;
	}

	carro = filaCarros->fim;

	if(filaCarros->ini == filaCarros->fim){
		if(strcmp(carro->placa, placa) == 0){
			printf("Carro com placa %s removido do estacionamento\n", carro->placa);
			filaCarros->ini = filaCarros->fim = NULL;
			free(carro);
		}
		else{
			printf("Placa nao encontrada.\n");
		}
	}else{
		while(!(strcmp(carro->placa, placa) == 0)){
			pilhaCarros = pushPilha(pilhaCarros, carro);
			filaCarros->fim = carro->ant;
			filaCarros->fim->prox = NULL;
			aux = carro->ant;
			free(carro);
			carro = aux;
		}
		if(carro == NULL){
			printf("Placa nao encontrada.\n");
		}else{				

			if(carro->ant != NULL){
				carro->ant->prox = NULL;
				filaCarros->fim = carro->ant;
			}else{
				filaCarros->fim = NULL;
				filaCarros->ini = NULL;
			}

			free(carro);
		}

		while(pilhaCarros->prim != NULL){
			strcpy(carro->placa, pilhaCarros->prim->placa);
			carro->ticket = pilhaCarros->prim->ticket; 
			pilhaCarros = popPilha(pilhaCarros);
			filaCarros = insereEstacionamento(filaCarros, carro->placa, carro->ticket);
		}
	}

	free(pilhaCarros);

	return filaCarros;
}

void imprimeEstacionamento(FilaCarros* filaCarros){

	Carros *carro;
	int cont = 1;

	if(filaCarros->ini == NULL){
		printf("Estacionamento vazio.\n");
		return;
	}

	carro = filaCarros->ini;

	printf("=== ESTACIONAMENTO ===\n");

	while(carro != NULL){
		printf("Carro #%d\nPlaca %s\nTicket %d\n---\n", cont++, carro->placa, carro->ticket);
		carro = carro->prox;
	}

	printf("=== FIM ESTACIONAMENTO ===\n");
}

void buscaCarro(FilaCarros* filaCarros, char placa[]){

	Carros *carro;
	int cont = 1;

	if(filaCarros->ini == NULL){
		printf("Estacionamento vazio.\n");
		return;
	}

	carro = filaCarros->ini;

	while(carro != NULL){
		if(strcmp(carro->placa, placa) == 0)
			printf("Carro #%d\nPlaca %s\nTicket %d\n---\n", cont++, carro->placa, carro->ticket);
		carro = carro->prox;
	}

	if(cont == 1)
		printf("Carro nao encontrado.\n");
}

//MENU
int opMenu(){

	int op;

	printf("=== MENU ===\n");
	printf("1 - Mesas\n2 - Estacionamento\n3 - Sair\nOp: ");
	scanf("%d", &op);
	fflush(stdin);

	return op;
}

int opMenuTipo(char str[], char str2[], char str3[]){

	int opCliente;

	printf("=== Menu %s === \n", str);
	if(strcmp(str, "Mesas") == 0)
		printf("1 - Cadastrar %s\n2 - Imprime %s\n3 - Entrada %s\n4 - Saida %s\n5 - Imprime %s\n6 - Buscar %s\n7 - Voltar ao Menu\nOp: ", str, str, str2, str2, str3, str);
	else
		printf("1 - Cadastrar %s\n2 - Imprime %s\n3 - Entrada %s\n4 - Saida %s\n5 - Imprime %s\n6 - Buscar %s\n7 - Voltar ao Menu\nOp: ", str, str, str2, str2, str3, str2);
	scanf("%d", &opCliente);
	fflush(stdin);

	return opCliente;
}

void menuMesas(Mesas** matrizMesas, Fila* filaEspera, int* mesaRow, int* mesaCol){

	int opMesas = opMenuTipo("Mesas", "Clientes", "Fila de Espera");
	int row = *mesaRow, col = *mesaCol, nro;

	while(opMesas != 7){
		switch(opMesas){
			case 1:
				printf("=== CADASTRA MESAS ===\n");
				printf("Digite o numero de linhas de mesas: ");
				scanf("%d", &row);
				fflush(stdin);
				printf("Digite o numero de colunas de mesas: ");
				scanf("%d", &col);
				fflush(stdin);
				matrizMesas = (Mesas **) malloc(row * sizeof(struct mesa*));
			    for (int i = 0; i < row; i++)
			      	matrizMesas[i] = (Mesas *) malloc(col * sizeof(struct mesa));
				inicializaMesas(matrizMesas, row, col);
				break;
			case 2:
				imprimeMesas(matrizMesas, row, col);
				break;
			case 3:
				printf("Digite o numero de pessoas: ");
				scanf("%d", &nro);
				fflush(stdin);
				entradaClientes(matrizMesas, row, col, nro, filaEspera);
				break;
			case 4:
				printf("Digite o numero da mesa: ");
				scanf("%d", &nro);
				fflush(stdin);
				saidaClientes(matrizMesas, row, col, nro, filaEspera);
				break;
			case 5:
				imprimeFilaEspera(filaEspera);
				break;
			case 6:
				printf("Digite o numero da mesa a pesquisar: ");
				scanf("%d", &nro);
				buscaMesa(matrizMesas, row, col, nro);
				break;
			case 7:
				printf("Voltando ao menu.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		opMesas = opMenuTipo("Mesas", "Clientes", "Fila de Espera");
	}
	system("cls");
	*mesaRow = row;
	*mesaCol = col;
}

FilaCarros* menuEstacionamento(FilaCarros* filaCarros, int* nroCarros){

	int opEstacionamento = opMenuTipo("Estacionamento", "Carros", "Estacionamento");
	int maxCarros = *nroCarros;
	char placa[10];

	while(opEstacionamento != 7){
		switch(opEstacionamento){
			case 1:
				printf("Digite o numero de carros possiveis no estacionamento: ");
				scanf("%d", &maxCarros);
				break;
			case 2:
				imprimeEstacionamento(filaCarros);
				break;
			case 3:
				if(temVaga(filaCarros, maxCarros)){
					printf("Digite a placa do carro: ");
					gets(placa);
					filaCarros = insereEstacionamento(filaCarros, placa, 0);
				}else{
					printf("Sem vaga no estacionamento.\n");
				}
				break;
			case 4:
				printf("Digite a placa do carro: ");
				gets(placa);
				filaCarros = removeEstacionamento(filaCarros, placa);
				break;
			case 5: 
				imprimeEstacionamento(filaCarros);
				break;
			case 6: 
				printf("Digite a placa a pesquisar: ");
				gets(placa);
				buscaCarro(filaCarros, placa);
				break;
			case 7:
				printf("Voltando ao menu.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		opEstacionamento = opMenuTipo("Estacionamento", "Carros", "Estacionamento");
	}
	system("cls");
	*nroCarros = maxCarros;
	return filaCarros;
}

void menu(){

	Mesas **matrizMesas = NULL;
	Fila* filaEspera = criaFila();
	FilaCarros* filaCarros = criaFilaCarros();
	int nroCarros = MAX_CARROS, mesaRow = 0, mesaCol = 0;

	int op = opMenu();

	while(op != 3){
		switch(op){
			case 1:
				menuMesas(matrizMesas, filaEspera, &mesaRow, &mesaCol);
				break;
			case 2:
				filaCarros = menuEstacionamento(filaCarros, &nroCarros);
				break;
			case 3:
				printf("Finalizando...\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		op = opMenu();
	}
	printf("Sessao finalizada.\n");
}
