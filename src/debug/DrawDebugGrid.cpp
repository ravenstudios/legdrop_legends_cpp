#include "DrawDebugGrid.h"

DrawDebugGrid::DrawDebugGrid(){

}


void DrawDebugGrid::Draw(){
    for(size_t r = 0; r < ROWS; r++){
        DrawLine(0, r * BLOCK_SIZE, GAME_WIDTH, r * BLOCK_SIZE, RED); 
    }
    for(size_t c = 0; c < COLS; c++){
        DrawLine(c * BLOCK_SIZE, 0, c * BLOCK_SIZE, c * BLOCK_SIZE, RED); 
    }
}


