/* ================== TREPA COLINAS ================== */

/*Trepa colinas first-choice
  Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
  Devolve o custo da melhor solucao encontrada*/ 
int trepa_colinas(int sol[], int *mat, int vert, int num_iter);

/*Gera um vizinho
  Parametros: solucao actual, vizinho, numero de vertices
  swap two vertices*/
void geraVizinho(int *solucao, int *nova_solucao, int m);



//Evolutivo

typedef struct Info info;
struct info{
  
  int popsize; //tamanho da populacao
  float pm; // probabilidade de mutacao
  float pr; // probabilidade de recombinacao
  int tsize;//tamanho do torneio de selecao (vai ser sempre 2)
  int pen; //penalizacao
  int numSub; // numero de subconjuntos (g)
  int capacidade; // capacidade da solucao (m)
  int numGeracoes; // numero de geracoes
};


typedef struct  individual chrom, *pchrom;
struct individual {

  int p[10000];   // solucao
  int fitness;  // valor da qualidade da soluçao
  int valido;  // flag para ver se solucao e ou nao valida
};

//Hibrido
void torneioSelecao(pchrom pop, struct info *d, pchrom pais); //torneio binario
void recombinacao(pchrom pais, struct info *d, pchrom filhos); // ponto de corte
void mutacao(pchrom filhos, struct info *d); // mutacao



