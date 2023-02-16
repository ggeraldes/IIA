//
// Created by glgge on 08/01/2023.
//

#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define GENERATIONS_TC  100
#define PROBGERAVIZ     1.0

float eval_individual(int sol[], struct info d, int *mat, int *v, int k){
    int total = 0;
    int i, j, h, count=-1, contadork=0;

    for (i = 0; i < d.numGenes; i++){
        if (sol[i] == 1)
        {
            for (j = 0; j < d.numGenes; j++){
                if (j>count && *(mat+i*d.numGenes+j) == 1){
                    for (h = 0; h < d.numGenes; h++)
                        if(sol[h]==1 && j==h)
                            total++;
                }

            }
            count=i;
        }
    }
    for(i=0;i<d.numGenes;i++){
        if(sol[i]==1)
            contadork++;
    }
    if(contadork==k){
        *v=1;
        return total;
    }
    else{
        *v=0;
        return -total;
    }


}



float eval_individual_reparado1(int sol[], struct info d, int * mat, int *v, int k){
    int total = 0;
    int i, j, h, count=-1, contadork=0;

    for (i = 0; i < d.numGenes; i++){
        if (sol[i] == 1)
        {
            for (j = 0; j < d.numGenes; j++){
                if (j>count && *(mat+i*d.numGenes+j) == 1){
                    for (h = 0; h < d.numGenes; h++)
                        if(sol[h]==1 && j==h)
                            total++;
                }

            }
            count=i;
        }
    }
    for(i=0;i<d.numGenes;i++){
        if(sol[i]==1)
            contadork++;
    }
    if(contadork==k){
        *v=1;
        return total;
    }
    else{
        while (contadork!=k) {

            if(contadork<k){
                while(contadork!=k) {
                    do {
                        i = random_l_h(0, d.numGenes - 1);
                    } while (sol[i] != 0);
                    sol[i] = 1;
                    contadork++;
                }
            }
            else{
                while(contadork!=k) {
                    do {
                        i = random_l_h(0, d.numGenes - 1);
                    } while (sol[i] != 1);
                    sol[i] = 0;
                    contadork--;
                }
            }




            total = 0;
            contadork = 0;
            count = -1;

            for (i = 0; i < d.numGenes; i++) {
                if (sol[i] == 1) {
                    for (j = 0; j < d.numGenes; j++) {
                        if (j > count && *(mat + i * d.numGenes + j) == 1) {
                            for (h = 0; h < d.numGenes; h++)
                                if (sol[h] == 1 && j == h)
                                    total++;
                        }

                    }
                    count = i;
                }
            }
            for(i=0;i<d.numGenes;i++){
                if(sol[i]==1)
                    contadork++;
            }
        }
        *v = 1;
        return total;
    }
}

void evaluate(pchrom pop, struct info d, int *mat, int k)
{
    int i;

    for (i=0; i<d.popsize; i++)
        pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido,k);

}




