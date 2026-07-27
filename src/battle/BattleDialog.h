#pragma once
#include "raylib.h"
#include "../objects/NPC.h"
#include "../Constants.h"
#include "../objects/Player.h"

class BattleDialog{
    public:
        BattleDialog(Rectangle rect, Player* player);
        void Update();
        void Draw();

    private:
        Player* m_Player = nullptr;
        Rectangle m_Rect={};
     

};