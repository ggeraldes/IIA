//
// Created by glgge on 09/01/2023.
//

#ifndef HIBRIDO_UTILS_H
#define HIBRIDO_UTILS_H
void imprime_matriz(int *grafo, int vert);
void logtofile(chrom b, struct  info x,float mbf);
int* init_dados(char *nome, int *n,int *lig );
void init_data(char *filename, int *mat, struct  info *x , int *k);
pchrom init_pop(struct info, int k);
void print_pop(pchrom, struct info);
chrom get_best(pchrom, struct info, chrom);
void write_best(chrom, struct info);
void init_rand();
int random_l_h(int, int);
float rand_01();
int flip();
#endif //HIBRIDO_UTILS_H
