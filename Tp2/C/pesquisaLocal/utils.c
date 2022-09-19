#include "globals.h"
#include "utils.h"
// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *n, int *iter)
{
	FILE *f;
	int *p, *q;
	int i, j;
	char buffer[50];
	
	f=fopen(nome, "rt");
	if(!f){
		perror("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	do {
		fscanf(f, "%s ", buffer);
	}while(strcmp(buffer, "p") != 0);

	fscanf(f, " edge %d %d", n, iter);

	// Alocacao dinamica da matriz
	p = malloc(sizeof(int) * (*n) * (*n));

	if(!p){
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}

    int k = 0;
    while(k < (*n)*(*n)){
        p[k] = 0;
        ++k;
    }

    int n1 = 0, n2 = 0;
	// Preenchimento da matriz
	for(i=0; i<*iter; i++){
        fscanf(f, " e %d %d", &n1, &n2);
        p[(n1-1)*(*n)+(n2-1)] = 1;
    }
	
    fclose(f);
	return p;
}

// Gera a solucao inicial
// Parametros: numero de vertices
void gera_sol_inicial(int sol[], int v)
{
	int x, n;

	for(int i=0; i < v; i++){
		sol[i]=0;
	}

	n = random_l_h(2, v);

    for (int k = 0; k < n; ++k) {
        do{
            x = random_l_h(0,v-1);
        }while(sol[x] != 0);

        sol[x] = 1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nSolucao com vertices: ");
	for(i=0; i<vert; i++)
		if(sol[i]==1)
			printf("%2d  ", i+1);

	printf("\nSolucao binaria: ");
	for(i=0; i<vert; i++)
		printf("%d  ", sol[i]);
	printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

