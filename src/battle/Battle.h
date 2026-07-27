#pragma once
#include "../objects/Player.h"
#include "../objects/NPC.h"
#include "BattleUI.h"


class Battle{
    public:
        Battle(Player* player);
        void Update();
        void Draw();
        void StartBattle(NPC* npc);
        


    private:
        Player* m_Player;
        NPC* m_NPC = nullptr;
        BattleUI m_BattleUI;

};  