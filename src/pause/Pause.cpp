#include "Pause.h"

Pause::Pause(Player* player)
    :m_Player(player),
    m_PauseUI(player)
{

}


void Pause::Update(){
    m_PauseUI.Update();
}


void Pause::Draw(){
    m_PauseUI.Draw();
}


void Pause::UpdateInput(InputState* inputState){
    m_PauseUI.UpdateInput(inputState);
}