#ifndef ALG
#define ALG

#define MAX_OBJ 1000		// Numero maximo (de objectos ) de numGenes

// EStrutura para armazenar parametros
struct info
{
    // Tamanho da popula��o
    int     popsize; // número de soluções
    float   pm;  // Probabilidade de muta��o
    float   pr;// Probabilidade de recombina��o
	int     tsize;// Tamanho do torneio para sele��o do pai da pr�xima gera��o
	float   ro; //// Constante para avalia��o com penaliza��o
  //int     numGenes; // obj // numero máximo de objetos das nossas sol
	int     vert; //NumVertices
    int     *iter;
    int numSub; //(G)
    int capacidade;  // capacidade da solucao (m)
	// N�mero de gera��es
    int     numGenerations;  //max_gen
};

// Individuo (solu��o)
typedef struct individual chrom, *pchrom;

struct individual
{
    // Solu��o (objetos que est�o dentro da mochila)
    int     p[MAX_OBJ]; // tem 1 se o objeto pertence à solução, zero se não
	float   fitness;// Valor da qualidade da solu��o
	int     valido;// 1 se for uma solu��o v�lida e 0 se n�o for
};

void tournament(pchrom pop, struct info d, pchrom parents);
void genetic_operators(pchrom parents, struct info d, pchrom offspring);
void crossover(pchrom parents, struct info d, pchrom offspring);
void mutation(pchrom offspring,struct info d);


#endif