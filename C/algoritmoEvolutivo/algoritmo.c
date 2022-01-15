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