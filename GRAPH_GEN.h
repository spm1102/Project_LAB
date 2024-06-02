#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include"endorsed_graph.h"


static graph_t* GEN_GRAPH_Create(cell_t grid[COLS][ROWS]);

graph_t* GEN_GRAPH_Create(cell_t grid[COLS][ROWS]) {

    graph_t* p_graph = GRAPH_Create(grid);
    

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            int currentVertex = grid[i][j].vertex;

            // Add edges to the adjacent vertices
            if(!IS_wall(i, j, grid)){

                if (i > 0) {
                    if(IS_wall(i - 1, j, grid)){
                        continue;
                    }
                    int topVertex = grid[i - 1][j].vertex;
                    EDGE_Add(p_graph, currentVertex, topVertex, 1);
                }
                if (i < COLS - 1) {
                    if(IS_wall(i + 1, j, grid)){
                        continue;
                    }
                    int bottomVertex = grid[i + 1][j].vertex;
                    EDGE_Add(p_graph, currentVertex, bottomVertex, 1);
                }
                if (j > 0) {
                    if(IS_wall(i, j - 1, grid)){
                        continue;
                    }
                    int leftVertex = grid[i][j - 1].vertex;
                    EDGE_Add(p_graph, currentVertex, leftVertex, 1);
                }
                if (j < ROWS - 1) {
                    if(IS_wall(i, j + 1, grid)){
                        continue;
                    }
                    int rightVertex = grid[i][j + 1].vertex;
                    EDGE_Add(p_graph, currentVertex, rightVertex, 1);
                }
            }
        }
    }

    return p_graph;
}

#endif