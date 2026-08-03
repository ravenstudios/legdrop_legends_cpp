#include "PauseState.h"
#include "../StateManager.h"




PauseState::PauseState(StateManager* stateManager)
    :m_StateManagerPtr(stateManager),
    m_Player(stateManager->GetPlayer()),
    m_Pause(m_Player)
{

}


void PauseState::Draw(){

    m_Pause.Draw();
}


void PauseState::Update(){
    m_Pause.Update();
    
}

void PauseState::UpdateInput(InputState* inputState){
    m_Pause.UpdateInput(inputState);
}

