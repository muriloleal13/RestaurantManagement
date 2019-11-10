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

//FILA ESPERA
FilaEspera* criaFilaEspera(){

	FilaEspera* filaEspera = (FilaEspera*)malloc(sizeof(FilaEspera));
	filaEspera->ini = NULL;
	filaEspera->fim = NULL;
	return filaEspera;
}

void insereFilaEspera(FilaEspera* filaEspera, int nroPessoas){

	// int senha = buscaSenha(filaEspera);

	Lista* lista = (Lista*) malloc(sizeof(Lista));
	lista->nroPessoas = nroPessoas;
	lista->senha = 0;
	lista->prox = NULL;

	if (filaEspera->fim != NULL)
		filaEspera->fim->prox = lista;
	else
		filaEspera->ini = lista;

	filaEspera->fim = lista;
}

int retiraListaEspera(FilaEspera* filaEspera){

	Lista* lista;
	int nroPessoas = 0;

	if (filaEspera->ini == NULL) { 
		printf("A Fila de Espera esta vazia.\n");
		return nroPessoas;
	}
	lista = filaEspera->ini;
	nroPessoas = lista->nroPessoas;
	filaEspera->ini = lista->prox;
	if (filaEspera->ini == NULL)
		filaEspera->fim = NULL;

	free(lista);
	
	return nroPessoas;
}

void liberaFilaEspera(FilaEspera* filaEspera){

	Lista* lista = filaEspera->ini;
	while (lista != NULL) {
		Lista* listaAux = lista->prox;
		free(lista);
		lista = listaAux;
	}

	free(filaEspera);
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

void entradaClientes(Mesas** matrizMesas, int row, int col, int nroPessoas, FilaEspera* filaEspera){

	if(row != 0 && col != 0 && temLugar(matrizMesas, row, col, nroPessoas)){
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
	}else if(!temLugar(matrizMesas, row, col, nroPessoas)){
		printf("Nao existe mesas suficientes, inserindo na fila de espera.\n");
		insereFilaEspera(filaEspera, nroPessoas);
	}else{
		printf("Sem mesas cadastradas, portanto nao eh possivel cadastrar a entrada clientes.\n");
	}
}

void saidaClientes(Mesas** matrizMesas, int row, int col, int nroMesa, FilaEspera* filaEspera){

	if(row != 0 && col != 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(matrizMesas[i][j].nro == nroMesa){
					matrizMesas[i][j].sentados = 0;
					matrizMesas[i][j].livre = true;
					if(filaEspera->ini != NULL){

					}
				}
			}
		}
	}else{
		printf("Sem mesas cadastradas, portanto nao eh possivel cadastrar a saida de clientes.\n");
	}
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
	printf("1 - Cadastrar %s\n2 - Imprime %s\n3 - Entrada %s\n4 - Saida %s\n5 - Voltar ao Menu\nOp: ", str, str, str2, str2);
	scanf("%d", &opCliente);
	fflush(stdin);

	return opCliente;
}

void menuMesas(Mesas** matrizMesas, FilaEspera* filaEspera){

	int opCliente = opMenuTipo("Mesas", "Clientes");
	int row = 0, col = 0, nro;

	while(opCliente != 5){
		switch(opCliente){
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
				printf("Voltando ao menu.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		opCliente = opMenuTipo("Mesas", "Clientes");
	}
}

void menu(){

	Mesas **matrizMesas = NULL;
	FilaEspera* filaEspera = NULL;

	int op = opMenu();

	while(op != 3){
		switch(op){
			case 1:
				menuMesas(matrizMesas, filaEspera);
				break;
			case 2:
				// opCliente = opMenuTipo("Mesas", "Clientes");
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
