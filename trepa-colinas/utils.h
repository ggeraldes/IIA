//
// Created by glgge on 08/01/2023.
//

#ifndef NOVA_PASTA_UTILS_H
#define NOVA_PASTA_UTILS_H
void logtofile(int num_iter,int best ,float mbf);
int* init_dados(char *nome, int *n, int *k);
void gera_sol_inicial(int *sol, int v, int k);
void escreve_sol(int *sol, int vert);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();
int flip();
void imprime_matriz(int *grafo, int vert);
#endif //NOVA_PASTA_UTILS_H
