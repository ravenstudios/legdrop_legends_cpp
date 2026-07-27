#pragma once
#include "raylib.h"
#include "../objects/NPC.h"
#include "../Constants.h"

class BattleHealthBar{
    public:
        BattleHealthBar(Rectangle rect);
        ~BattleHealthBar();
        void Update();
        void Draw();
        void SetNPC(NPC* npc);

    private:
        Rectangle m_Rect={};
        NPC* m_NPC = nullptr;

};