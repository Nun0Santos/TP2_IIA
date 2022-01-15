#define _CRT_SECURE_NO_WARNINGS 1
#include "globals.h"
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    char    nome_fich[100];
    int     vert, num_iter, k, runs, custo, best_custo=0, op=0;
    int     *grafo, *sol, *best,it;
	float   mbf = 0.0;

	if(argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else
        if(argc == 2)
        {
            runs = DEFAULT_RUNS;
            strcpy(nome_fich, argv[1]);
        }
        else
        {
            runs = DEFAULT_RUNS;
            printf("Nome do Ficheiro: ");
            gets(nome_fich);
        }
	if(runs <= 0)
		return 0;
	init_rand();

	// Preenche matriz de adjacencias
	grafo = init_dados(nome_fich, &vert, &num_iter);
	best = malloc(sizeof(int)*vert);
	sol = malloc(sizeof(int)*vert);

	if(sol == NULL || best == NULL){
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	printf("Iterações :");
	scanf("%d",&it);

	for(int i = 1; i<=it; i++){
		printf("Iteração: %d",it);
		for(k=0; k<runs; k++) {
			if(k != 0) {
				printf("------------------\n");
			}

			custo = trepa_colinas(sol, grafo, vert, num_iter);

			// Escreve resultados da repeticao k
			printf("\nRepeticao %d:", k);
			escreve_sol(sol, vert);
			printf("Custo final: %2d\n", custo);
			mbf += custo;
			if(k==0 || best_custo < custo){
				best_custo = custo;
				substitui(best, sol, vert);
			}
		}
	}
	// Escreve resultados globais
	printf("\n\nMBF: %f\n", mbf/k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, vert);
	printf("Custo final: %2d\n", best_custo);
	free(grafo);
	free(sol);
	free(best);
	return 0;			
					
}

