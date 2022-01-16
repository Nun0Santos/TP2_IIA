#define _CRT_SECURE_NO_WARNINGS 1

#include "utils.h"

// Inicializa��o do gerador de n�meros aleat�rios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Leitura dos par�metros e dos dados do problema
// Par�metros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Par�metros de sa�da: Devolve a estrutura com os par�metros
int* lerFicheiro(char *nome , struct info *x)
{

	x->popsize = 20; 

	x->pm = 0.05; 
	x->pr = 0.7; 

	x->tsize = 2; //Torneio
	x->numGenerations = 2500;
	x->ro = 0.5; //penalização


	if (x->vert > MAX_OBJ){
		printf("Numero é superior ao MAX_OBJ\n");
		exit(1);
	}

	FILE *f;
	int *p , i , arestas;

	f=fopen(nome, "rt");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
    char c;
    fscanf(f," %c",&c);
    while(c == 'c')
    {
        fscanf(f," %*[^\n]");
        fscanf(f," %c",&c);
    }
    if(c == 'p')
    {
        fscanf(f," edge %d %d", &x->vert , &arestas);
    }
    // Alocacao dinamica da matriz
	p = malloc(sizeof(int)*(x->vert)*(x->vert));
	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}

	// Preenchimento da matriz
    int vert1,vert2;
	for(i=0; i < arestas; i++){

        fscanf(f," e %d %d",&vert1,&vert2);
        p[(vert1 - 1)*( x->vert ) + ( vert2 - 1 )] = 1;
		p[(vert2 - 1)*( x->vert ) + ( vert1 - 1 )] = 1;
    }
    fclose(f);
    return p;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Par�metro de entrada: Estrutura com par�metros do problema
// Par�metro de sa�da: Preenche da estrutura da popula��o apenas o vector bin�rio com os elementos que est�o dentro ou fora da mochila
pchrom init_pop(struct info x)
{
	int     i, j, r;
	pchrom  indiv;

	indiv = malloc(sizeof(chrom)*x.popsize);
	if (indiv==NULL){
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	
	for (i=0 ; i < x.popsize ; i++)
	{
		for (j=0; j < x.vert ; j++)
			indiv[i].p[j] = 0;
	}

	i = j = 0;
	
        for(i=0 ; i < x.popsize ; i++){
			int num_verts_sol = random_l_h(0, x.vert-1);
			for(j = 0; j < num_verts_sol; j++){
				do{
					r = random_l_h(0, x.vert -1);
				}while(indiv[i].p[r] != 0);
				indiv[i].p[r] = 1;
			}
		}
		
	return indiv;
}

// Actualiza a melhor solu��o encontrada
// Par�metro de entrada: populacao actual (pop), estrutura com par�metros (d) e a melhor solucao encontrada at� a gera��oo imediatamente anterior (best)
// Par�metro de sa�da: a melhor solucao encontrada at� a gera��o actual
chrom get_best(pchrom pop, struct info d, chrom best)
{
	int i;

	for (i=0; i<d.popsize; i++) //popsize é o tamanho do array pop
	{
		if (best.fitness < pop[i].fitness && pop[i].valido == 1)
			best=pop[i];
	}
	return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
	return ((float)rand())/(float)RAND_MAX;
}

// Escreve uma solu��o na consola
// Par�metro de entrada: populacao actual (pop) e estrutura com par�metros (d)
void write_best(chrom x, struct info d)
{
	int i;

	printf("\nMelhor Individual: %4.1f\n", x.fitness);
	for (i=0; i<d.vert; i++)
		printf("%d", x.p[i]);
		
	putchar('\n');
}

int verificaValidaPen(int *solucao, struct info *d){
    int n = d->capacidade / d->numSub;
    int contador = 0, aux = 0, penalidade = 0;

    for(int i = 0; i < d->capacidade; i++){
        aux = solucao[i];
        for(int j = 0; j < d->capacidade; j++){
            if(solucao[j] == aux)
                contador++;
        }
        if(contador == n)
            contador = 0;
        else{
            penalidade += contador;
            contador = 0;
            }
    }

    return penalidade;

}
int avaliaIndividual_1(int *solucao, struct info *d, int **mat, int *valido){
    int n = d->capacidade / d->numSub;
    int aux[n];
    int conta = d->numSub-1;
    int soma = 0;

    // verifica sem penalizacao
    if(!evaluate(solucao,d)){
            *valido = 0;
            return -1;
        }
        else{
            *valido = 1;
    }

    for(int i = 0; i < n; i++)
        aux[i] = 0;

    // enquanto conta >= 0
    while(conta >= 0){
        for(int i = 0, j = 0; i < d->capacidade; i++){
            if(solucao[i] == conta){
                aux[j] = i;
                j++;
            }
        }

        for(int i = 0; i < n-1; i++){
            for(int j = i+1; j < n; j++){
                soma +=  mat[aux[i]][aux[j]];
            }
        }

        for(int i = 0; i < n; i++)
            aux[i] = 0;

        conta--;
    }

    return soma;
}

void verificaGeral_1(pchrom pop, struct info *d, int **mat){

    for(int i = 0; i < d->popsize; i++){
        pop[i].fitness = avaliaIndividual_1(pop[i].p,d,mat,&pop[i].valido);

    }
}
