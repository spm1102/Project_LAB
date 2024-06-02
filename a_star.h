#ifndef A_STAR_H
#define A_STAR_H


#include"a_star_queue.h"

static void a_star_queue (graph_t* p_graph, int startVertex, int destination, void (*GUI_displaypPath)(graph_t* p_graph));

void a_star_queue(graph_t* p_graph, int startVertex, int destination, void (*GUI_displaypPath)(graph_t* p_graph)) {
    queue_t* p_queue = NULL;
    p_queue = QUEUE_Create();
    p_graph->vertices[startVertex].total_dist_to_src = 0;
    QUEUE_Put(p_queue, startVertex, 0, p_graph);
    while(p_queue->front != NULL) {
        node_heap_t* minNode = QUEUE_Get(p_queue);
        int currentVertex = minNode->vertexName;
        NODE_HEAP_Free(minNode);

        if(currentVertex == destination){
            break;
        }

        if(p_graph->vertices[currentVertex].visited) {
            continue;
        }
        p_graph->vertices[currentVertex].visited = 1;
        GUI_displaypPath(p_graph);
        
        edge_t* temp = p_graph->vertices[currentVertex].edge;
        while(temp != NULL){
            int nextVertex = temp->dest;
            int weight = temp->weight;

            if(!p_graph->vertices[nextVertex].visited) {
                int newDist = p_graph->vertices[currentVertex].total_dist_to_src + weight;
                if(newDist < p_graph->vertices[nextVertex].total_dist_to_src) {
                    p_graph->vertices[nextVertex].total_dist_to_src = newDist;
                    p_graph->vertices[nextVertex].preVertex = currentVertex;
                    QUEUE_Put(p_queue, nextVertex, newDist, p_graph);
                }
            }
            temp = temp->next;
        }
        
    }
    QUEUE_Free(p_queue);
}

#endif