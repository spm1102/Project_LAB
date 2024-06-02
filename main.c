#include"gui.h"


//void print_shortest_path(graph_t* p_graph, int src, int dest);

int main() {
    SetTargetFPS(60);
    cell_t (*grid)[ROWS] = GRID_Create();
    // grid[3][3].IS_source = true;
    // grid[0][5].IS_dest = true;
    // grid[2][4].IS_containWall = true;
    // grid[1][5].IS_containWall = true;
    // grid[0][4].IS_containWall = true;
    // graph_t* p_graph = GEN_GRAPH_Create(grid);
    //a_star_queue(p_graph, 33, 5);
    //print_shortest_path(p_graph, 33, 5);
    GUI_INIT(grid);
    GRID_Free(grid);
    //GRAPH_Free(p_graph);


    return 0;
}



// void print_shortest_path(graph_t* p_graph, int src, int dest){
//     if(p_graph->vertices[dest].total_dist_to_src == INT_MAX) {
//         printf("\nThere is no path from %d to %d", src, dest);
//         return;
//     }
//     else{
//         int currVertex = dest;
//         int pathLength = 0;
//         int path[MAX_PATH_LENGTH];
//         while(currVertex != src){
//             path[pathLength++] = currVertex;
//             currVertex = p_graph->vertices[currVertex].preVertex;
//         }
        
//         printf("\nShortest path from vertex %d to %d: ", src, dest);
//         printf("%d ", src);
//         for(int i = pathLength - 1; i >= 0; i--){
//             printf("%d ", path[i]);
//         }
//         printf("\nDistance: %d\n", p_graph->vertices[dest].total_dist_to_src);
//     }
// }

