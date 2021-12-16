#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[]){
    char nome_fich[100];
    int vert, num_iter, k, runs, custo, best_custo=0,op;
    int *grafo, *sol, *best;
    float   mbf = 0.0;

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
    grafo = init_dados(nome_fich,&vert,&num_iter);

    /* ================== MENU ================== */
    printf("1- Trepa Colinas\n");
    printf("2- Algoritmo Evolutivo\n");
    printf("3- Algoritmo Hibrido\n");

    printf("Escolha: ");scanf("%d",&op);



}                                                                                           