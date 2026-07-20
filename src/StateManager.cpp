#include "StateManager.h"
#include "states/MainState.h"



StateManager::StateManager()

    : m_MainState(),
    m_CurrentState(&m_MainState)
{

    
}


void StateManager::Draw(){
    m_CurrentState->Draw();
}


void StateManager::Update(){
    m_CurrentState->Update();
}

