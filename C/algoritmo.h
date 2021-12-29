/* ================== TREPA COLINAS ================== */

/*Trepa colinas first-choice
  Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
  Devolve o custo da melhor solucao encontrada*/ 
int trepa_colinas(int sol[], int *mat, int vert, int num_iter);

/*Gera um vizinho
  Parametros: solucao actual, vizinho, numero de vertices
  swap two vertices*/
void gera_vizinho(int a[], int b[], int n);



//Evolutivo

typedef struct Info info;
struct info{

    //tamanho da populacao
    int popsize;

    // probabilidade de mutacao
    float pm;

    // probabilidade de recombinacao
    float pr;

    //tamanho do torneio de selecao (vai ser sempre 2)
    int tsize;

    //penalizacao
    int pen;

    // numero de subconjuntos (g)
    int numSub;

    // capacidade da solucao (m)
    int capacidade;

    // numero de geracoes
    int numGeracoes;
};

typedef struct  individual chrom, *pchrom;
struct individual {

    // solucao
    int p[10000];

    // valor da fitnesss
    int fitness;

    // flag para ver se solucao e ou nao valida
    int valido;
};





//Hibrido
void torneioSelecao(pchrom pop, struct info *d, pchrom pais); //torneio binario
void recombinacao(pchrom pais, struct info *d, pchrom filhos); // ponto de corte
void mutacao(pchrom filhos, struct info *d); // mutacao



