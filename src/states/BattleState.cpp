#include "BattleState.h"
#include "../StateManager.h"



BattleState::BattleState(StateManager* stateManager)
    :m_StateManagerPtr(stateManager)
{
    
}


void BattleState::Draw(){
    DrawRectangle(50, 50, 50, 50, RED);
}


void BattleState::Update(){

}

void BattleState::UpdateInput(InputState* inputState){
    if(inputState->action){
        m_StateManagerPtr->SwitchToMainState();
    }
}
    



