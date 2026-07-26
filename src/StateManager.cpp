#include "StateManager.h"
#include "states/MainState.h"




StateManager::StateManager()

    :m_Input(),
    m_MainState(this),
    m_BattleState(this),
    m_CurrentState(&m_MainState)
{

    
}


void StateManager::Draw(){
    m_CurrentState->Draw();
}


void StateManager::Update(){
    UpdateInput();
    m_CurrentState->Update();
}


void StateManager::StoreParrentState(State* state){
    m_ParrentState = state;
}


void StateManager::SwitchToBattleState(){
    LOG("switch battle");
     m_ParrentState = &m_MainState;
     m_CurrentState = &m_BattleState;
}


void StateManager::SwitchToMainState(){
    LOG("switch main");
    m_CurrentState = &m_MainState;
}


void StateManager::SwitchToPauseState(){

}

void StateManager::UpdateInput(){
    m_InputState = m_Input.GetInputState();
    
    m_CurrentState->UpdateInput(&m_InputState);
}

