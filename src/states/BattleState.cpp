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
    if(m_Battle.GetBattleResult() == BattleResult::Escaped){
      m_StateManagerPtr->SwitchToMainState();
    }
}

void BattleState::UpdateInput(InputState* inputState){
    m_Battle.UpdateInput(inputState);
}



void BattleState::StartBattle(NPC* npc){
    m_Battle.StartBattle(npc);
}
