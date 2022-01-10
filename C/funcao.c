#include "funcao.h"

// Calcula a qualidade de uma solu��o
// Recebe:  A solu��o, a, a matriz de adjac�ncias, mat, e o n�mero de v�rtices, vert
// Devolve: O custo que � o n�mero de liga��es que existem na solu��o
int calcula_fit(int a[], int *mat, int vert)
{
	int total=0;
	int i, j;

	for(i=0; i<vert; i++)
		if(a[i]==1)
		{
            for (j = 0; j < vert; ++j) {
                if(a[j] == 1 && mat[i*vert+j] == 1){ 
                    return -1;
                }
            }
		}

    for (int k = 0; k < vert; ++k) {
        if(a[k] == 1){
            ++total;
        }
    }
	
    return total;
}



int melhorVizinho(int a[], int b[], int c[], int *mat, int vert){
    int custo_b, custo_c;

    custo_b = calcula_fit(b, mat, vert);
    custo_c = calcula_fit(c, mat, vert);

    if(custo_b == -1 && custo_c == -1){

        return -1;   
    }   
    else if(custo_c == -1) {    
        for(int i = 0; i < vert; ++i){
            a[i] = b[i];
        }

        return custo_b;
    }else if(custo_b == -1){
        for(int i = 0; i < vert; ++i){
            a[i] = c[i];
        }

        return custo_c;
        
    }else if(custo_b < custo_c){
        for(int i = 0; i < vert; ++i){
            a[i] = c[i];
        }

        return custo_c;
    }else {
        for(int i = 0; i < vert; ++i){
            a[i] = b[i];
        }

        return custo_b;
    }
}
