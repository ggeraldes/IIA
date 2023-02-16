//
// Created by glgge on 08/01/2023.
//


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS	10

int main(int argc, char *argv[])
{
    char        nome_fich[100];
    struct info EA_param;
    int         mat[MAX_OBJ][MAX_OBJ], runs, i;
    pchrom      pop = NULL, parents = NULL;
    chrom       best_run, best_ever;
    int         gen_actual, r, inv, kFile;
    float       mbf = 0.0;


    EA_param.popsize = 50; //tamanho da população
    EA_param.pr = 0.7;     //probabilidade de recombinação
    EA_param.pm = 0.01;    //probabilidade de mutação
    EA_param.tsize = 80;    //tamanho do torneio
    EA_param.numGenerations = 1000;  //numero de geracoes




    printf("Nome do Ficheiro: ");
    gets(nome_fich);
    printf("Numero de iterações:");
    scanf("%d", &runs);

    if (runs <= 0)
        return 0;

    init_rand();

    init_data(nome_fich, *mat, &EA_param, &kFile);

    for (r=0; r<runs; r++)
    {
        printf("Repeticao %d\n",r);
        // Gera��o da popula��o inicial
        pop = init_pop(EA_param, kFile);
        // Avalia a popula��o inicial
        evaluate(pop, EA_param, *mat, kFile);
        // Como ainda n�o existe, escolhe-se como melhor solu��o a primeira da popula��o (poderia ser outra qualquer)
        best_run = pop[0];
        // Encontra-se a melhor solu��o dentro de toda a popula��o
        best_run = get_best(pop, EA_param, best_run);
        // Reserva espa�o para os pais da popula��o seguinte
        parents = malloc(sizeof(chrom)*EA_param.popsize);
        // Caso n�o consiga fazer a aloca��o, envia aviso e termina o programa
        if (parents==NULL)
        {
            printf("Erro na alocacao de memoriaa\n");
            exit(1);
        }

        // Ciclo de optimiza��o
        gen_actual = 1;
        while (gen_actual <= EA_param.numGenerations)
        {
            // Torneio bin�rio para encontrar os progenitores (ficam armazenados no vector parents)
            tournament(pop, EA_param, parents);
            // Torneio de k elementos, com k >= 2, para encontrar os progenitores (ficam armazenados no vector parents)
            // Exerc�cio 4.5
            //tournament_geral(pop, EA_param, parents);
            // Aplica os operadores gen�ticos aos pais (os descendentes ficam armazenados na estrutura pop)
            genetic_operators(parents, EA_param, pop);
            // Avalia a nova popula��o (a dos filhos)
            evaluate(pop, EA_param, *mat, kFile);
            // Actualiza a melhor solu��o encontrada
            best_run = get_best(pop, EA_param, best_run);
            gen_actual++;
        }


        for (inv=0, i=0; i<EA_param.popsize; i++)
            if (pop[i].valido == 0)
                inv++;

        // Escreve resultados da repeti��o que terminou
        write_best(best_run, EA_param);
        printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
        mbf += best_run.fitness;
        if (r==0 || best_run.fitness > best_ever.fitness)
            best_ever = best_run;
        // Liberta a mem�ria usada
        free(parents);
        free(pop);
    }
    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf/r);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, EA_param);
    logtofile(best_ever, EA_param,mbf/r);
    return 0;
}