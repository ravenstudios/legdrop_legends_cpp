#include "StateManager.h"
#include "states/MainState.h"




StateManager::StateManager()
    :m_SoundManager(),
    m_Input(),
    m_player(),
    m_MainState(this),
    m_BattleState(this),
    m_PauseState(this),
    m_CurrentState(&m_MainState),
    m_StoreState(this)
    
    
{

    
}


void StateManager::Draw(){
    m_CurrentState->Draw();
}


void StateManager::Update(){
    UpdateInput();
    m_CurrentState->Update();
    m_SoundManager.Update();

    
}


void StateManager::StoreParrentState(State* state){
    m_ParrentState = state;
}


void StateManager::SwitchToBattleState(){
    LOG("switch battle");
    m_BattleState.StartBattle(m_player.GetCurrentNPC());
    m_ParrentState = &m_MainState;
    m_CurrentState = &m_BattleState;
}


void StateManager::SwitchToMainState(){
    LOG("switch main");
    m_CurrentState = &m_MainState;
    m_MainState.BackFromOtherState();
}


void StateManager::SwitchToPauseState(){
    if(m_CurrentState == &m_MainState){
        m_ParrentState = &m_MainState;
        m_CurrentState = &m_PauseState;
    }
    else{
        m_CurrentState = m_ParrentState;
    }
}

void StateManager::SwitchToStoreState(){
    m_ParrentState = &m_MainState;
    m_CurrentState = &m_StoreState;
}



void StateManager::UpdateInput(){
    m_InputState = m_Input.GetInputState();
    
    if(IsKeyPressed(KEY_P)){
        SwitchToPauseState();
    }

    m_CurrentState->UpdateInput(&m_InputState);
}


Player* StateManager::GetPlayer(){
    return &m_player;
}


SoundManager& StateManager::GetSoundManager(){
    return m_SoundManager;
}