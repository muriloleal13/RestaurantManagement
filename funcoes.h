typedef struct mesa{
	int nro;
	bool livre;
} Mesas;

//MESAS
void preencheMesas(Mesas** matrizMesas, int row, int col);
void imprimeMesas(Mesas** matrizMesas, int row, int col);

//Menu
void menu();
