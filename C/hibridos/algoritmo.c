#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

#define PROB 0.1 //Para Trepa Colinas

// Preenche uma estrutura com os progenitores da pr�xima gera��o, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Par�metros de entrada: popula��o actual (pop), estrutura com par�metros (d) e popula��o de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents){
	int i, temp,max;

	// Realiza popsize torneios
	for(i=0; i<d.popsize;i++) // tamanho do array pop com as soluções
	{
		max = random_l_h(0, d.popsize-1);
		do
			temp = random_l_h(0,d.popsize - 1);
		while(temp == max);

		if(pop[max].fitness > pop[temp].fitness) 
			parents[i] = pop[max];
		else
			parents[i]=pop[temp];
		
	}
}

// Operadores geneticos a usar na gera��o dos filhos
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom pop)
{
    // Recombina��o com um ponto de corte
	crossover(parents, d, pop); // quando sucesso na probabilidade de recombinação, pop fica com metade dos bits do parent e mantém metade dos seus
	// Muta��o bin�ria
	mutation(pop, d); // para cada bit de cada solução vê atravéz da probabilidade de mutação se lhe dá flip
}

// Preenche o vector descendentes com o resultado das opera��es de recombina��o
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void crossover(pchrom parents, struct info x, pchrom offspring)
{
	int i, j, point;

	for (i=0; i<x.popsize; i+=2) // tam de parents
	{
		if (rand_01() < x.pr) // rand_01 retorna um valor entre 0 e 1, pr = probabilidade de recombinação
		{
			point = random_l_h(0, x.vert - 1); 
			for (j=0; j<point; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i+1].p[j] = parents[i+1].p[j];
			}
			for (j = point; j< x.vert ; j++)
			{
				offspring[i].p[j] = parents[i+1].p[j];
				offspring[i+1].p[j] = parents[i].p[j];
			}
		}else{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
	}
}

// Muta��o bin�ria com v�rios pontos de muta��o
// Par�metros de entrada: estrutura com os descendentes (offspring) e estrutura com par�metros (d)
void mutation(pchrom offspring, struct info x)
{
    int i, j;

	for(i = 0 ; i < x.popsize ; i++)
    	for (j=0; j < x.vert; j++)
        	if (rand_01() < x.pm)
            	offspring[i].p[j] = !(offspring[i].p[j]);		
                
}

//Trepa colinas

int trepa_colinas(int sol[], int *mat, struct info x, int num_iter)
{
    int custo, custo_viz, i;
    double prob;

	int vizinho1[x.vert];
    int vizinho2[x.vert];
    int nova_sol[x.vert];

    do {
        //Gere sol inicial
        gera_sol_inicial(sol, x.vert);			

        //Calcula fitness de sol inicial
        custo = calcula_fit(sol, mat, x.vert);
        
    }while(custo == -1); //Enquanto o custo da solucao inicial for -1 (ser invalida) originar outra

    
    //Escrever sol inicial
   /* escreve_sol(sol, x.vert);
    printf("Custo inicial = %d\n", custo);*/
    
    for(i=0; i<num_iter; i++)
    {
		do{
            // Gera vizinho
            gera_vizinho(sol, vizinho1, vizinho2, x.vert);
            // Avalia melhor vizinho
            custo_viz = melhorVizinho(nova_sol, vizinho1, vizinho2, mat, x.vert);
        }while(custo_viz == -1);
        
        if(custo_viz >= custo)
        {
			substitui(sol, nova_sol, x.vert);
			custo = custo_viz;
        }
    }
    return custo;
}

void gera_vizinho(int a[], int b[], int c[], int n)
{
    int i, pos, pos_ant;

    for(i=0; i<n; i++) {
        b[i]=a[i];
        c[i]=a[i];
    }
	
    pos=random_l_h(0, n-1);
    if(b[pos] == 1) {
        b[pos] = 0;
    }else
        b[pos] = 1;

    pos_ant = pos;
    
    do {
        pos = random_l_h(0, n-1);
    }while(pos == pos_ant);
    
    if(c[pos] == 1)
        c[pos] = 0;
    else
        c[pos] = 1;

}

int melhorVizinho(int a[], int b[], int c[], int *mat, int vert){
    int custo_b, custo_c;

    custo_b = calcula_fit(b, mat, vert);
    custo_c = calcula_fit(c, mat, vert);

    if(custo_b == -1 && custo_c == -1){

        return -1;   
    }   
    else if(custo_c == -1) {    
        for(int i = 0; i < vert; ++i){
            a[i] = b[i];
        }

        return custo_b;
    }else if(custo_b == -1){
        for(int i = 0; i < vert; ++i){
            a[i] = c[i];
        }

        return custo_c;
        
    }else if(custo_b < custo_c){
        for(int i = 0; i < vert; ++i){
            a[i] = c[i];
        }

        return custo_c;
    }else {
        for(int i = 0; i < vert; ++i){
            a[i] = b[i];
        }

        return custo_b;
    }
}



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

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}