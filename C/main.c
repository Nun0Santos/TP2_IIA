#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[]){
    char nome_fich[100];
    int vert, num_iter, k, runs, custo, best_custo = 0,op = 0;
    int **matriz, *sol, *best;
    float mbf = 0.0;

    //Parte 2
    int rondas = 15;
    struct info EA_param;
    pchrom pop = NULL, pais = NULL;
    chrom melhor_ronda_atual, melhor_ronda_final;
    int geracao_atual;
    int solucoes_invalidas;

    int x;
    int g ,n;

    apagar_ecra();

    if(argc == 3){
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    }
    else
    if(argc == 2){
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    }else{
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
    if(runs <= 0)
        return 0;

    init_rand(); //Inicializa numeros aleatorios

    matriz = init_dados(nome_fich, &vert, &num_iter);



    /* ================== Programa ================== */
    while(1){
        mostrarMenu();
        scanf("%d",&op);

        if(op == -1)
            break;
        if(op == 1){     // ================= Trepa Colinas ===================
                    sol = malloc(sizeof(int)*vert);
                    best = malloc(sizeof(int)*vert);


                    printf("\nSolução inicial");
                    for(k = 0 ; k < runs ; k++){
                        printf("\nRepeticao %d:", k);
                        // Gerar solucao inicial
                        gera_sol_inicial(sol, vert);
                        escreve_sol(sol, vert);
                        // Trepa colinas
                        custo = trepa_colinas(sol, matriz, vert, num_iter);
                        // Escreve resultados da repeticao k

                        escreve_sol(sol, vert);
                        printf("Custo final: %2d\n", custo);
                        mbf += custo;

                        if(k==0 || best_custo > custo)
                        {
                            best_custo = custo;
                            substitui(best, sol, vert);
                        }
                    }

                    // Escreve eresultados globais
                    printf("\n\nMBF: %f\n", mbf/k);
                    printf("\nMelhor solucao encontrada");
                    escreve_sol(best, vert);
                    printf("Custo final: %2d\n", best_custo);

                   // free(matriz);             ========= Se tivermos isto comentado nao podemos voltar a correr o programa infinitamente
                    free(sol);
                    free(best);
                    op = -1;
                    
            }
            if(op == 2){    //============= Evolutivo ==================

                //preencher a struct EA_param
                EA_param = leEA(nome_fich);

                for(x  = 0; x < rondas; x++ ){
                    printf("\nRepeticao %d\n",x+1);
                    printf("--------------------");

                    //geracao da populacao inicial
                    pop = initPop(&EA_param);

                    geracao_atual = 1;

                    melhor_ronda_atual = pop[0];

                    // encontra-se a melhor solucao dentro de toda a populacao
                    melhor_ronda_atual = getMelhor(pop,&EA_param,melhor_ronda_atual);

                    //mostraPop(melhor_ronda_atual,&EA_param);

                    pais = malloc(sizeof(chrom)*EA_param.popsize);
                    if(pais == NULL){
                        printf("Erro na alocacao de memoria\n");
                        exit(1);
                    }

                    while(geracao_atual <= EA_param.numGeracoes){
                        //torneio binario
                        torneioSelecao(pop,&EA_param,pais);

                        //crossover
                        recombinacao(pais,&EA_param,pop);

                        //mutacao
                        mutacao(pop,&EA_param);


                        //avalia a nova pop
                        verificaGeral_2(pop, EA_param,matriz);


                        //atualizar a melhor solucao encontrada
                        melhor_ronda_atual = getMelhor(pop,&EA_param,melhor_ronda_atual);

                        //incrementamos a geracao atual
                        geracao_atual++;
                    }

                    //Escreve resultados da repeticao que terminou
                    solucoes_invalidas = contaInvals(&EA_param,pop);

                    printf("\nNa repeticao %d a melhor solucao foi: ",x+1);
                    mostraPop(melhor_ronda_atual,&EA_param);
                    printf("Media de solucoes invalidas: %.2f\n",(float)solucoes_invalidas/EA_param.popsize);
                    printf("--------------------\n");

                    mbf += melhor_ronda_atual.fitness;

                    if(x == 0 || melhor_ronda_atual.fitness > melhor_ronda_final.fitness)
                        melhor_ronda_final = melhor_ronda_atual;

                    free(pais);
                    free(pop);
                }

                printf("\n\nMBF: %f\n", mbf/x);
                printf("\nMelhor solucao encontrada");
                mostraPop(melhor_ronda_final,&EA_param);
                op = -1;

            }
            if(op == 3){     //===================== Hibrido =====================

                //preencher a struct EA_param
                EA_param = leEA(nome_fich);

                for(x  = 0; x < rondas; x++ ){
                    printf("\nRepeticao %d\n",x+1);
                    printf("--------------------");

                    //geracao da populacao inicial
                    pop = initPop(&EA_param);

                    // avalia populacao inicial
                    verificaGeral_1(pop,&EA_param,matriz);

                    // HIBRIDO 1
                    for(int i = 0; i < EA_param.popsize; i++){

                        //pop[i].fitness = trepaColinas(pop[i].p, matriz, vert, num_iter);

                    }
                    geracao_atual = 1;

                    melhor_ronda_atual = pop[0];

                    // encontra-se a melhor solucao dentro de toda a populacao
                    melhor_ronda_atual = getMelhor(pop,&EA_param,melhor_ronda_atual);

                    //mostraPop(melhor_ronda_atual,&EA_param);

                    pais = malloc(sizeof(chrom)*EA_param.popsize);
                    if(pais == NULL){
                        printf("Erro na alocacao de memoria\n");
                        exit(1);
                    }

                    while(geracao_atual <= EA_param.numGeracoes){
                        //torneio binario
                        torneioSelecao(pop,&EA_param,pais);

                        //aplicar os operadores geneticos

                        //crossover
                        recombinacao(pais,&EA_param,pop);

                        //mutacao
                        mutacao(pop,&EA_param);


                        //avalia a nova pop
                        verificaGeral_1(pop,&EA_param,matriz);


                        //atualizar a melhor solucao encontrada
                        melhor_ronda_atual = getMelhor(pop,&EA_param,melhor_ronda_atual);

                        //incrementamos a geracao atual
                        geracao_atual++;
                    }


                    /*
                    // HIBRIDO 2
                    for(int i = 0; i < EA_param.popsize; i++){
                        pop[i].fitness = trepaColinas(pop[i].p,matriz,m,g,n,num_iter);
                    }
                    // chamamos a getMelhor porque o Hibrido2 pode melhorar
                    melhor_ronda_atual = getMelhor(pop,&EA_param,melhor_ronda_atual);
                    */


                    //Escreve resultados da repeticao que terminou
                    solucoes_invalidas = contaInvals(&EA_param,pop);

                    printf("\nNa repeticao %d a melhor solucao foi: ",x+1);
                    mostraPop(melhor_ronda_atual,&EA_param);
                    printf("Media de solucoes invalidas: %.2f\n",(float)solucoes_invalidas/EA_param.popsize);
                    printf("--------------------\n");

                    mbf += melhor_ronda_atual.fitness;

                    if(x == 0 || melhor_ronda_atual.fitness > melhor_ronda_final.fitness)
                        melhor_ronda_final = melhor_ronda_atual;

                    free(pais);
                    free(pop);
                }

                printf("\n\nMBF: %f\n", mbf/x);
                printf("\nMelhor solucao encontrada");
                mostraPop(melhor_ronda_final,&EA_param);
                op = -1;

            }
            if(op == 4){
                    break;
            }    
            
    }
    
}
