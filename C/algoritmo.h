/* ================== TREPA COLINAS ================== */

/*Trepa colinas first-choice
  Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
  Devolve o custo da melhor solucao encontrada*/ 
int trepa_colinas(int sol[], int *mat, int vert, int num_iter);

/*Gera um vizinho
  Parametros: solucao actual, vizinho, numero de vertices
  swap two vertices*/
void gera_vizinho(int a[], int b[], int n);