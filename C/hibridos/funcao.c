#define _CRT_SECURE_NO_WARNINGS 1
# include <math.h>
# include "utils.h"
#include "algoritmo.h"
#include "funcao.h"

// Calcula a qualidade de uma solu��o
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, int *mat , int *v){
	int x=0;

	if (solucaovalida(sol, d.vert, mat) == 0) { // solução inválida	
			for(int j=0; j<d.vert; j++){
				do{																	
					x = random_l_h(0, d.vert-1);
				}while(sol[x] == 0);
				sol[x]=1;
			}
			*v = 0;
	}else{
		*v = 1;
	}

	int fit = calcula_fit(sol , d);
	if (*v == 0 ) 
		fit = 0;
	
	return fit;
}

int solucaovalida(int *sol, int v, int * mat){
    int i=0, j=0;
    for(i=0; i<v; i++)
		if(sol[i]==1)
		{
			for(j=0; j<v;j++)
				if(sol[j]==1 && mat[i*v+j]==1)
                    return 0; 

		}
    return 1;
}

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate(pchrom pop, struct info d, int *mat)
{
	int i;

	for (i=0; i<d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
		
}

// Calcula a qualidade de uma solu��o
// Recebe:  A solu��o, a, a matriz de adjac�ncias, mat, e o n�mero de v�rtices, vert
// Devolve: O custo que � o n�mero de liga��es que existem na solu��o
int calcula_fit(int sol[], struct info x)
{
	int total=0;
	int i;

	for(i=0; i < x.vert; i++)
		if(sol[i] == 1)
			total++;

	return total;
}