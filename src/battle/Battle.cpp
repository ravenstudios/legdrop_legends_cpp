#include "Battle.h"
#include "../Constants.h"


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
    
    m_NPC = npc;
    m_BattleUI.StartBattle(npc);
}