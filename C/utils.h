int** init_dados(char *nome, int *n, int *iter);
void gera_sol_inicial(int *sol, int v);
int calculaFit(int a[], int *mat, int vert);
void escreve_sol(int *sol, int vert);
void substitui(int a[], int b[], int n);
void init_rand(void);
int random_l_h(int min, int max);
float rand_01(void);


//Parte 2
struct info leEA(char *nome_fich); // preenche uma struct info



pchrom initPop(struct info *d); // inicia populacao
chrom getMelhor(pchrom pop, struct info *d, chrom best); // devolve melhor solucao
void mostraPop(chrom x, struct info *d); // mostra uma solucao
void mostraTudo(pchrom x, struct info *d); // mostra a populacao total

int verificaValida(int *solucao, struct info *d); //valida solucao
int verificaValidaPen(int *solucao, struct info *d);//valida solucao com penalizacao
int contaNumsArray(int *solucai, int num, struct info *d); // conta um numero especifico num array
int avaliaIndividual_1(int *solucao, struct info *d, int **mat, int *valido); // penalizacao cega
float avaliaIndividual_2(int sol[], struct info d, int mat[][2], int *v); // penalizacao e reparacao

void verificaGeral_1(pchrom pop, struct info *d, int **mat); // penalizacao cega
void verificaGeral_2(pchrom pop, struct info d, int **mat); // com penalizacao e reparacao


int contaInvals(struct info *d,pchrom pop); // conta solucoes invalidas
int contaMenosUns(int *aux, int tam);


void reparacao(int *solucao, struct info *d);

//Funcoes para o ecra
void apagar_ecra(); //Funcao que deteta o sistema e apaga o ecra
void mostrarMenu();
