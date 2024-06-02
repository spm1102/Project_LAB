#ifndef ENDORSED_GRAPH_H
#define ENDORSED_GRAPH_H

#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include"cell.h"

#define MAX_VERTICES 100

struct edge_t {
    int src;
    int dest;
    int weight;
    struct edge_t* next;
};

typedef struct edge_t edge_t;

struct vertex_t {
    int x, y;
    int visited;
    int heuristic_dist;
    int total_dist_to_src;
    int preVertex;
    edge_t* edge;
};
typedef struct vertex_t vertex_t;

struct graph_t {
    int numVertices;
    vertex_t vertices[MAX_VERTICES];
};

typedef struct graph_t graph_t;


static graph_t* GRAPH_Create(cell_t grid[COLS][ROWS]);
static void GRAPH_Free(graph_t* p_graph);
static void EDGE_Add(graph_t* p_graph, int src, int dest, int weight);
static void EDGE_Free(edge_t* p_edge);
static int distance_measure(graph_t* p_graph, int source, int dest);


inline graph_t* GRAPH_Create(cell_t grid[COLS][ROWS]) {
    graph_t* p_graph = (graph_t*)malloc(sizeof(graph_t));

    int dest = TAKE_dest(grid);

    p_graph->numVertices = NUM_VERTICES;
    for(int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++){
            p_graph->vertices[COLS * i + j].x = grid[i][j].x;
            p_graph->vertices[COLS * i + j].y = grid[i][j].y;
            p_graph->vertices[COLS * i + j].visited = 0;
            p_graph->vertices[COLS * i + j].total_dist_to_src = INT_MAX;
            p_graph->vertices[COLS * i + j].preVertex = -1;
            p_graph->vertices[COLS * i + j].edge =NULL;
        }
    }

    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++) {
            p_graph->vertices[COLS * i + j].heuristic_dist = distance_measure(p_graph, COLS * i + j, dest);
        }
    }

    return p_graph;
}

inline int distance_measure(graph_t* p_graph, int source, int dest) {
    int xSRC = p_graph->vertices[source].x;
    int ySRC = p_graph->vertices[source].y;
    int xDES = p_graph->vertices[dest].x;
    int yDES = p_graph->vertices[dest].y;
    int dx = (xSRC - xDES) * (xSRC - xDES);
    int dy = (ySRC - yDES) * (ySRC - yDES);

    return (int)sqrt(dx + dy);// Mahattan distance
}

void GRAPH_Free(graph_t* p_graph) {
    free(p_graph);
}

inline void EDGE_Add(graph_t* p_graph, int src, int dest, int weight) {
    edge_t* p_edge_src = (edge_t*)malloc(sizeof(edge_t));
    p_edge_src->src = src;
    p_edge_src->dest = dest;
    p_edge_src->weight = weight;
    p_edge_src->next = p_graph->vertices[src].edge;
    p_graph->vertices[src].edge = p_edge_src;

    edge_t* p_edge_dest = (edge_t*)malloc(sizeof(edge_t));
    p_edge_dest->src = dest;
    p_edge_dest->dest = src;
    p_edge_dest->weight = weight;
    p_edge_dest->next = p_graph->vertices[dest].edge;
    p_graph->vertices[dest].edge = p_edge_dest;
}

inline void EDGE_Free(edge_t* p_edge) {
    free(p_edge);
}

#endif