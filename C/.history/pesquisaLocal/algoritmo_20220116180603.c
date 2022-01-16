#include "algoritmo.h"
#include "globals.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho 1, vizinho 2, numero de vertices
//swap two vertices
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

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int custo, custo_viz, i;
    double prob;

	int vizinho1[vert];
    int vizinho2[vert];
    int nova_sol[vert];

    do {   //Com ciclo 
        //Gere sol inicial
        gera_sol_inicial(sol, vert);			

        //Calcula fitness de sol inicial
        custo = calcula_fit(sol, mat, vert);
        //printf("12");
    }while(custo == -1); //Enquanto o custo da solucao inicial for -1 (ser invalida) originar outra

    
    //Escrever sol inicial
    escreve_sol(sol, vert);
    printf("Custo inicial = %d\n", custo);
    
    for(i=0; i<num_iter; i++)
    {
		do{
            // Gera vizinho
            gera_vizinho(sol, vizinho1, vizinho2, vert);
            // Avalia melhor vizinho
            custo_viz = melhorVizinho(nova_sol, vizinho1, vizinho2, mat, vert);
        }while(custo_viz == -1);
        
        if(custo_viz >= custo) // maior 1º
        {
			substitui(sol, nova_sol, vert);
			custo = custo_viz;
        }
    }
    return custo;
}