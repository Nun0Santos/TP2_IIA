
#include "algoritmo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include <string.h>

int* lerFicheiro(char *nome , struct info *x);
 pchrom init_pop(struct info x);
void print_pop(pchrom pop, struct info d);
chrom get_best(pchrom pop, struct info d, chrom best);
void write_best(chrom x, struct info d);
void init_rand();
int random_l_h(int min, int max);
float rand_01();
int flip();

