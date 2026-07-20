#include "MainState.h"



MainState::MainState()

    : m_Player(100, 100) 
{  
    
}


void MainState::Update(){
    m_Player.Update();
}


void MainState::Draw(){
    m_Player.Draw();
    DrawText("Main State", 20, 20, 30, WHITE);
}

