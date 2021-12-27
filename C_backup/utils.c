#include "utils.h"
#include "algoritmo.h"

/*Leitura do ficheiro de input
  Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
  Devolve a matriz de adjacencias*/
int* init_dados(char *nome, int *n, int *iter){
	FILE *f;
	int *p, *q;
	int i, j;

	f=fopen(nome, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
    int a,b;
    char c;
		c = fgetc(f);
		printf("%c",c);
	// Numero de iteracoes
	
		
	
	
	 
    
	// Numero de vertices
	//fscanf(f, " %d", n);
	// Alocacao dinamica da matriz
	/*p = malloc(sizeof(int)*(*n)*(*n));
	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}
	q=p;
	// Preenchimento da matriz
	for(i=0; i<*n; i++)
        for(j=0; j<*n; j++)
            fscanf(f, " %d", q++);
	fclose(f);
	return p;*/
}
/* Inicializa o gerador de numeros aleatorios */
void init_rand(){
    srand((unsigned)time(NULL));
}


