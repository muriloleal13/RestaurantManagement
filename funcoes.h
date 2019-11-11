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
	struct carros* ant;
	struct carros* prox;
} Carros;

typedef struct fila_carros{
	Carros* ini;
	Carros* fim;
} FilaCarros;

typedef struct lista_carros{
	char placa[10];
	struct lista_carros* prox;
} ListaCarros;

typedef struct pilha_carros{
	ListaCarros* prim;
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
void pushPilha(PilhaCarros* PilhaCarros, char placa[]);
void popPilha(PilhaCarros* pilhaCarros, char *placa);

//MESAS
void inicializaMesas(Mesas** matrizMesas, int row, int col);
void imprimeMesas(Mesas** matrizMesas, int row, int cols);
void entradaClientes(Mesas** matrizMesas, int row, int col, int nroPessoas, Fila* filaEspera);
void saidaClientes(Mesas** matrizMesas, int row, int col, int nroMesa, Fila* filaEspera);

//ESTACIONAMENTO
void insereEstacionamento(FilaCarros* filaCarros, char placa[]);
void removeEstacionamento(FilaCarros* filaCarros, char placa[]);
void imprimeEstacionamento(FilaCarros* filaCarros);

//Menu
int opMenu();
int opMenuTipo(char str[], char str2[]);
void menuMesas(Mesas** matrizMesasm, Fila* filaEspera);
int menuEstacionamento(FilaCarros* filaCarros, int nroCarros);
void menu();
