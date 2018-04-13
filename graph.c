#include "graph.h"
#include<stdio.h>
#include<stdlib.h>

void BFS_recurr(int current, int* old_chain, int carry, int points, int to, int* paths, int** walks)
{
    int i, paths_checked = 0;
    int chain_step = carry;
    int* chain = malloc((points+1) * sizeof(int));

    for (i = 0; i < points+1; i++)
        chain[i] = 0;

    for (i = 0; i < chain_step; i++)
        chain[i] = old_chain[i]; 
    
    chain[chain_step] = current;
    chain_step++;

    if ((current == to)&&(chain[1] != 0))
    {
        output_chain(chain, chain_step);
        free(chain);
        return;
    }

    for (paths_checked = 0; paths_checked < paths[current-1]; paths_checked++)
        {   
            if (walks[current-1][paths_checked] == to)
                BFS_recurr(walks[current-1][paths_checked], chain, chain_step, points, to, paths, walks);
            
            else
                if (already(chain, walks[current-1][paths_checked], chain_step) == 1) 
                    continue;
                else   
                    BFS_recurr(walks[current-1][paths_checked], chain, chain_step, points, to, paths, walks);    
        }

    free(chain);
}

int already(int* chain, int next, int end)
{
    int i;
    for (i = 0; i < end; i++)
        if (chain[i] == next)
            return 1;
    return 0;
}

void output_chain(int* chain, int chain_step)
{
    int i;
    FILE* out = fopen("output.txt", "a");
    for (i = 0; i < chain_step; i++)
    {
        printf("%d ", chain[i]);
        fprintf(out, "%d ", chain[i]);
    }
    printf("\n");
    fprintf(out, "\n");
    fclose(out);
}

int* allocate_paths_mem(FILE* in, int points)
{
    rewind(in);
    int* paths = malloc(points*sizeof(int));
    int i; 
    for (i = 0; i < points; i++)
        paths[i] = 0;

    int temp;
    for(i = 0; fscanf(in, "%d", &temp) != EOF; i++)
        if ((i % 2) == 0)
            paths[temp-1]++;

    return paths;
}

int** allocate_walks_mem(FILE* in, int points, int* paths)
{
    rewind(in);
    int step, i, j, temp;
    int** walks = malloc(points*sizeof(int*));

    for (i = 0; i < points; i++)
        walks[i] = malloc(paths[i] * sizeof(int));

    for(i = j = step = 0; fscanf(in, "%d", &temp) != EOF; step++)
        {
            if ((step % 2) != 0)
            {
                walks[i][j] = temp;
                j++;
            };

            if (j == paths[i])
            {
                j = 0;
                i++;
            }
        };

    return walks;
}

void count_graph(FILE* in, int* p, int* e)
{
    rewind(in);
    int temp;
    int i;
    for(i = 0; fscanf(in, "%d", &temp) != EOF; i++)
        if ((i % 2) == 0)
        {
            (*e)++;
            if (temp > (*p))
                (*p) = temp;
        }
        else
        {
            if (temp > (*p))
                (*p) = temp;
        }
}
