typedef struct mesas{
	int nro;
	bool livre;
} Mesa;

typedef struct lista_mesas{
	Conta conta;
	struct lista_mesas* prox;
} Mesas;

//MESAS
Mesas** criaMesas();
Mesas** insereMesas (Mesas* listaMesas, int row, int col);

//Menu
void menu();
int opMenu();
int opMenuTipos(char str[])
Mesas** menuMesas(Mesas** listaMesas);
