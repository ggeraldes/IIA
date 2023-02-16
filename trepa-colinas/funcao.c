//
// Created by glgge on 08/01/2023.
//

#include "funcao.h"

int calcula_fit(int a[], int *mat, int vert, int k){
    int total = 0;
    int i, j, h, count=-1, contadork=0;

    for (i = 0; i < vert; i++){
        if (a[i] == 1){

            for (j = 0; j < vert; j++){
                if (j>count && *(mat+i*vert+j) == 1){
                    for (h = 0; h < vert; h++)
                        if(a[h]==1 && j==h)
                            total++;
                }

            }
            count=i;
        }
    }
    for(i=0;i<vert;i++){
        if(a[i]==1)
            contadork++;
    }
    if(contadork==k)
        return total;
    else
        return 0;
}
