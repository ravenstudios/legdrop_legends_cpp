#include "Battle.h"
#include "../Constants.h"
#include <string>
#include <vector>
#include "../objects/NPC.h"
#include <iostream>

Battle::Battle(Player* player)
    :m_Player(player),
    m_BattleUI(player),
    m_TurnTimer(k_TurnDelay)
    

{
  m_TurnTimer.SetPause(true);
}


void Battle::Update(){
  m_TurnTimer.Update(GetFrameTime());
  m_BattleUI.Update();
  if(m_currentTurn == Turn::Cpu){
    if(!m_TurnTimer.Finished()) return;
      CpuTurn();
      m_TurnTimer.Reset();
      m_TurnTimer.SetPause(true);
  }
}


void Battle::Draw(){
    m_BattleUI.Draw();
}


void Battle::StartBattle(NPC* npc){
    if(!npc){
        LOG("Start battle failed");
        return;
    }
    m_BattleResult = BattleResult::Ongoing;
    m_NPC = npc;
    m_BattleUI.StartBattle(npc);
}


// returns to battleState.
void Battle::UpdateInput(InputState* inputState){
  if(m_currentTurn == Turn::Cpu) return;
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
  m_CurrentWrestler = m_Player->GetCurrentWrestler();
  Data currentWrestlerData = m_CurrentWrestler->GetData();

  const auto& items = currentWrestlerData.items;
  Item item = items[index];
  std::string s = item.message;

  if(item.qty > 0){
    if(item.type == "restore_hp") m_CurrentWrestler->AdjustHP(item.hp);
    if(item.type == "restore_mp") m_CurrentWrestler->AdjustMP(item.mp);
    m_BattleUI.SetMessage(s);
    
    m_CurrentWrestler->AdjustItemQty(index, -1);
    StartCpuTurn();
  }
  
}


void Battle::Attack(int index){
  m_CurrentWrestler = m_Player->GetCurrentWrestler();
  m_CurrentOpponent = m_Player->GetCurrentNPC(); 

  Data currentWrestlerData = m_CurrentWrestler->GetData();
  Data currentOpponentData = m_CurrentOpponent->GetData();

  const auto& attacks = currentWrestlerData.attacks;
  const auto attack = attacks[index];

  if(currentWrestlerData.mp >= attack.cost){
    m_BattleUI.SetMessage(attack.name);
    m_CurrentOpponent->AdjustHP(-attack.power);
    m_CurrentWrestler->AdjustMP(-attack.cost);
    std::string s = {
      currentOpponentData.name + 
      " Used " + attack.name + ", Dealt " + 
      std::to_string(attack.power) +  " damage!"};

    m_BattleUI.SetMessage(s);
    m_TurnTimer.SetPause(false);
    m_currentTurn = Turn::Cpu;
    
  }

  else{
    m_BattleUI.SetMessage("Not enough MP");
  }

  if(m_CurrentOpponent->GetData().hp <= 0){
    LOG("opp dead");
    m_BattleUI.SetMessage("Player Won");
    
    m_BattleResult = BattleResult::PlayerWon;
  }
  
}


void Battle::Tag(int index){
  LOG("Tag");
}


BattleResult Battle::GetBattleResult(){
  return m_BattleResult;
}


void Battle::BattleOver(){
  m_BattleResult = BattleResult::PlayerWon;
}


void Battle::CpuTurn(){
  if(m_currentTurn == Turn::Player) return;

  m_CurrentWrestler = m_Player->GetCurrentWrestler();
  m_CurrentOpponent = m_Player->GetCurrentNPC(); 

  Data currentWrestlerData = m_CurrentWrestler->GetData();
  Data currentOpponentData = m_CurrentOpponent->GetData();

  const auto& attacks = currentOpponentData.attacks;
  int index = GetRandomValue(0, attacks.size() - 1);
  const auto attack = attacks[index];
  if(currentOpponentData.mp >= attack.cost){
    std::string s = {
      currentOpponentData.name + 
      " Used " + attack.name + ", Dealt " + 
      std::to_string(attack.power) +  " damage!"};
    m_BattleUI.SetMessage(s);
    m_CurrentWrestler->AdjustHP(-attack.power);
    m_CurrentOpponent->AdjustMP(-attack.cost);
    m_BattleUI.SetMessage(s);
    m_currentTurn = Turn::Player;
  }

  if(m_CurrentWrestler->GetData().hp <= 0){
    m_BattleUI.SetMessage("Player Lost");
    
    m_BattleResult = BattleResult::PlayerLost;
  }
}


void Battle::StartCpuTurn(){
  m_TurnTimer.SetPause(false);
  m_currentTurn = Turn::Cpu;
}