#include "raylib.h"
#include "Constants.h"
#include "StateManager.h"



void update(StateManager& stateManager){
    stateManager.Update();
}


void draw(StateManager& stateManager){
    BeginDrawing();
    ClearBackground(DARKGREEN);
    stateManager.Draw();
    EndDrawing();
}


int main(){
    
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Wrestling Game");
    SetTargetFPS(TICK_RATE);

    StateManager stateManager;
    while (!WindowShouldClose()){
        if (IsKeyPressed(KEY_Q)){
            break;
        }
        update(stateManager);
        draw(stateManager);
    }

    CloseWindow();

    return 0;
}