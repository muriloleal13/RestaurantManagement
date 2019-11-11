#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

#define MAX_MESA   4
#define MAX_ESPERA 10

//FUNÇÕES AUXILIARES
bool temLugar(Mesas** matrizMesas, int row, int col, int nroPessoas){

	int lugares = 0;

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(matrizMesas[i][j].livre){
				lugares += matrizMesas[i][j].lugares;
			}
		}
	}

	return lugares > nroPessoas;
}

bool temVaga(FilaCarros* filaCarros, int nroCarros){

	Carros *carro;
	int cont = 0;

	if(filaCarros->ini == NULL){
		return true;
	}

	carro = filaCarros->ini;
	
	while(carro != NULL){
		cont++;
		carro = carro->prox;
	}

	free(carro);
	// printf("%d carros estacionados\n", cont);
	return cont < nroCarros;
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

	filaEspera->fim = lista;
}

int retiraListaEspera(Fila* filaEspera){

	Lista* lista;
	int nroPessoas = 0;

	if (filaEspera->ini == NULL) { 
		printf("A Fila de Espera esta vazia.\n");
		return nroPessoas;
	}
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
	while(lista != NULL){
		printf("#%d\n%d pessoas\n---\n", cont++,lista->nroPessoas);
		lista = lista->prox;
	}

	free(lista);
}

//PILHA 
PilhaCarros* criaPilha(){

	PilhaCarros* p = (PilhaCarros*) malloc(sizeof(PilhaCarros));
	p->prim = NULL;
	return p;
}

void pushPilha(PilhaCarros* pilhaCarros, char placa[]){

	ListaCarros* listaCarros = (ListaCarros*) malloc(sizeof(ListaCarros));
	strcpy(listaCarros->placa, placa);
	listaCarros->prox = pilhaCarros->prim;
	pilhaCarros->prim = listaCarros;
}

void popPilha(PilhaCarros* pilhaCarros, char *placa){

	ListaCarros* listaCarros;

	listaCarros = pilhaCarros->prim;
	strcpy(placa, listaCarros->placa);
	pilhaCarros->prim = listaCarros->prox;
	free(listaCarros);
}

//MESAS
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

	if(row != 0 && col != 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				char status[10];
				if(matrizMesas[i][j].livre)
					strcpy(status, "Livre");	
				else
					strcpy(status, "Ocupado");

				printf("#%d\nMesa %d\nStatus: %s\nSentados: %d\n---\n", cont, matrizMesas[i][j].nro, status, matrizMesas[i][j].sentados);
				cont++;
			}
		}
	}else{
		printf("Sem mesas cadastradas.\n");
	}
}

void entradaClientes(Mesas** matrizMesas, int row, int col, int nroPessoas, Fila* filaEspera){

	if(row != 0 && col != 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(matrizMesas[i][j].livre && nroPessoas > 0){
					matrizMesas[i][j].livre = false;
					if(nroPessoas > MAX_MESA){
						matrizMesas[i][j].sentados = MAX_MESA;
						nroPessoas -= MAX_MESA;
					}else{
						matrizMesas[i][j].sentados = nroPessoas;
						nroPessoas = 0;
					}
				}
			}
		}
	}else{
		printf("Sem mesas cadastradas, portanto nao eh possivel cadastrar a entrada clientes.\n");
	}
	if(nroPessoas > 0){
		printf("Nao existe mesas suficientes, inserindo pessoas restantes na fila de espera.\n");
		insereFilaEspera(filaEspera, nroPessoas);
	}
}

void saidaClientes(Mesas** matrizMesas, int row, int col, int nroMesa, Fila* filaEspera){

	if(row != 0 && col != 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(matrizMesas[i][j].nro == nroMesa){
					matrizMesas[i][j].sentados = 0;
					matrizMesas[i][j].livre = true;
					if(filaEspera->ini != NULL){
						int nroPessoas = retiraListaEspera(filaEspera);
						entradaClientes(matrizMesas, row, col, nroPessoas,filaEspera);
					}
				}
			}
		}
	}else{
		printf("Sem mesas cadastradas, portanto nao eh possivel cadastrar a saida de clientes.\n");
	}
}

