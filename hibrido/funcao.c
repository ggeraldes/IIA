//
// Created by glgge on 09/01/2023.
//

#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#define PROB 0.01
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


            do {
                i = random_l_h(0, d.numGenes - 1);
            } while (sol[i] != 0);


            sol[i] = 1;

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


float eval_individual_reparado2(int sol[], struct info d, int mat[][2], int *v)
{

}


void evaluate(pchrom pop, struct info d, int *mat, int k)
{
    int i;

    for (i=0; i<d.popsize; i++)
        pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido,k);
}

void gera_vizinho(int sol[], int solViz[], int *mat, int nGenes)
{
    int i, menorCustoIn, maiorCustoOut, p1, p2;

    for (i=0; i < nGenes; i++)
        solViz[i] = sol[i];
    if (rand_01() < PROBGERAVIZ)
    {
        i = random_l_h(0, nGenes-1);
        solViz[i] = !solViz[i];
    }
    else
    {
        menorCustoIn = MAX_OBJ;
        maiorCustoOut = 0;
        for (i=0; i < nGenes; i++)
        {
            if (sol[i] == 1 && menorCustoIn > *mat)
            {
                menorCustoIn = *mat;
                p1 = i;
            }
            if (sol[i] == 0 && maiorCustoOut < *mat)
            {
                maiorCustoOut = *mat;
                p2 = i;
            }
        }
        solViz[p1] = 0;
        solViz[p2] = 1;
    }
}

void trepa_colinas(pchrom pop, struct info d, int *mat, int k)
{
    int     i, j;
    chrom   vizinho;

    for (i=0; i<d.popsize; i++)
    {
        for (j=0; j<GENERATIONS_TC; j++)
        {
            gera_vizinho(pop[i].p, vizinho.p, mat, d.numGenes);
            vizinho.fitness = eval_individual(vizinho.p, d, mat, &vizinho.valido, k);
            if (vizinho.fitness >= pop[i].fitness)
                pop[i] = vizinho;
            else
            {
                if(rand_01() < PROB)
                {
                    pop[i] = vizinho;
                }
            }
        }
    }
}

