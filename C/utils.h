#include "globals.h"

int* init_dados(char *nome, int *n, int *iter);
void init_rand(void);

/* ========== Funções -> Algoritmos Evolutivos ========== */
struct info leEA(char *nome_fich); // preenche uma struct info
pchrom initPop(struct info *d); // inicia populacao
void mostraPop(chrom x, struct info *d); // mostra uma solucao
chrom getMelhor(pchrom pop, struct info *d, chrom best); // devolve melhor solucao
void escreveMelhor(chrom x, struct info d);
void init_rand(); // inicializa o gerador de nrs aleatorios
int random_l_h(int min,int max); // devolve um int aleatorio num intervalor
float rand_01(); //devolve um valor entre 0 e 1
int flip();
