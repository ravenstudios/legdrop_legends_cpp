#include "MainState.h"



MainState::MainState()

    : m_Player(100, 100),
    m_Map("src/assets/maps/town1.tmx")
{  
    
}


void MainState::Update(){
    m_Player.Update();
}


void MainState::Draw(){
    m_Map.Draw();
    m_Player.Draw();
    DrawText("Main State", 20, 20, 30, WHITE);
    
}

