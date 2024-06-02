#ifndef GUI_H
#define GUI_H

#include"a_star.h"
#include"raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_PATH_LENGTH 100



static void CELL_Draw(cell_t cell);
static bool INDEX_IsValid(int x, int y);
static void GUI_displayPath(graph_t* p_graph);
static void GUI_findShortestPath(cell_t (*grid)[ROWS]);
static void GUI_INIT(cell_t (*grid)[ROWS]);


void CELL_Draw(cell_t cell){
    if(cell.IS_containWall){
        DrawRectangle(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, YELLOW);
    }
    else if(cell.IS_source){
        DrawRectangle(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, RED);
    }
    else if(cell.IS_dest){
        DrawRectangle(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, BLUE);
    }
    
    DrawRectangleLines(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, BLACK);

}

bool INDEX_IsValid(int x, int y) {
    return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}


inline void GUI_displayPath(graph_t* p_graph) {
    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            if(p_graph->vertices[COLS * i + j].visited == true){
                DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight, GREEN);
            }

        }
    }
}

inline void GUI_findShortestPath(cell_t (*grid)[ROWS]) {
    graph_t* p_graph = GEN_GRAPH_Create(grid);
    int source = TAKE_source(grid);
    int dest = TAKE_dest(grid);
    a_star_queue(p_graph, source, dest, &GUI_displayPath);
    int currentVertex = dest; 
    int pathLength = 0;
    int path[MAX_PATH_LENGTH];
    while(currentVertex != source) {
        path[pathLength++] = currentVertex;
        currentVertex = p_graph->vertices[currentVertex].preVertex;
        int j = currentVertex % 10;
        int i = (currentVertex - j) / 10;
        grid[i][j].IS_inPath = true;
    }

}

void GUI_INIT(cell_t (*grid)[ROWS]) {
    InitWindow(screenWidth, screenHeight, "Algorithm");
    
    bool isDrawingWalls = false;
    bool hasSource = false;
    bool hasDest = false;
    int sourceX = -1;
    int sourceY = -1;
    int destX = -1;
    int destY = -1;

    bool isAlgorithmRunning = false;

    while(!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isDrawingWalls = true;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDrawingWalls = false;
        }

        if(isDrawingWalls) {
            Vector2 mPos = GetMousePosition();
            int inX = mPos.x / cellWidth;
            int inY = mPos.y / cellHeight;
            Rectangle bound;
            bound.x = grid[inX][inY].x * cellWidth;
            bound.y = grid[inX][inY].y * cellHeight;
            bound.width = cellWidth;
            bound.height = cellHeight;
            if(INDEX_IsValid(inX, inY) && CheckCollisionPointRec(mPos, bound)) {
                grid[inX][inY].IS_containWall = true;
            }
        }
        else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Vector2 mPos2 = GetMousePosition();
            int inX = mPos2.x / cellWidth;
            int inY = mPos2.y / cellHeight;

            if (INDEX_IsValid(inX, inY)) {
                if (!hasSource) {
                    hasSource = true;
                    sourceX = inX;
                    sourceY = inY;
                    grid[inX][inY].IS_source = true;
                } else if (!hasDest) {
                    hasDest = true;
                    destX = inX;
                    destY = inY;
                    grid[inX][inY].IS_dest = true;
                } else {
                    // Clear previous source and destination
                    grid[sourceX][sourceY].IS_source = false;
                    grid[destX][destY].IS_dest = false;
                    hasSource = false;
                    hasDest = false;
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        //GuiToggleGroup((Rectangle){0, 0 , cellWidth, cellHeight}, "BFS; Dijkstra; A Star", &ToggleGroup001Active);

        for(int i = 0; i < COLS; i++){
            for(int j = 0; j < ROWS; j++){
                CELL_Draw(grid[i][j]);
            }
        }

        if(IsKeyPressed(KEY_ENTER) && sourceX != -1 && sourceY != -1 && destX != -1 && destY != -1 ){
            isAlgorithmRunning = true;
            GUI_findShortestPath(grid);
        }

        if(isAlgorithmRunning) {
            for(int i = 0; i < COLS; i++){
                for(int j = 0; j < ROWS; j++){
                    if(grid[i][j].IS_inPath){
                        DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight, GRAY);
                    }
                }
            }
        }
        EndDrawing();
    }


    CloseWindow();
}
#endif