#include "globals.h"
#include "algoritmo.h"
#include "utils.h"

#define PROB 0.1

void geraVizinho(int *solucao, int *nova_solucao, int m)
{
  int p_ponto, s_ponto, temp = 0;
    // copiar a solucao para a nova solucao
    for(int i = 0; i < m; i++)
        nova_solucao[i] = solucao[i];

    // gerar um indice aleatorio
    p_ponto = random_l_h(0, m-1);

    // gerar um indice aleatorio
    do{
        s_ponto = random_l_h(0,m-1);

    }while(nova_solucao[s_ponto] == nova_solucao[p_ponto]);

    // substitui os valores
    temp = nova_solucao[p_ponto];
    nova_solucao[p_ponto] = nova_solucao[s_ponto];
    nova_solucao[s_ponto] = temp;

}


int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;
    int *nova_sol2 , custo_viz2;

    nova_sol = malloc(sizeof(int)*vert);
    nova_sol2 = malloc(sizeof(int)*vert);

    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    if(nova_sol2 == NULL)
    {
        printf("Erro na alocalao de memoria");
        exit(1);
    }

    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
		gera_vizinho(sol, nova_sol, vert);
        gera_vizinho(sol,nova_sol2,vert);

        custo_viz = calcula_fit(nova_sol, mat, vert);
        custo_viz2 = calcula_fit(nova_sol2 , mat , vert);

        if(custo_viz < custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        else{

            if(rand_01() < PROB){
                substitui(sol,nova_sol,vert);
                custo = custo_viz;
            }
        }
	}

    free(nova_sol);
    free(nova_sol2);
    return custo;
}


//Parte 2

void torneioSelecao(pchrom pop, struct info *d, pchrom pais){
    int a,b;


    for(int i = 0; i < d->popsize;i++){

        //gero um indice aleatorio
        a = random_l_h(0,(d->popsize-1));

        // gero outro indice aleatorio ate ambos serem diferentes
        do
            b = random_l_h(0,(d->popsize-1));
        while(a == b);

        if(pop[a].fitness > pop[b].fitness)
            pais[i] = pop[a];
        else
            pais[i] = pop[b];
    }
}


void recombinacao(pchrom pais, struct info *d, pchrom filhos){

    //ponto de corte aleatorio
    int ponto,j;

    for(int i = 0; i < d->popsize; i+=2){

        // vai haver ponto de corte
        if(rand_01() < d->pr){
            ponto = random_l_h(0, d->capacidade-1);
            for(j = 0; j < ponto; j++){
                // passamos ao mesmo tempo os numeros ate ao ponto de corte
                filhos[i].p[j] = pais[i].p[j];
                filhos[i+1].p[j] = pais[i+1].p[j];
            }
            // preenchemos o primeiro filho
            if(j == ponto){
                for(int x = j; x < d->capacidade; x++)
                    filhos[i].p[x] = pais[i+1].p[x];
            }
            // preenchemos o segundo filho
            j = ponto;
            for(int x = j; x < d->capacidade; x++)
                filhos[i+1].p[x] = pais[i].p[x];
        }

        else{
            // faz uma copia exata porque nao houve a pr
            filhos[i] = pais[i];
            filhos[i+1] = pais[i+1];
        }
    }
}



void mutacao(pchrom filhos, struct info *d){
    int num;

    for(int i = 0; i < d->popsize; i++){
        for(int j = 0; j < d->capacidade; j++){
            if(rand_01() < d->pm){

                // encontramos um nr aleatorio != do nr atual
                do{
                    num = random_l_h(0,(d->numSub-1));
                }while(num == filhos[i].p[j]);

                // alteramos o nr atual pelo num
                filhos[i].p[j] = num;
            }
        }
    }
}