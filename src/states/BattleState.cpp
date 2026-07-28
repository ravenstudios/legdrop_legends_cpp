#include "BattleState.h"
#include "../StateManager.h"



BattleState::BattleState(StateManager* stateManager)
    :m_StateManagerPtr(stateManager),
    m_Player(stateManager->GetPlayer()),
    m_Battle(m_Player)
{
    
}


void BattleState::Draw(){
    
    m_Battle.Draw();
}


void BattleState::Update(){
    m_Battle.Update();
}

void BattleState::UpdateInput(InputState* inputState){
    if(m_Battle.UpdateInput(inputState) == BattleMenuAction::Run)m_StateManagerPtr->SwitchToMainState();
}
    


void BattleState::StartBattle(NPC* npc){
    m_Battle.StartBattle(npc);
}

