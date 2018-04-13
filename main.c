#include "graph.h"
#include<stdio.h>
#include<stdlib.h>

int main (int argc, char** argv)
{
    printf("Welcome to BFS simulator\nThis program is designed to find all paths from M in a certain graph\n");

    int points = 0;
    int edges = 0;
    int from, to;
    int* paths;
    int** walks;
    int mode;

    if ((argc != 3)&&(argc != 2))
    {
        printf("\nPlease, enter M and N values (decimal positive) via Standard Input and relaunch the program\n");
        return 1;
    }
    else
    {
        if (argc == 3) 
            {
                mode = 1;
                printf("The program has been launched in Mode 1 (searching ways from M to N)");
            }
        else 
            {
                to = 1;
                mode = 2;
                printf("The program has been launched in Mode 2 (searching ways from M to every other point)");
            }

        from = atoi(argv[1]);
        if (mode == 1) to = atoi(argv[2]);
        if ((from <= 0)||(to <= 0))
            {
                printf("\nPlease, enter M and N values (decimal positive) via Standard Input and relaunch the program\n");
                return 1;
            }
    };

    remove("output.txt");
    FILE* in = fopen("input.txt", "r");

    if (in == NULL) 
    {
        printf("Please, fill the input.txt text file correctly and relaunch the program\n");
        return 2;
    }
    else
    {
        count_graph(in, &points, &edges);
            if ((from > points)||(to > points))
                {
                    printf("\nThe graph does not contain entered points\n");
                    return 3;
                }
        paths = allocate_paths_mem(in, points);
        walks = allocate_walks_mem(in, points, paths); 
        fclose(in);
    }

    printf("\n\n[The graph contains]\nPoints: %d\nEdges: %d\n", points, edges);
    printf("The program will search for ways from point %d to point %d\n", from, to);
    printf("\nPress [ENTER] to start computing\n"); getchar();

// uncomment to see contents of paths and walks
/* 
    int i, j;
    for (i = 0; i < points; i++)
        printf("%d ", paths[i]);
    printf("\n");

    for (i = 0; i < points; i++)
    {
        for (j = 0; j < paths[i]; j++)
            printf("%d ", walks[i][j]);
        printf("\n");
    }
*/
    printf("The program has found the following paths:\n");
    if (mode == 1)
        BFS_recurr(from, paths, 0, points, to, paths, walks);
    else
    {  
        for (to = 1; to <= points; to++)
            BFS_recurr(from, paths, 0, points, to, paths, walks);
    }

    printf("\nAll data is saved in output.txt\nBFS Simulator (C) Alexey Haidukevich, WE PW 2018\n");
    return 0;
}