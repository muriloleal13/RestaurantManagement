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
} Fila;

typedef struct carros{
	char placa[10];
	int ticket;
	struct carros* ant;
	struct carros* prox;
} Carros;

typedef struct fila_carros{
	Carros* ini;
	Carros* fim;
} FilaCarros;

typedef struct pilha_carros{
	Carros* prim;
} PilhaCarros;

//FUNÇÕES AUXILIARES
bool temLugar(Mesas** matrizMesas, int row, int col, int nroPessoas);
bool temVaga(FilaCarros* filaCarros, int nroCarros);

//FILA
Fila* criaFila();
FilaCarros* criaFilaCarros();
void insereFilaEspera(Fila* filaEspera, int nroPessoas);
int retiraListaEspera(Fila* filaEspera);
void liberaFilaEspera(Fila* filaEspera);
void imprimeFilaEspera(Fila* filaEspera);

//PILHA
PilhaCarros* criaPilha();
PilhaCarros* pushPilha(PilhaCarros* PilhaCarros, Carros* novoCarro);
PilhaCarros* popPilha(PilhaCarros* pilhaCarros);

//MESAS
void inicializaMesas(Mesas** matrizMesas, int row, int col);
void imprimeMesas(Mesas** matrizMesas, int row, int cols);
void entradaClientes(Mesas** matrizMesas, int row, int col, int nroPessoas, Fila* filaEspera);
void saidaClientes(Mesas** matrizMesas, int row, int col, int nroMesa, Fila* filaEspera);

//ESTACIONAMENTO
FilaCarros* insereEstacionamento(FilaCarros* filaCarros, char placa[], int ticket);
FilaCarros* removeEstacionamento(FilaCarros* filaCarros, char placa[]);
void imprimeEstacionamento(FilaCarros* filaCarros);

//Menu
int opMenu();
int opMenuTipo(char str[], char str2[], char str3[]);
void menuMesas(Mesas** matrizMesasm, Fila* filaEspera);
FilaCarros* menuEstacionamento(FilaCarros* filaCarros, int* nroCarros);
void menu();
