#include "Battle.h"
#include "../Constants.h"
#include <string>
#include <vector>
#include "../objects/NPC.h"

Battle::Battle(Player* player)
    :m_Player(player),
    m_BattleUI(player)

{

}


void Battle::Update(){
    m_BattleUI.Update();
}


void Battle::Draw(){
    m_BattleUI.Draw();
}


void Battle::StartBattle(NPC* npc){
    LOG("Start battle");
    if(!npc){
        LOG("Start battle failed");
        return;
    }
    m_BattleResult = BattleResult::Ongoing;
    m_NPC = npc;
    m_BattleUI.StartBattle(npc);
}
// enum class BattleResult {
//     Ongoing,
//     Escaped,
//     PlayerWon,
//     PlayerLost
// };

// returns to battleState.
void Battle::UpdateInput(InputState* inputState){
    BattleCommand battleCommand = m_BattleUI.UpdateInput(inputState);
    switch(battleCommand.type){
      case BattleMenuAction::Attack:
        Attack(battleCommand.selectionIndex);
        break;
      case BattleMenuAction::Item:
        Bag(battleCommand.selectionIndex);
        break;
      case BattleMenuAction::Tag:
        Tag(battleCommand.selectionIndex);
        break;
      case BattleMenuAction::Run:
        Run();
        break;
      default:
        break;
    }


    if(battleCommand.type == BattleMenuAction::Run){

    }

}

void Battle::Run(){
  m_BattleResult = BattleResult::Escaped;
}

void Battle::Bag(int index){
  LOG("Bag");
}

void Battle::Attack(int index){
  LOG("Attack");
  const auto& attacks = m_Player->GetCurrentWrestler()->GetData().attacks;
  m_BattleUI.SetMessage(attacks[index].name);
}

void Battle::Tag(int index){
  LOG("Tag");
}

BattleResult Battle::GetBattleResult(){
  return m_BattleResult;
}
