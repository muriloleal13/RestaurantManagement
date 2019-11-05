typedef struct mesa{
	int nro;
	int lugares;
	int sentados;
	bool livre;
} Mesas;

typedef struct lista{
	int senha;
	int nroPessoas;
	struct lista* prox;
} Lista;

typedef struct fila{
	Lista* ini;
	Lista* fim;
} FilaEspera;

//FILA ESPERA
FilaEspera* criaFilaEspera();
void insereFilaEspera(FilaEspera* filaEspera, int nroPessoas);
int retiraListaEspera(FilaEspera* filaEspera);
void liberaFilaEspera(FilaEspera* filaEspera);

//FUNÇÕES AUXILIARES
bool temLugar(Mesas** matrizMesas, int row, int col, int nroPessoas);

//MESAS
void inicializaMesas(Mesas** matrizMesas, int row, int col);
void imprimeMesas(Mesas** matrizMesas, int row, int cols);
void entradaClientes(Mesas** matrizMesas, int row, int col, int nroPessoas, FilaEspera* filaEspera);
void saidaClientes(Mesas** matrizMesas, int row, int col, int nroMesa, FilaEspera* filaEspera);

//Menu
int opMenu();
int opMenuTipo(char str[], char str2[]);
void menuMesas(Mesas** matrizMesasm, FilaEspera* filaEspera);
void menu();
