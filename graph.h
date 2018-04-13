#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<stdio.h>

void count_graph(FILE*, int*, int*);
int* allocate_paths_mem(FILE*, int);
int** allocate_walks_mem(FILE*, int, int*);
void BFS_recurr(int current, int* old_chain, int carry, int points, int to, int* paths, int** walks);
void output_chain(int* chain, int chain_step);
int already(int* chain, int next, int end);

#endif