FilaCarros* insereEstacionamento(FilaCarros* filaCarros, char placa[]){

	Carros* carro;
	carro = (Carros*) malloc(sizeof(Carros));

	strcpy(carro->placa, placa);
	carro->prox = NULL;
	carro->ant = NULL;

	if(filaCarros->ini == NULL){
		filaCarros->ini = carro;
		filaCarros->fim = carro;
	}else{
		filaCarros->fim->prox = carro;
		carro->ant = filaCarros->fim;
		filaCarros->fim = carro;
	}

	imprimeEstacionamento(filaCarros);

	free(carro);

	return filaCarros;
}

FilaCarros* removeEstacionamento(FilaCarros* filaCarros, char placa[]){

	Carros *carro;
	PilhaCarros *pilhaCarros = criaPilha();
	char placaRet[10];

	if(filaCarros->ini == NULL){
		printf("Estacionamento vazio.\n");
		return filaCarros;
	}

	carro = filaCarros->fim;

	if(filaCarros->ini == filaCarros->fim){
		filaCarros->ini = filaCarros->fim = NULL;
	}else{
		while(!(strcmp(carro->placa, placa) == 0)){ //remove os carros que não é o com a placa igual e insere na lista
			pushPilha(pilhaCarros, carro->placa);
			filaCarros->fim = carro->ant;
			filaCarros->fim->prox = NULL;
		}

		filaCarros->fim = carro->ant; //remove o carro que vai sair
		filaCarros->fim->prox = NULL;

		while(pilhaCarros->prim != NULL){ //remove o carro da pilha e insere novamente no estacionamento
			popPilha(pilhaCarros, placaRet);
			insereEstacionamento(filaCarros, placaRet);
		}
	}

	free(pilhaCarros);
	free(carro);

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

	while(carro != NULL){
		printf("#%d\nPlaca %s\n---\n", cont++, carro->placa);
		carro = carro->prox;
	}

	free(carro);
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

int opMenuTipo(char str[], char str2[]){

	int opCliente;

	printf("=== Menu %s === \n", str);
	if(strcmp(str, "Mesas") == 0)
		printf("1 - Cadastrar %s\n2 - Imprime %s\n3 - Entrada %s\n4 - Saida %s\n5 - Imprime Fila de Espera\n6 - Voltar ao Menu\nOp: ", str, str, str2, str2);
	else
		printf("1 - Cadastrar %s\n2 - Imprime %s\n3 - Entrada %s\n4 - Saida %s\n5 - Voltar ao Menu\nOp: ", str, str, str2, str2);
	scanf("%d", &opCliente);
	fflush(stdin);

	return opCliente;
}

void menuMesas(Mesas** matrizMesas, Fila* filaEspera){

	int opMesas = opMenuTipo("Mesas", "Clientes");
	int row = 0, col = 0, nro;

	while(opMesas != 6){
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
				printf("Voltando ao menu.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		opMesas = opMenuTipo("Mesas", "Clientes");
	}
}

int menuEstacionamento(FilaCarros* filaCarros, int nroCarros){

	int opEstacionamento = opMenuTipo("Estacionamento", "Carros");
	int row = 0, col = 0;
	char placa[10];

	while(opEstacionamento != 5){
		switch(opEstacionamento){
			case 1:
				printf("Digite o numero de carros possiveis no estacionamento: ");
				scanf("%d", &nroCarros);
				break;
			case 2:
				imprimeEstacionamento(filaCarros);
				break;
			case 3:
				if(temVaga(filaCarros, nroCarros)){
					printf("Digite a placa do carro: ");
					scanf("%[^\n]", placa);
					insereEstacionamento(filaCarros, placa);
				}else{
					printf("Sem vaga no estacionamento.\n");
				}
				break;
			case 4:
				printf("Digite a placa do carro: ");
				scanf("%[^\n]", placa);
				removeEstacionamento(filaCarros, placa);
				break;
			case 5:
				printf("Voltando ao menu.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		opEstacionamento = opMenuTipo("Estacionamento", "Carros");
	}
	return nroCarros;
}

void menu(){

	Mesas **matrizMesas = NULL;
	Fila* filaEspera = criaFila();
	FilaCarros* filaCarros = criaFilaCarros();
	int nroCarros = 0;

	int op = opMenu();

	while(op != 3){
		switch(op){
			case 1:
				menuMesas(matrizMesas, filaEspera);
				break;
			case 2:
				nroCarros = menuEstacionamento(filaCarros, nroCarros);
				break;
			case 3:
				printf("Sessao finalizada.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		system("cls");
		op = opMenu();
	}

}
