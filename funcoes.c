#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

void criaMesas(){
	return NULL;
}

//MESAS
void preencheMesas(Mesas** matrizMesas, int row, int col){

	int cont = 1;

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			matrizMesas[i][j].nro = cont;
			matrizMesas[i][j].livre = true;
			cont++;
		}
	}
}

void imprimeMesas(Mesas** matrizMesas, int row, int col){

	int cont = 1;

	if(row == 0 || col == 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				char status[10];
				if(matrizMesas[i][j].livre)
					strcpy(status, "Livre");	
				else
					strcpy(status, "Ocupado");

				printf("%d\nMesa %d\nStatus: %s\n =X=X=X=X=X=X=X=X=X=", cont, matrizMesas[i][j].nro, status);
				cont++;
			}
		}
	}else{
		printf("Sem mesas cadastradas\n");
	}
}

void menu(){

	Mesas **matrizMesas = NULL;
	int op;
	int opCliente;
	int row = 0, col = 0;

	printf("=== MENU ===\n");

	printf("1 - Mesas\n2 - Estacionamento\n3 - Sair\nOp: ");
	scanf("%d", &op);
	fflush(stdin);

	while(op != 3){
		switch(op){
			case 1:
				printf("=== Menu Mesas === \n");
				printf("1 - Cadastrar Mesas\n2 - Imprime Mesas\n3- Voltar ao Menu\nOp: ");
				scanf("%d", &opCliente);
				fflush(stdin);
				while(opCliente != 3){
					switch(opCliente){
						case 1:
							printf("=== CADASTRA MESAS ===\n");
							printf("Digite o numero de linhas de mesas: ");
							scanf("%d", &row);
							fflush(stdin);
							printf("Digite o numero de colunas de mesas: ");
							scanf("%d", &col);
							fflush(stdin);

						    matrizMesas = (Mesas **)malloc(row *(sizeof(struct mesa*)));
						    for (int i = 0; i < row; i++)
						      	matrizMesas[i] = (Mesas *)malloc(col *(sizeof(struct mesa)));
						     
						    preencheMesas(matrizMesas, row, col);
							break;
						case 2:
							imprimeMesas(matrizMesas, row, col);
							break;
						case 3:
							printf("Voltando ao menu.\n");
							break;
						default:
							printf("Operacao invalida.\n");
							break;
					}
					printf("1 - Cadastrar Mesa\n2 - Imprime Mesas\n3 - Voltar ao Menu\nOp: ");
					scanf("%d", &opCliente);
					fflush(stdin);
				}
				break;
			case 2:
				break;
			case 3:
				printf("Sessao finalizada.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		system("cls");
		printf("1 - Mesas\n2 - Estacionamento\n3 - Sair\nOp: ");
		scanf("%d", &op);
		fflush(stdin);
	}

}
