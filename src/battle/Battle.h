#pragma once
#include "../objects/Player.h"
#include "../objects/NPC.h"
#include "BattleUI.h"
#include "../core/Input.h"
#include "BattleMenuAction.h"



class Battle{
    public:
        Battle(Player* player);
        void Update();
        void Draw();
        void StartBattle(NPC* npc);
        BattleMenuAction UpdateInput(InputState* inputState);
        


    private:
        Player* m_Player;
        NPC* m_NPC = nullptr;
        BattleUI m_BattleUI;

};  