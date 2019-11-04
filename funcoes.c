Mesas** criaMesas(){
	return NULL;
}

//MESAS
Mesas** insereMesas(Mesas** listaMesas, int row, int col){

	listaMesas = (Mesas**) malloc(sizeof(Mesas*) * row);
	for(int i = 0; i < row; i++){
		listaMesas = (Mesas*) malloc(sizeof(Mesas) * col);
	}

	return listaMesas;
}

Mesas** cadastraMesas(Mesas** listaMesas){

	int row, col;

	printf("=== CADASTRA MESAS ===\n");

	printf("Digite o numero de linhas de mesas: ");
	scanf("%d", &row);
	fflush(stdin);
	printf("Digite o numero de colunas de mesas: ");
	scanf("%d", &col);
	fflush(stdin);

	listaMesas = insereMesas(listaMesas, row, col);

	return listaMesas;
}

void menu(){

	Mesas** listaMesas = criaMesas();

	int op = opMenu();
	fflush(stdin);

	while(op != 3){
		switch(op){
			case 1:
				listaClientes = menuMesas(listaMesas);
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
		op = opMenu();
	}

int opMenu(){

	int op;

	printf("=== MENU ===\n");

	printf("1 - Mesas\n2 - Estacionamento\n3 - Sair\nOp: ");
	scanf("%d", &op);
	fflush(stdin);

	return op;
}

int opMenuTipos(char str[]){

	int op;

	printf("=== Menu %s === \n", str);

	printf("1 - Cadastrar %s\n2 - Voltar ao Menu\nOp: ", str, str, str);
	scanf("%d", &op);
	fflush(stdin);

	return op;
}

Mesas** menuMesas(Mesas** listaMesas){

	int opCliente = opMenuTipos("Mesas");
	
	while(opCliente != 4){
		switch(opCliente){
			case 1:
				listaMesas = cadastraMesas(listaMesas);
				break;
			case 2:
				printf("Voltando ao menu.\n");
				break;
			default:
				printf("Operacao invalida.\n");
				break;
		}
		opCliente = opMenuTipos("Clientes");
	}
	return listaClientes;
}

}
